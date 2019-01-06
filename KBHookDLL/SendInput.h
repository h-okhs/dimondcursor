#pragma once

#define SI_INPUTBUFFERMAX		8

class CSendInput
{
public:
	CSendInput(void);
	~CSendInput(void);

	BOOL CreateKeyboardInput(WORD wVK);

	void Send();

private:
	int	m_nInputNum;
	INPUT m_InputData[SI_INPUTBUFFERMAX];
};
