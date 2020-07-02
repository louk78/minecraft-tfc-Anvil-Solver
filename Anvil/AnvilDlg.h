
// ForgeDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "CMyEdit.h"

// CAnvilDlg 对话框
class CAnvilDlg : public CDialogEx
{
// 构造
public:
	CAnvilDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FORGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
