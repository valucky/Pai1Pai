#pragma once


// CSysSetUp �Ի���

class CSysSetUp : public CDialogEx
{
	DECLARE_DYNAMIC(CSysSetUp)

public:
	CSysSetUp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysSetUp();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

protected:
	HICON m_hIcon;
public:
	int m_OperateSys;
	int m_Access_way;
	afx_msg void OnBnClickedOk();
	CFont font;
};
