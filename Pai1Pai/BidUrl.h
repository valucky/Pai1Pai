#pragma once


// CBidUrl �Ի���

class CBidUrl : public CDialogEx
{
	DECLARE_DYNAMIC(CBidUrl)

public:
	CBidUrl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBidUrl();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
