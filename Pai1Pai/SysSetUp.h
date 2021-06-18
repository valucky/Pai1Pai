#pragma once


// CSysSetUp 对话框

class CSysSetUp : public CDialogEx
{
	DECLARE_DYNAMIC(CSysSetUp)

public:
	CSysSetUp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysSetUp();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	HICON m_hIcon;
public:
	int m_OperateSys;
	int m_Access_way;
	afx_msg void OnBnClickedOk();
	CFont font;
};
