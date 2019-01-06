#pragma once

class AFX_EXT_CLASS CKBHook
{
public:
	CKBHook(void);
	~CKBHook(void);

	BOOL Set(void);
	void Unset(void);

	BYTE *GetKeySetPtr(void);

private:
	static LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);

private:
	static HHOOK m_hHook;
	static BOOL m_bDiamondON;
	static BOOL m_bNT4;
	static BYTE m_byKey[16];
};
