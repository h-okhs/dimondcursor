#pragma once
#include "afxwin.h"

// COptionDlg �_�C�A���O

class COptionDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~COptionDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_OPTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

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
