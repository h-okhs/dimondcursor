// OptionDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "DiamondCursor.h"
#include "OptionDlg.h"

// COptionDlg ダイアログ

IMPLEMENT_DYNAMIC(COptionDlg, CDialog)
COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionDlg::IDD, pParent)
{
}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	int i;
	CDialog::DoDataExchange(pDX);
	for (i = 0; i < 11; i++)
		DDX_Control(pDX, IDC_BUTTON1 + i, m_ctlKeyButton[i]);
	DDX_Control(pDX, IDC_EDIT1, m_ctlEditKeySet);
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON1, IDC_BUTTON11, OnBnClickedKeyButton)
	ON_EN_CHANGE(IDC_EDIT1, OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// COptionDlg メッセージ ハンドラ

BOOL COptionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO :  ここに初期化を追加してください
	m_bInEditChange = FALSE;
/*	RECT rcButton, rcEditClient;
	CFont *pFont;
	CFont cFont;
	LOGFONT sLogFont;
	CDC *pDC;
	TEXTMETRIC sTM;

	m_ctlKeyButton[0].GetWindowRect(&rcButton);
	m_sButtonSize.cx = rcButton.right - rcButton.left;
	m_sButtonSize.cy = rcButton.bottom - rcButton.top;

	pFont = m_ctlEditKeySet.GetFont();
	pFont->GetLogFont(&sLogFont);
	pDC = m_ctlEditKeySet.GetDC();
	pDC->GetTextMetrics(&sTM);
	m_ctlEditKeySet.SetWindowPos(NULL, 0, 0, sTM.tmMaxCharWidth, abs(sLogFont.lfHeight) + 2, SWP_NOMOVE|SWP_NOZORDER);

	m_ctlEditKeySet.GetClientRect(&rcEditClient);
	m_lEditSize.cx= rcEditClient.right;
	m_lEditSize.cy = rcEditClient.bottom;
*/
	int i;
	char szTemp[2];

	szTemp[1] = NULL;
	for (i = 0; i < 11; i++)
	{
		szTemp[0] = m_pbyKey[i];
		m_ctlKeyButton[i].SetWindowText(szTemp);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void COptionDlg::OnBnClickedKeyButton(UINT uiID)
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
/*	int nButtonIndex;
	RECT rcButton, rcEditClient;

	nButtonIndex = uiID - IDC_BUTTON1;
	m_ctlKeyButton[nButtonIndex].GetWindowRect(&rcButton);
	this->ScreenToClient(&rcButton);
	m_ctlEditKeySet.GetClientRect(&rcEditClient);

	m_ctlEditKeySet.SetWindowPos(NULL, rcButton.left + (m_sButtonSize.cx - m_lEditSize.cx) / 2, rcButton.top + ((rcButton.bottom -rcButton.top)- rcEditClient.bottom) / 2 - 2, 0, 0, SWP_NOSIZE|SWP_NOZORDER);
*/
	CString strTemp;

	m_ctlEditKeySet.SetReadOnly(FALSE);
	m_ctlEditKeySet.SetFocus();
	m_nCurrentEdit = uiID - IDC_BUTTON1;

	SetDlgItemText(IDC_STATIC, szKeyName[m_nCurrentEdit]);
	m_ctlEditKeySet.SetWindowText("");
}

void COptionDlg::OnEnChangeEdit1()
{
	// TODO :  ここにコントロール通知ハンドラ コードを追加してください。
	CString strTemp;
	CString strTemp2;
	int i;

	if (m_bInEditChange)
		return;

	if (m_ctlEditKeySet.GetWindowTextLength() == 0)
		return;

	m_ctlEditKeySet.GetWindowText(strTemp);
	for (i = 0; i < 11; i++)
	{
		m_ctlKeyButton[i].GetWindowText(strTemp2);
		if (strTemp.Left(1).Compare(strTemp2.Left(1)) == 0)
		{
			m_ctlKeyButton[i].SetWindowText("");
			break;
		}
	}

	m_ctlEditKeySet.SetReadOnly(TRUE);

	m_ctlKeyButton[m_nCurrentEdit].SetWindowText((LPCTSTR)strTemp);
	SetDlgItemText(IDC_STATIC, szKeyName[m_nCurrentEdit]);

	m_bInEditChange = FALSE;
}

void COptionDlg::OnBnClickedOk()
{
	// TODO : ここにコントロール通知ハンドラ コードを追加します。
	int i;
	char szTemp[2];

	for (i = 0; i < 11; i++)
	{
		m_ctlKeyButton[i].GetWindowText(szTemp, 2);
		m_pbyKey[i] = szTemp[0];
	}

	OnOK();
}
