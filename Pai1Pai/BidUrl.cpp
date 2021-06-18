// BidUrl.cpp : 实现文件
//

#include "stdafx.h"
#include "Pai1Pai.h"
#include "BidUrl.h"
#include "afxdialogex.h"


// CBidUrl 对话框

IMPLEMENT_DYNAMIC(CBidUrl, CDialogEx)

CBidUrl::CBidUrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBidUrl::IDD, pParent)
	, m_UrlOption(1)
	, m_BidUrl(_T(""))
{
	font.CreatePointFont(120, _T("微软雅黑 Light")); 
	//m_internettype = 0;
}

CBidUrl::~CBidUrl()
{
}

void CBidUrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_UrlOption);
	DDX_Text(pDX, IDC_EDIT1, m_BidUrl);
}


BEGIN_MESSAGE_MAP(CBidUrl, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBidUrl::OnBnClickedOk)
END_MESSAGE_MAP()


// CBidUrl 消息处理程序


BOOL CBidUrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CTime ttm = CTime::GetCurrentTime();

	if(m_internettype)
		m_BidUrl.Format(_T("https://paimai.alltobid.com/bid/%d%02d%02d01/login.htm"),ttm.GetYear(),ttm.GetMonth(),ttm.GetDay());
	else
		m_BidUrl.Format(_T("https://paimai2.alltobid.com/bid/%d%02d%02d01/login.htm"),ttm.GetYear(),ttm.GetMonth(),ttm.GetDay());

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CBidUrl::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_UrlOption)
		urlstr = m_BidUrl;
	else
		urlstr = _T("");

	CDialogEx::OnOK();
}
