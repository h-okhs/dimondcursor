#include "StdAfx.h"
#include "sendinput.h"

CSendInput::CSendInput(void)
{
	m_nInputNum = 0;
}

CSendInput::~CSendInput(void)
{
}

BOOL CSendInput::CreateKeyboardInput(WORD wVK)
{
	if (m_nInputNum >= SI_INPUTBUFFERMAX)
		return FALSE;

	if (wVK < 1 || wVK > 254)
		return FALSE;

	return TRUE;
}

void CSendInput::Send()
{
	if (m_nInputNum = 0)
		return;

	::SendInput(m_nInputNum, m_InputData, sizeof(INPUT));
}
