// KBHookTestDlg.h : ヘッダー ファイル
//

#pragma once
#include "../KBHookDLL/KBHook.h"
#include "afxwin.h"

// CKBHookTestDlg ダイアログ
class CKBHookTestDlg : public CDialog
{
// コンストラクション
public:
	CKBHookTestDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_KBHOOKTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;
	CKBHook m_cKBHook;
	char m_szBuf[256];

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListBox m_ctlList;
	afx_msg void OnBnClickedOk();
};
