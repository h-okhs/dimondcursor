// DiamondCursor.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

#define WM_NOTIFYICON	(WM_APP + 1)
// CDiamondCursorApp:
// このクラスの実装については、DiamondCursor.cpp を参照してください。
//

class CDiamondCursorApp : public CWinApp
{
public:
	CDiamondCursorApp();
	~CDiamondCursorApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()

public:
	void EnableNotifyIcon(BOOL bEnable, HWND hWndSendMessage);

private:
	HANDLE m_hMutex;
};

extern CDiamondCursorApp theApp;
