// BidUrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Pai1Pai.h"
#include "BidUrl.h"
#include "afxdialogex.h"


// CBidUrl �Ի���

IMPLEMENT_DYNAMIC(CBidUrl, CDialogEx)

CBidUrl::CBidUrl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBidUrl::IDD, pParent)
	, m_UrlOption(1)
	, m_BidUrl(_T(""))
{
	font.CreatePointFont(120, _T("΢���ź� Light")); 
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


// CBidUrl ��Ϣ�������


BOOL CBidUrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CTime ttm = CTime::GetCurrentTime();

	if(m_internettype)
		m_BidUrl.Format(_T("https://paimai.alltobid.com/bid/%d%02d%02d01/login.htm"),ttm.GetYear(),ttm.GetMonth(),ttm.GetDay());
	else
		m_BidUrl.Format(_T("https://paimai2.alltobid.com/bid/%d%02d%02d01/login.htm"),ttm.GetYear(),ttm.GetMonth(),ttm.GetDay());

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CBidUrl::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_UrlOption)
		urlstr = m_BidUrl;
	else
		urlstr = _T("");

	CDialogEx::OnOK();
}
