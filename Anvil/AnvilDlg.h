
// ForgeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "CMyEdit.h"

// CAnvilDlg �Ի���
class CAnvilDlg : public CDialogEx
{
// ����
public:
	CAnvilDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FORGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCbnSelchangeCbAction1();
	afx_msg void OnCbnSelchangeCbAction2();
	afx_msg void OnCbnSelchangeCbAction3();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtCalculate();
	afx_msg void OnBnClickedBtCaculForgePoint();
	afx_msg void OnCbnSelchangeCbAction33();
	afx_msg void OnBnClickedCleantozero();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_CBAction3;
	CComboBox m_CBAction2;
	CComboBox m_CBAction1;

	CStatic m_Picture3;
	CStatic m_Picture2;
	CStatic m_Picture1;
	CBitmap m_Bitmap1;
	CBitmap m_Bitmap2;
	CBitmap m_Bitmap3;

	CMyEdit m_ETTarget;
	CMyEdit m_ETCalShrink;
	CMyEdit m_ETCalUpset;
	CMyEdit m_ETCalBend;
	CMyEdit m_ETCalPunch;
	CMyEdit m_ETCalHitlight;
	CMyEdit m_ETCalHitmedium;
	CMyEdit m_ETCalHitheavy;
	CMyEdit m_ETCalDraw;
		
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnStnClickedStaForgerule();
	afx_msg void OnEnChangeEtPunch();
};
