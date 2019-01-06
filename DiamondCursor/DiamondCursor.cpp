// DiamondCursor.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "DiamondCursor.h"
#include "DiamondCursorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiamondCursorApp

BEGIN_MESSAGE_MAP(CDiamondCursorApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDiamondCursorApp �R���X�g���N�V����

CDiamondCursorApp::CDiamondCursorApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

CDiamondCursorApp::~CDiamondCursorApp()
{
}

// �B��� CDiamondCursorApp �I�u�W�F�N�g�ł��B

CDiamondCursorApp theApp;


// CDiamondCursorApp ������

BOOL CDiamondCursorApp::InitInstance()
{
	m_hMutex = ::CreateMutex(NULL, TRUE, "OYAYUBI_HIME");
	if (::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		::CloseHandle(m_hMutex);
		return FALSE;
	}

	// �A�v���P�[�V�����@�}�j�t�F�X�g���@visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll �o�[�W���� 6�@�ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �Ɂ@InitCommonControls() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CDiamondCursorDlg dlg;
	m_pMainWnd = &dlg;
	dlg.m_bAutoStart = (lstrcmpi(m_lpCmdLine, "-auto") == 0);
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �_�C�A���O�� <�L�����Z��> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}

	if (m_hMutex != NULL)
		::CloseHandle(m_hMutex);
	// �_�C�A���O�͕����܂����B�A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n���Ȃ���
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}

void CDiamondCursorApp::EnableNotifyIcon(BOOL bEnable, HWND hWndSendMessage)
{
	NOTIFYICONDATA nid;
	::ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWndSendMessage;

	if (bEnable)
	{
		nid.uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE;
		nid.hIcon = (HICON)::LoadImage(theApp.m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
		nid.uCallbackMessage = WM_NOTIFYICON;
		lstrcpy(nid.szTip, _T("�N�\�Q�["));
		::Shell_NotifyIcon(NIM_ADD, &nid);
		DestroyIcon(nid.hIcon);
	}
	else
	{
		::Shell_NotifyIcon(NIM_DELETE, &nid);
	}
}
