// SysSetUp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Pai1Pai.h"
#include "SysSetUp.h"
#include "afxdialogex.h"


// CSysSetUp �Ի���

IMPLEMENT_DYNAMIC(CSysSetUp, CDialogEx)

CSysSetUp::CSysSetUp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSysSetUp::IDD, pParent)
	, m_OperateSys(1)
	, m_Access_way(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	font.CreatePointFont(120, _T("΢���ź� Light")); 
}

CSysSetUp::~CSysSetUp()
{
}

void CSysSetUp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_OperateSys);
	DDX_Radio(pDX, IDC_RADIO3, m_Access_way);
}


BEGIN_MESSAGE_MAP(CSysSetUp, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSysSetUp::OnBnClickedOk)
END_MESSAGE_MAP()


// CSysSetUp ��Ϣ�������


void CSysSetUp::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	//CString str;
	//str.Format(_T("os:%d,aw:%d"),m_OperateSys,m_Access_way);
//	AfxMessageBox(str);
	CDialogEx::OnOK();
}
