#pragma once


// CBidUrl 对话框

class CBidUrl : public CDialogEx
{
	DECLARE_DYNAMIC(CBidUrl)

public:
	CBidUrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBidUrl();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_UrlOption;
	CString m_BidUrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString urlstr;
	CFont font;
	int m_internettype;
};
