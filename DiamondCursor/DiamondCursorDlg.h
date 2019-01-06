// DiamondCursorDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once


// CDiamondCursorDlg �_�C�A���O
class CDiamondCursorDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CDiamondCursorDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^
	~CDiamondCursorDlg();
// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIAMONDCURSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;
public:
	CKBHook m_cKBHook;


protected:
	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void CDiamondCursorDlg::OnNotifyIconClick();

	BOOL m_bAutoStart;

private:
	void NotifyIconPopupMenu();


private:
	UINT m_uiNotifyIconMsgID;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCustomize();
	afx_msg void OnNiCustomize();
	afx_msg void OnNiQuit();
};
