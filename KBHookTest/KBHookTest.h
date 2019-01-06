// KBHookTest.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル


// CKBHookTestApp:
// このクラスの実装については、KBHookTest.cpp を参照してください。
//

class CKBHookTestApp : public CWinApp
{
public:
	CKBHookTestApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CKBHookTestApp theApp;
