#pragma once
#include "afxwin.h"

// COptionDlg ダイアログ

class COptionDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~COptionDlg();

// ダイアログ データ
	enum { IDD = IDD_OPTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedKeyButton(UINT uiID);
	afx_msg void OnEnChangeEdit1();

	virtual BOOL OnInitDialog();

private:
	CButton m_ctlKeyButton[11];
	CEdit m_ctlEditKeySet;
	SIZE m_lEditSize;
	SIZE m_sButtonSize;
	int m_nCurrentEdit;
	BOOL m_bInEditChange;

public:
	BYTE *m_pbyKey;
	afx_msg void OnBnClickedOk();
};
