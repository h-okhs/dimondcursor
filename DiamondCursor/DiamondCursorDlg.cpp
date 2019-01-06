// DiamondCursorDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "DiamondCursor.h"
#include "DiamondCursorDlg.h"
#include "OptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiamondCursorDlg ダイアログ

CDiamondCursorDlg::CDiamondCursorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiamondCursorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDiamondCursorDlg::~CDiamondCursorDlg()
{
	int i;
	char szTemp[2];

	szTemp[1] = NULL;
	for (i = 0; i < 11; i++)
	{
		szTemp[0] = *(m_cKBHook.GetKeySetPtr() + i);
		WritePrivateProfileString(APPNAME, szKeyName[i], szTemp, ".\\dc.ini");
	}
}

void CDiamondCursorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDiamondCursorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_MESSAGE(WM_NOTIFYICON, OnNotifyIcon)
	ON_COMMAND(ID_CUSTOMIZE, OnCustomize)
	ON_COMMAND(ID_NI_CUSTOMIZE, OnNiCustomize)
	ON_COMMAND(ID_NI_QUIT, OnNiQuit)
END_MESSAGE_MAP()


// CDiamondCursorDlg メッセージ ハンドラ

BOOL CDiamondCursorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	if (m_bAutoStart)
	{
		m_cKBHook.Set();
		theApp.EnableNotifyIcon(TRUE, GetSafeHwnd());
	}

	int i;
	DWORD dwTemp;
	char szTemp[128];

	for (i = 0; i < 11; i++)
	{
		dwTemp = GetPrivateProfileString(APPNAME, szKeyName[i], NULL, szTemp, 128, ".\\dc.ini");
		if (dwTemp != 0)
			*(m_cKBHook.GetKeySetPtr() + i) = szTemp[0];
	}

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CDiamondCursorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CDiamondCursorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDiamondCursorDlg::OnBnClickedOk()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	m_cKBHook.Set();
	ShowWindow(SW_HIDE);
	theApp.EnableNotifyIcon(TRUE, GetSafeHwnd());
}

void CDiamondCursorDlg::OnBnClickedCancel()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	theApp.EnableNotifyIcon(FALSE, GetSafeHwnd());
	OnCancel();
}

LRESULT CDiamondCursorDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONDBLCLK:
		m_cKBHook.Unset();
		theApp.EnableNotifyIcon(FALSE, GetSafeHwnd());
		ShowWindow(SW_SHOW);
		break;

	case WM_RBUTTONDOWN:
		NotifyIconPopupMenu();
		break;
	}

	return 0;
}

void CDiamondCursorDlg::NotifyIconPopupMenu()
{
	CMenu Menu;
	CMenu *pSubMenu;

	Menu.LoadMenu(IDR_MENU1);
	pSubMenu = Menu.GetSubMenu(0);

	if(pSubMenu == NULL)
		return;

	POINT point;
	GetCursorPos(&point);
		
	SetForegroundWindow();
	pSubMenu->TrackPopupMenu(TPM_LEFTBUTTON, (INT)point.x, (INT)point.y, this, NULL);
	PostMessage(WM_NULL, 0, 0); 

	pSubMenu->DestroyMenu();
	Menu.DestroyMenu();
}

void CDiamondCursorDlg::OnCustomize()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	COptionDlg dlg;
	dlg.m_pbyKey = m_cKBHook.GetKeySetPtr();
	dlg.DoModal();
}

void CDiamondCursorDlg::OnNiCustomize()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。

	//一旦停止
	m_cKBHook.Unset();
	theApp.EnableNotifyIcon(FALSE, GetSafeHwnd());
	ShowWindow(SW_SHOW);

	COptionDlg dlg;
	dlg.m_pbyKey = m_cKBHook.GetKeySetPtr();
	dlg.DoModal();

	//再起動
	m_cKBHook.Set();
	ShowWindow(SW_HIDE);
	theApp.EnableNotifyIcon(TRUE, GetSafeHwnd());
}

void CDiamondCursorDlg::OnNiQuit()
{
	// TODO : ここにコマンド ハンドラ コードを追加します。
	theApp.EnableNotifyIcon(FALSE, GetSafeHwnd());
	EndDialog(0);
}
