// KBHookTestDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "../KBHookDLL/KBHook.h"
#include "afxwin.h"

// CKBHookTestDlg �_�C�A���O
class CKBHookTestDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CKBHookTestDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_KBHOOKTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;
	CKBHook m_cKBHook;
	char m_szBuf[256];

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListBox m_ctlList;
	afx_msg void OnBnClickedOk();
};
