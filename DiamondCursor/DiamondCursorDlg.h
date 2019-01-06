// DiamondCursorDlg.h : ヘッダー ファイル
//

#pragma once


// CDiamondCursorDlg ダイアログ
class CDiamondCursorDlg : public CDialog
{
// コンストラクション
public:
	CDiamondCursorDlg(CWnd* pParent = NULL);	// 標準コンストラクタ
	~CDiamondCursorDlg();
// ダイアログ データ
	enum { IDD = IDD_DIAMONDCURSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;
public:
	CKBHook m_cKBHook;


protected:
	// 生成された、メッセージ割り当て関数
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
