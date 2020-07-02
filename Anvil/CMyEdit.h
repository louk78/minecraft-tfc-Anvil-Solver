#pragma once
#include "afxwin.h"

class CMyEdit :public CEdit
{
	
public:
	CMyEdit();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};