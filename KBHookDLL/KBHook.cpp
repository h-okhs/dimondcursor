#include "StdAfx.h"
#include "kbhookdll.h"
#include "kbhook.h"

#pragma data_seg(".CKBHookData")
	HHOOK	CKBHook::m_hHook = NULL;
	BOOL	CKBHook::m_bDiamondON = FALSE;
	BOOL	CKBHook::m_bNT4 = FALSE;
/*	BYTE	CKBHook::m_byKey[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
									 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
									 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
									 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
									 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
									 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
									 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
									 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
*/
	BYTE	CKBHook::m_byKey[16] = {'H','Q','9','0','U','O','P','I','J','K','L',0,0,0,0,0};
#pragma data_seg()

#pragma comment(lib, "imm32.lib")

const LONG VKTABLE[16] = {
	VK_BACK,
	VK_INSERT,
	VK_HOME,
	VK_PRIOR,
	VK_DELETE,
	VK_END,
	VK_NEXT,
	VK_UP,
	VK_LEFT,
	VK_DOWN,
	VK_RIGHT,
	0,0,0,0,0
};

CKBHook::CKBHook(void)
{
	m_hHook = NULL;
	m_bDiamondON = FALSE;
	m_bNT4 = FALSE;

/*	OSVERSIONINFOEX osver;
	DWORDLONG dwlConditionMask = 0;
	::ZeroMemory(&osver, sizeof(OSVERSIONINFOEX));
	osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	osver.dwMajorVersion = 4;
	osver.dwMinorVersion = 0;
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_LESS_EQUAL);
	VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, VER_LESS_EQUAL);
	m_bNT4 = (VerifyVersionInfo(&osver, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask) != 0);
*/
	OSVERSIONINFO osver;
	osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osver);
	m_bNT4 = (osver.dwMajorVersion < 5);
}

CKBHook::~CKBHook(void)
{
	Unset();
}

BOOL CKBHook::Set(void)
{
	if (m_hHook != NULL)
		return TRUE;

	m_hHook = ::SetWindowsHookEx(WH_KEYBOARD, CKBHook::KeyboardProc, GetThisHInst(), 0);
	if (m_hHook == NULL)
		return FALSE;

	return TRUE;
}

void CKBHook::Unset(void)
{
	if (m_hHook != NULL)
	{
		::UnhookWindowsHookEx(m_hHook);
		m_hHook = NULL;
	}
}

BYTE *CKBHook::GetKeySetPtr(void)
{
	return m_byKey;
}

LRESULT CALLBACK CKBHook::KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	BOOL bReplaceKey;
	UINT uiMsg;
	int i;
	BYTE byTemp;

	if( code < 0 || code == HC_NOREMOVE )
		return ::CallNextHookEx(CKBHook::m_hHook, code, wParam, lParam);

//	if ((lParam & (1 << 29)) != 0)	//ALT check
//		return ::CallNextHookEx(CKBHook::m_hHook, code, wParam, lParam);

	if (lParam & (1 << 31))	//keyup?
		uiMsg = WM_KEYUP;
	else
		uiMsg = WM_KEYDOWN;

	switch (wParam & 0xFF)
	{
	case VK_OEM_AUTO:
	case VK_OEM_ENLW:
		if (m_bNT4 && uiMsg == WM_KEYUP)
		{
			::ImmSimulateHotKey(::GetFocus(), IME_JHOTKEY_CLOSE_OPEN);
			return 1;
		}
		break;

	case VK_CONVERT:
	case VK_NONCONVERT:
		if (CKBHook::m_bDiamondON == (uiMsg == WM_KEYUP))
			CKBHook::m_bDiamondON ^= TRUE;
		break;

	case VK_RETURN:
	case VK_TAB:
	case VK_SHIFT:
	case VK_CONTROL:
		return ::CallNextHookEx(CKBHook::m_hHook, code, wParam, lParam);
		break;
	}

	if (CKBHook::m_bDiamondON)
	{
		bReplaceKey = TRUE;

		byTemp = (BYTE)(wParam & 0xFF);
		for (i = 0; i < 16; i++)
		{
			if (m_byKey[i] != 0)
			{
				if ((::MapVirtualKey((UINT)byTemp, 2) & 0xFF) == m_byKey[i])
				{
					wParam = VKTABLE[i];
					break;
				}
			}
		}
		if (i == 16)
			bReplaceKey = FALSE;

		if (bReplaceKey)
		{
			lParam &= 0xFF00FFFF;
			lParam |= ((::MapVirtualKey((UINT)wParam, 0) & 0xFF) << 16);
		}
	}

	if (CKBHook::m_bDiamondON)
	{
		if (bReplaceKey)
			::PostMessage(::GetFocus(), uiMsg, wParam, lParam);
		return 1;
	}

	return ::CallNextHookEx(CKBHook::m_hHook, code, wParam, lParam);
}
