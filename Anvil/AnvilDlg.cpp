
// ForgeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Anvil.h"
#include "AnvilDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <vector>
#include <string>
using namespace std;
//index define
// 0 ���(HITLIGHT) 1 ����(HITMEDIUM) 2 �ػ�(HITHEAVY) 3 ǣ��(DRAW)  4��ѹ(PUNCH) 5 ����(BEND) 6 煶�(UPSET) 7 ����(SHRINK)
#define INDEX_HITLIGHT  0
#define INDEX_HITMEDIUM 1
#define INDEX_HITHEAVY  2
#define INDEX_DRAW      3
#define INDEX_PUNCH     4
#define INDEX_BEND      5
#define INDEX_UPSET     6
#define INDEX_SHRINK     7

//path define
#define PATH_FORWARD TRUE
#define PATH_BACK    FALSE
#ifdef UNICODE
#define TSTRING wstring
#else
#define TSTRING string
#endif // UNICODE
struct Action
{
	int iIndex;
	int value;
	BOOL path;
	TSTRING name;
};
struct ACTIONCOUT
{
	int iThirteenCount;
	int iSevenCount;
	int iTwoCount;
	bool bCan;
};

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAnvilDlg �Ի���



CAnvilDlg::CAnvilDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAnvilDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnvilDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_ACTION3, m_CBAction3);
	DDX_Control(pDX, IDC_CB_ACTION2, m_CBAction2);
	DDX_Control(pDX, IDC_CB_ACTION1, m_CBAction1);
	DDX_Control(pDX, IDC_PICTURE3, m_Picture3);
	DDX_Control(pDX, IDC_PICTURE2, m_Picture2);
	DDX_Control(pDX, IDC_PICTURE1, m_Picture1);
	DDX_Control(pDX, IDC_ET_TARGET, m_ETTarget);
	DDX_Control(pDX, IDC_ET_SHRINK, m_ETCalShrink);
	DDX_Control(pDX, IDC_ET_UPSET, m_ETCalUpset);
	DDX_Control(pDX, IDC_ET_BEND, m_ETCalBend);
	DDX_Control(pDX, IDC_ET_PUNCH, m_ETCalPunch);
	DDX_Control(pDX, IDC_ET_HITLIGHT, m_ETCalHitlight);
	DDX_Control(pDX, IDC_ET_HITMEDIUM, m_ETCalHitmedium);
	DDX_Control(pDX, IDC_ET_HITHEAVY, m_ETCalHitheavy);
	DDX_Control(pDX, IDC_ET_DRAW, m_ETCalDraw);
}

BEGIN_MESSAGE_MAP(CAnvilDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BT_CALCULATE, &CAnvilDlg::OnBnClickedBtCalculate)
	ON_BN_CLICKED(IDC_BT_CACULTARGET, &CAnvilDlg::OnBnClickedBtCaculForgePoint)
	ON_CBN_SELCHANGE(IDC_CB_ACTION3, &CAnvilDlg::OnCbnSelchangeCbAction3)
	ON_CBN_SELCHANGE(IDC_CB_ACTION2, &CAnvilDlg::OnCbnSelchangeCbAction2)
	ON_CBN_SELCHANGE(IDC_CB_ACTION1, &CAnvilDlg::OnCbnSelchangeCbAction1)
	ON_BN_CLICKED(IDC_CLEANTOZERO, &CAnvilDlg::OnBnClickedCleantozero)
	ON_WM_CLOSE()
	ON_STN_CLICKED(IDC_STA_FORGERULE, &CAnvilDlg::OnStnClickedStaForgerule)
END_MESSAGE_MAP()


// CAnvilDlg ��Ϣ�������

BOOL CAnvilDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	CenterWindow();
	SetWindowText(_T("TerraFirmaCraft Anvil Solver              by louk78"));
	ShowWindow(SW_SHOW);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CRect rect;
	m_Bitmap1.LoadBitmap(IDB_HITLIGHT);
	m_Bitmap2.LoadBitmap(IDB_HITLIGHT);
	m_Bitmap3.LoadBitmap(IDB_HITLIGHT);


	TCHAR chActionText[9][20] = { _T("Hit Light"), _T("Hit Medium"), _T("Hit Heavy"), _T("Draw"),_T("Punch"), _T("Bend"), _T("Upset"), _T("Shrink"),_T("None") };
	
	m_CBAction1.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_CBAction1.MoveWindow(rect.left, rect.top, 110, 230);

	m_CBAction2.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_CBAction2.MoveWindow(rect.left, rect.top, 110, 230);

	m_CBAction3.GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_CBAction3.MoveWindow(rect.left, rect.top, 110, 230);

	for (int i = 0; i < 9; i++)
	{
		m_CBAction1.InsertString(i, chActionText[i]);
		m_CBAction2.InsertString(i, chActionText[i]);
		m_CBAction3.InsertString(i, chActionText[i]);
	}
	
	m_CBAction1.SetCurSel(0);
	m_CBAction2.SetCurSel(0);
	m_CBAction3.SetCurSel(0);

	GetDlgItem(IDC_ET_SHRINK)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_UPSET)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_BEND)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_PUNCH)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_HITLIGHT)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_HITMEDIUM)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_HITHEAVY)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_DRAW)->SetWindowText(_T("0"));



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAnvilDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAnvilDlg::OnPaint()
{
	m_Picture1.SetBitmap(m_Bitmap1);
	m_Picture2.SetBitmap(m_Bitmap2);
	m_Picture3.SetBitmap(m_Bitmap3);
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������


		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAnvilDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAnvilDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO:  �ڴ˴������Ϣ����������


}


void CAnvilDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������


}


ACTIONCOUT CalculateNeedAction(int data)
{
	int iRemainer;
	int iMaxMultiple;
	ACTIONCOUT actioncout;
	actioncout.iThirteenCount = 0;
	actioncout.iSevenCount = 0;
	actioncout.iTwoCount = 0;
	actioncout.bCan = false;
	if (data < 13)
	{

		if (data >= 7)
		{
			if (!((data - 7) % 2))
			{
				actioncout.iSevenCount = 1;
				actioncout.iTwoCount = (data - 7) / 2;
				actioncout.bCan = true;
			}
		}
		else
		{
			if (!data % 2)
			{
				actioncout.iTwoCount = data / 2;
				actioncout.bCan = true;
			}
		}
		return actioncout;

	}
	iMaxMultiple = data / 13;//26+9=35
	for (int iMul = iMaxMultiple; iMul > 0; iMul--)
	{
		iRemainer = data - 13 * iMul;//9= data-13*2,data
		if (iRemainer == 0)
		{
			actioncout.iThirteenCount = iMul;
			actioncout.bCan = true;
			break;
		}
		if (iRemainer >= 2 && iRemainer <= 8)
		{
			if (!(iRemainer % 2))
			{
				actioncout.iThirteenCount = iMul;
				actioncout.iTwoCount = iRemainer / 2;
				actioncout.bCan = true;
				break;
			}
		}
		else
		{
			if (!(iRemainer % 7))
			{
				actioncout.iThirteenCount = iMul;
				actioncout.iSevenCount = iRemainer / 7;
				actioncout.bCan = true;
				break;
			}
			else
			{
				//���磺(9-2)%7=0 (11-2)%7=2 
				if (!(((iRemainer - 2) % 7) % 2))
				{
					actioncout.iThirteenCount = iMul;
					actioncout.iSevenCount = iRemainer / 7;
					actioncout.iTwoCount = (iRemainer % 7) / 2;
					actioncout.bCan = true;
					break;
				}
			}


		}


	}
	return actioncout;

}
void CAnvilDlg::OnBnClickedBtCalculate()
{
	//�����ı����
	TCHAR chActionText[9][20] = { _T("Hit Light"), _T("Hit Medium"), _T("Hit Heavy"), _T("Draw"),_T("Punch"), _T("Bend"), _T("Upset"), _T("Shrink"),_T("None") };
	//����ֵ���
	int  iActionVal[9] = { 3, 6, 9, 15, 2, 7, 13, 16 ,0};


	vector<Action> vctAction;
	typedef vector<Action> VCTACTION;
	typedef vector<Action> ::value_type VCTACTION_TYPE;
	Action action;
	int iComboBox1Sel, iComboBox2Sel, iComboBox3Sel;
	int iForgePoint;
	int iFinalCoordinate;
	CString csResult;




	for (int i = 0; i < 9; i++)
	{
		action.iIndex  = i;
		action.value = iActionVal[i];
		if (i < 4)action.path = PATH_BACK;
		else action.path = PATH_FORWARD;
		action.name = chActionText[i];
		vctAction.push_back(VCTACTION_TYPE(action));

	}
	

	UpdateData(TRUE);
	iComboBox1Sel = m_CBAction1.GetCurSel();
	iComboBox2Sel = m_CBAction2.GetCurSel();
	iComboBox3Sel = m_CBAction3.GetCurSel();
	CString csTemp;
	GetDlgItem(IDC_ET_TARGET)->GetWindowText(csTemp);
	iForgePoint = _ttoi(csTemp.GetBuffer());

	VCTACTION::iterator iter;
	for (iter = vctAction.begin(); iter != vctAction.end(); ++iter)
	{
		if (iComboBox1Sel == iter->iIndex)
		{
			if (iter->path == PATH_BACK)
			{
				iForgePoint += iter->value;
			}
			else
			{
				iForgePoint -= iter->value;
			}
		}
		if (iComboBox2Sel == iter->iIndex)
		{
			if (iter->path == PATH_BACK)
			{
				iForgePoint += iter->value;
			}
			else
			{
				iForgePoint -= iter->value;
			}
		}
		if (iComboBox3Sel == iter->iIndex)
		{
			if (iter->path == PATH_BACK)
			{
				iForgePoint += iter->value;
			}
			else
			{
				iForgePoint -= iter->value;
			}
		}
	}

	iFinalCoordinate = iForgePoint;
	// 0 ��� 1 ���� 2 �ػ� 3 ǣ�� 4��ѹ 5 ���� 6 煶� 7 ����
	//��� ���� �ػ� ǣ�� Ϊ���� -
	//��� ���� 煶� ���� Ϊǰ�� +
	//  ��� = 1.5��ѹ = 3
	//	���� = 3  ��ѹ = 6
	//	�ػ� = 4.5��ѹ = 9
	//	ǣ�� = 7.5��ѹ = 15
	//  ��ѹ =         = 2
	//	���� = 3.5��ѹ = 7
	//	��� = 6.5��ѹ = 13
	//	���� = 8  ��ѹ = 16
	//2 7 13 [2,7,13,9,15,20]
	int iRemainer;
	int iMaxMultiple;
	ACTIONCOUT actioncout;

	iMaxMultiple = iFinalCoordinate / 16;//99
	for (int iMul = iMaxMultiple; iMul > 0; iMul--)
	{
		iRemainer = iFinalCoordinate - iMul * 16;//35 = data -4*16
		if (iRemainer == 0)
		{
			csResult.Format(_T("%dShrink"), iMul);
			break;
		}
		else
		{
			actioncout = CalculateNeedAction(iRemainer);
			if (actioncout.bCan)
			{
				csResult.Format(_T("%dShrink "), iMul);
				csTemp = "";
				if (actioncout.iThirteenCount != 0)
				{
					csTemp.Format(_T("%dUpset "), actioncout.iThirteenCount);
					csResult += csTemp;
					csTemp = "";
				}
				if (actioncout.iSevenCount != 0)
				{
					csTemp.Format(_T("%dBend "), actioncout.iSevenCount);
					csResult += csTemp;
					csTemp = "";
				}
				if (actioncout.iTwoCount != 0)
				{
					csTemp.Format(_T("%dPunch"), actioncout.iTwoCount);
					csResult += csTemp;
					csTemp = "";
				}
				break;

			}

		}
	}

	GetDlgItem(IDC_ET_FORMULA)->SetWindowText(csResult.GetBuffer());

}



void CAnvilDlg::OnBnClickedBtCaculForgePoint()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int iCalShrink = 0, iCalUpset = 0, iCalBend = 0, iCalPunch = 0;
	int iCalHitlight = 0, iCalHitmedium = 0, iCalHitheavy = 0, iCalDraw = 0;
	CString rTemp;
	int iForgePoint = 0;
	CString csCoordinate;

	GetDlgItem(IDC_ET_SHRINK)->GetWindowText(rTemp);
	iCalShrink = _ttoi(rTemp.GetBuffer());
	GetDlgItem(IDC_ET_UPSET)->GetWindowText(rTemp);
	iCalUpset = _ttoi(rTemp.GetBuffer());
	GetDlgItem(IDC_ET_BEND)->GetWindowText(rTemp);
	iCalBend = _ttoi(rTemp.GetBuffer());
	GetDlgItem(IDC_ET_PUNCH)->GetWindowText(rTemp);
	iCalPunch = _ttoi(rTemp.GetBuffer());

	GetDlgItem(IDC_ET_HITLIGHT)->GetWindowText(rTemp);
	iCalHitlight = _ttoi(rTemp.GetBuffer());
	GetDlgItem(IDC_ET_HITMEDIUM)->GetWindowText(rTemp);
	iCalHitmedium = _ttoi(rTemp.GetBuffer());
	GetDlgItem(IDC_ET_HITHEAVY)->GetWindowText(rTemp);
	iCalHitheavy = _ttoi(rTemp.GetBuffer());
	GetDlgItem(IDC_ET_DRAW)->GetWindowText(rTemp);
	iCalDraw = _ttoi(rTemp.GetBuffer());

		if (iCalShrink)
		{
			iForgePoint += iCalShrink * 16;
		}
		if (iCalUpset)
		{
			iForgePoint += iCalUpset * 13;
		}
		if (iCalBend)
		{
			iForgePoint += iCalBend * 7;
		}
		if (iCalPunch)
		{
			iForgePoint += iCalPunch * 2;
		}
		if (iCalHitlight)
		{
			iForgePoint -= iCalHitlight * 3;
		}
		if (iCalHitmedium)
		{
			iForgePoint -= iCalHitmedium * 6;
		}
		if (iCalHitheavy)
		{
			iForgePoint -= iCalHitheavy * 9;
		}
		if (iCalDraw)
		{
			iForgePoint -= iCalDraw * 15;
		}
		if (iForgePoint > 150)
		{
			MessageBox(_T("Sorry��Out of Range"));
			return;
		}
		csCoordinate.Format(_T("%d"), iForgePoint);
		GetDlgItem(IDC_ET_COORDINATE)->SetWindowText(csCoordinate);


}


void CAnvilDlg::OnCbnSelchangeCbAction1()
{
	int iCurSel;
	iCurSel = m_CBAction1.GetCurSel();
	// 0 ��� 1 ���� 2 �ػ� 3 ǣ�� 4��ѹ 5 ���� 6 煶� 7 ����
	m_Bitmap1.DeleteObject();
	switch (iCurSel)
	{
		case 0:
			m_Bitmap1.LoadBitmap(IDB_HITLIGHT);
			break;
		case 1:
			m_Bitmap1.LoadBitmap(IDB_HITMEDIUM);
			break;
		case 2:
			m_Bitmap1.LoadBitmap(IDB_HITHEAVY);
			break;
		case 3:
			m_Bitmap1.LoadBitmap(IDB_DRAW);
			break;
		case 4:
			m_Bitmap1.LoadBitmap(IDB_PAUCH);
			break;
		case 5:
			m_Bitmap1.LoadBitmap(IDB_BEND);
			break;
		case 6:
			m_Bitmap1.LoadBitmap(IDB_UPSET);
			break;
		case 7:
			m_Bitmap1.LoadBitmap(IDB_SHRINK);
			break;
		default:break;

	}
	RedrawWindow();
}
void CAnvilDlg::OnCbnSelchangeCbAction2()
{
	int iCurSel;
	iCurSel = m_CBAction2.GetCurSel();
	// 0 ��� 1 ���� 2 �ػ� 3 ǣ�� 4 ���� 5 煶� 6 ����
	m_Bitmap2.DeleteObject();
	switch (iCurSel)
	{
		case 0:
			m_Bitmap2.LoadBitmap(IDB_HITLIGHT);
			break;
		case 1:
			m_Bitmap2.LoadBitmap(IDB_HITMEDIUM);
			break;
		case 2:
			m_Bitmap2.LoadBitmap(IDB_HITHEAVY);
			break;
		case 3:
			m_Bitmap2.LoadBitmap(IDB_DRAW);
			break;
		case 4:
			m_Bitmap2.LoadBitmap(IDB_PAUCH);
			break;
		case 5:
			m_Bitmap2.LoadBitmap(IDB_BEND);
			break;
		case 6:
			m_Bitmap2.LoadBitmap(IDB_UPSET);
			break;
		case 7:
			m_Bitmap2.LoadBitmap(IDB_SHRINK);
			break;
		default:break;

	}
	RedrawWindow();
}
void CAnvilDlg::OnCbnSelchangeCbAction3()
{
	int iCurSel;
	iCurSel = m_CBAction3.GetCurSel();
	m_Bitmap3.DeleteObject();
	switch (iCurSel)
	{
		case 0:
			m_Bitmap3.LoadBitmap(IDB_HITLIGHT);
			break;
		case 1:
			m_Bitmap3.LoadBitmap(IDB_HITMEDIUM);
			break;
		case 2:
			m_Bitmap3.LoadBitmap(IDB_HITHEAVY);
			break;
		case 3:
			m_Bitmap3.LoadBitmap(IDB_DRAW);
			break;
		case 4:
			m_Bitmap3.LoadBitmap(IDB_PAUCH);
			break;
		case 5:
			m_Bitmap3.LoadBitmap(IDB_BEND);
			break;
		case 6:
			m_Bitmap3.LoadBitmap(IDB_UPSET);
			break;
		case 7:
			m_Bitmap3.LoadBitmap(IDB_SHRINK);
			break;
		default:break;
	}
	RedrawWindow();
}


void CAnvilDlg::OnBnClickedCleantozero()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_ET_SHRINK)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_UPSET)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_BEND)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_PUNCH)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_HITLIGHT)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_HITMEDIUM)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_HITHEAVY)->SetWindowText(_T("0"));
	GetDlgItem(IDC_ET_DRAW)->SetWindowText(_T("0"));

}


void CAnvilDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialogEx::OnCancel();
}


void CAnvilDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnCancel();

}


void CAnvilDlg::OnStnClickedStaForgerule()
{
	// TODO: Add your control notification handler code here
}
