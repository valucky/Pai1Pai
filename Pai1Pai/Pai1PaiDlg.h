
// Pai1PaiDlg.h : ͷ�ļ�
//

#pragma once
#include "cwebbrowser2.h"


// CPai1PaiDlg �Ի���
class CPai1PaiDlg : public CDialogEx
{
// ����
public:
	CPai1PaiDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PAI1PAI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//COLORREF m_colorEditText; // edit�ؼ���������ɫ
  //COLORREF m_colorEditBK; // edit�ؼ��ı�����ɫ
  //  CBrush* m_pEditBkBrush;	
	CWebBrowser2 m_hupaiweb;
	CFont font,numfont;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void hwn2mat();
	afx_msg void OnBnClickedStart();
	bool startpp;
	bool confirmpp;
	
	int m_Begintime;
	int m_AddMoney;
	int m_ConfirmTime;
	int m_ConfirmS;

	int m_ms;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	void MouseLeftClick();
	void inputKey(int keydata);
	CWinThread* mythread;
	void Deal_Go(int deltaprice,int current_price);
	void Do_Final();
	void Write_Log(CString timestr,CString pricestr,int mode);
	char logfilename[255];
	FILE *flog;
	CString confirmpricestr;
	// ʱ��ѡ�0Ϊʹ����ҳʱ�䣬1Ϊʹ��ϵͳʱ��
	int m_timeoption;
	int m_PPOption;
	afx_msg void OnBnClickedFast();
	afx_msg void OnBnClickedSlow();
	afx_msg void OnBnClickedSelf();
	afx_msg void OnBnClickedAI();
	//BOOL m_adapt_price;
	afx_msg void OnBnClickedCheck2();
	BOOL m_Price_Check;
	BOOL m_Pre100;
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	void CreateDir();
	afx_msg void OnBnClickedButton2();
	int price_40s,price_45s,price_50s,price_55s;
	BOOL ppdone;   //final done
	int m_os;
	int m_access;
	afx_msg void OnBnClickedButton3();
	CString workpath;
};
