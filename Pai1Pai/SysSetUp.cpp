// SysSetUp.cpp : 实现文件
//

#include "stdafx.h"
#include "Pai1Pai.h"
#include "SysSetUp.h"
#include "afxdialogex.h"


// CSysSetUp 对话框

IMPLEMENT_DYNAMIC(CSysSetUp, CDialogEx)

CSysSetUp::CSysSetUp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSysSetUp::IDD, pParent)
	, m_OperateSys(1)
	, m_Access_way(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	font.CreatePointFont(120, _T("微软雅黑 Light")); 
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


// CSysSetUp 消息处理程序


void CSysSetUp::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	//CString str;
	//str.Format(_T("os:%d,aw:%d"),m_OperateSys,m_Access_way);
//	AfxMessageBox(str);
	CDialogEx::OnOK();
}
