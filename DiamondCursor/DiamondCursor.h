// DiamondCursor.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

#define WM_NOTIFYICON	(WM_APP + 1)
// CDiamondCursorApp:
// ���̃N���X�̎����ɂ��ẮADiamondCursor.cpp ���Q�Ƃ��Ă��������B
//

class CDiamondCursorApp : public CWinApp
{
public:
	CDiamondCursorApp();
	~CDiamondCursorApp();

// �I�[�o�[���C�h
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()

public:
	void EnableNotifyIcon(BOOL bEnable, HWND hWndSendMessage);

private:
	HANDLE m_hMutex;
};

extern CDiamondCursorApp theApp;
