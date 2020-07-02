#include "stdafx.h"
#include "CMyEdit.h"

BEGIN_MESSAGE_MAP(CMyEdit,CEdit)
	ON_WM_PAINT()
END_MESSAGE_MAP()

CMyEdit::CMyEdit()
{

}

void CMyEdit::OnPaint()
{
	CRect rect;
	GetClientRect(&rect);
	OffsetRect(&rect, 0, 6);
	SendMessage(EM_SETRECT, 0, (LPARAM)&rect);
	CEdit::OnPaint();
}

BOOL CMyEdit::PreTranslateMessage(MSG* pMsg)
{
	CString rTemp;
	int nStartChar, nEndChar;

	if (pMsg->message == WM_CHAR)
	{
		if ((pMsg->wParam >= '0'&&pMsg->wParam <= '9')||pMsg->wParam==VK_DELETE||pMsg->wParam==VK_BACK)
		{
			GetWindowText(rTemp);
			if (rTemp.GetLength() == 3)
			{
				GetSel(nStartChar, nEndChar);
				if (nStartChar != nEndChar||pMsg->wParam == VK_DELETE||pMsg->wParam == VK_BACK)
				{
					return 0;
				}
				else
				{
					return 1;
				}
				
			}
			else
			{
				return 0;//应该派送
			}
		}
		else
		{
			return 1;//不应该派送
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}
