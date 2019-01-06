// DiamondCursorDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "DiamondCursor.h"
#include "DiamondCursorDlg.h"
#include "OptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDiamondCursorDlg �_�C�A���O

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


// CDiamondCursorDlg ���b�Z�[�W �n���h��

BOOL CDiamondCursorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
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

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CDiamondCursorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CDiamondCursorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDiamondCursorDlg::OnBnClickedOk()
{
	// TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	m_cKBHook.Set();
	ShowWindow(SW_HIDE);
	theApp.EnableNotifyIcon(TRUE, GetSafeHwnd());
}

void CDiamondCursorDlg::OnBnClickedCancel()
{
	// TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
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
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	COptionDlg dlg;
	dlg.m_pbyKey = m_cKBHook.GetKeySetPtr();
	dlg.DoModal();
}

void CDiamondCursorDlg::OnNiCustomize()
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B

	//��U��~
	m_cKBHook.Unset();
	theApp.EnableNotifyIcon(FALSE, GetSafeHwnd());
	ShowWindow(SW_SHOW);

	COptionDlg dlg;
	dlg.m_pbyKey = m_cKBHook.GetKeySetPtr();
	dlg.DoModal();

	//�ċN��
	m_cKBHook.Set();
	ShowWindow(SW_HIDE);
	theApp.EnableNotifyIcon(TRUE, GetSafeHwnd());
}

void CDiamondCursorDlg::OnNiQuit()
{
	// TODO : �����ɃR�}���h �n���h�� �R�[�h��ǉ����܂��B
	theApp.EnableNotifyIcon(FALSE, GetSafeHwnd());
	EndDialog(0);
}
