// DiamondCursor.cpp : アプリケーションのクラス動作を定義します。
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


// CDiamondCursorApp コンストラクション

CDiamondCursorApp::CDiamondCursorApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

CDiamondCursorApp::~CDiamondCursorApp()
{
}

// 唯一の CDiamondCursorApp オブジェクトです。

CDiamondCursorApp theApp;


// CDiamondCursorApp 初期化

BOOL CDiamondCursorApp::InitInstance()
{
	m_hMutex = ::CreateMutex(NULL, TRUE, "OYAYUBI_HIME");
	if (::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		::CloseHandle(m_hMutex);
		return FALSE;
	}

	// アプリケーション　マニフェストが　visual スタイルを有効にするために、
	// ComCtl32.dll バージョン 6　以降の使用を指定する場合は、
	// Windows XP に　InitCommonControls() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	CDiamondCursorDlg dlg;
	m_pMainWnd = &dlg;
	dlg.m_bAutoStart = (lstrcmpi(m_lpCmdLine, "-auto") == 0);
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//       記述してください。
	}

	if (m_hMutex != NULL)
		::CloseHandle(m_hMutex);
	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	// アプリケーションを終了するために FALSE を返してください。
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
		lstrcpy(nid.szTip, _T("クソゲー"));
		::Shell_NotifyIcon(NIM_ADD, &nid);
		DestroyIcon(nid.hIcon);
	}
	else
	{
		::Shell_NotifyIcon(NIM_DELETE, &nid);
	}
}
