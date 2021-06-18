
// Pai1PaiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Pai1Pai.h"
#include "Pai1PaiDlg.h"
#include "afxdialogex.h"
#include <atlconv.h>
#include "BidUrl.h"
#include "SysSetUp.h"

extern void hwnd2mat(HWND hwnd,bool savefile);
extern bool Auto_Pos(HWND hwnd);

SYSTEMTIME stLocalbegin,stLocalend;


extern int cuprice ;
extern int cutime ;
extern int cuprice_range;
extern int m_os_type;
extern bool autopos;
extern int g_time_x ;
extern int g_time_y ;
extern char bmpname[255];
extern int beginxpos;
extern int beginypos;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
enum TimeID{
	GET_SYS_TIME,
	GET_WEB_TIME,
	DO_PAI_PAI,
	DO_ENTER_PRICE,
	FINISH_DONE
};

static int currentprice;   //全局变量，当前价格
static int Confirmprice;
//static int addmoney;    //全局变量，当前加价幅度      
static BYTE keymap[10] = {'0','1','2','3','4','5','6','7','8','9'};
static unsigned char scankey[10] = {0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69};

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPai1PaiDlg 对话框




CPai1PaiDlg::CPai1PaiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPai1PaiDlg::IDD, pParent)
	, m_Begintime(47)
	, m_AddMoney(800)
	, m_ConfirmTime(55)
	, m_ConfirmS(5)
	, m_timeoption(0)
	, m_PPOption(2)
	, m_Price_Check(FALSE)
	, m_Pre100(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//font.CreatePointFont(120, _T("微软雅黑 Light")); 
}

void CPai1PaiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_hupaiweb);
	DDX_Text(pDX, IDC_EDIT4, m_Begintime);
	DDX_Text(pDX, IDC_EDIT5, m_AddMoney);
	DDX_Text(pDX, IDC_EDIT6, m_ConfirmTime);
	DDX_CBIndex(pDX, IDC_COMBO1, m_ConfirmS);
	DDX_Radio(pDX, IDC_RADIO1, m_timeoption);
	DDX_Radio(pDX, IDC_RADIO3, m_PPOption);
	//	DDX_Check(pDX, IDC_CHECK2, m_adapt_price);
	DDX_Check(pDX, IDC_CHECK3, m_Price_Check);
	DDX_Check(pDX, IDC_CHECK4, m_Pre100);
}

BEGIN_MESSAGE_MAP(CPai1PaiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CPai1PaiDlg::OnBnClickedStart)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CPai1PaiDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CPai1PaiDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO3, &CPai1PaiDlg::OnBnClickedFast)
	ON_BN_CLICKED(IDC_RADIO4, &CPai1PaiDlg::OnBnClickedSlow)
	ON_BN_CLICKED(IDC_RADIO5, &CPai1PaiDlg::OnBnClickedSelf)
	ON_BN_CLICKED(IDC_RADIO6, &CPai1PaiDlg::OnBnClickedAI)
	ON_BN_CLICKED(IDC_CHECK3, &CPai1PaiDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CPai1PaiDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_BUTTON2, &CPai1PaiDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPai1PaiDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CPai1PaiDlg 消息处理程序

BOOL CPai1PaiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CSysSetUp sysdlg;

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	if(sysdlg.DoModal() == IDOK)
	{
		m_os = sysdlg.m_OperateSys;
		m_access = sysdlg.m_Access_way;
	}

	m_os_type = m_os;

	// TODO: 在此添加额外的初始化代码
	startpp = false;
	confirmpp = false;
	ppdone = false;
	flog = NULL;

	//CWnd *pWnd = GetTopWindow();  
	//while (NULL != pWnd)  
	//{  
	//	pWnd->SetFont(&font);  
	//	pWnd = pWnd->GetNextWindow();  
	//}

	CEdit *m_systime = (CEdit *)GetDlgItem(IDC_EDIT1);     //关联控件A
	CEdit *m_webtime = (CEdit *)GetDlgItem(IDC_EDIT2);     //关联控件A
	CEdit *m_curprice = (CEdit *)GetDlgItem(IDC_EDIT3);

	numfont.CreatePointFont(200, _T("微软雅黑"));     //选择字体

	m_systime->SetFont(&numfont);
	m_webtime->SetFont(&numfont);
	m_curprice->SetFont(&numfont);
	m_ms = 0;
	CreateDir();

	SetTimer(GET_SYS_TIME,100,NULL);

	COleVariant varEmpty;

	//CString str("http://moni.51hupai.com/");
//	CString str(_T("file:///.\\start\\CopyRight.htm"));
	CString str;
	str = _T("file:///") +workpath +_T("\\start\\CopyRight.htm");

	COleVariant varUrl(str);

	m_hupaiweb.Navigate2(varUrl,varEmpty, varEmpty,varEmpty, varEmpty);

	price_40s = price_45s = price_50s = price_55s = 0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPai1PaiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPai1PaiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPai1PaiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPai1PaiDlg::hwn2mat()
{
}

void CPai1PaiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 CString strsystime,strwebtime,strPrice,strPrice2;
	 SYSTEMTIME stLocal;
     CTime tm;
	 int shour,smin,ssec,sms;

	 switch(nIDEvent)
	 {
	 case GET_SYS_TIME:
		 {
			 ::GetLocalTime(&stLocal); 
			 //显示时间的间隔。
			 shour = stLocal.wHour;
			 smin = stLocal.wMinute;
			 ssec = stLocal.wSecond;
			 sms = stLocal.wMilliseconds/100;

			 strsystime.Format(_T("%02d:%02d:%02d.%d"),shour,smin,ssec,sms );

			 SetDlgItemText(IDC_EDIT1,strsystime);

			 ///////////////////用于跳价检测////////////////////
			 if((shour == 11) && (smin == 29 )&&( ssec == 40))
				 price_40s = cuprice;
			 if((shour == 11) && (smin == 29 )&&( ssec == 45))
				 price_45s = cuprice;
			 if((shour == 11) && (smin == 29 )&&( ssec == 50))
				 price_50s = cuprice;
			 if((shour == 11) && (smin == 29 )&&( ssec == 55))
				 price_55s = cuprice;
			 ////////////////////////////////////////////////////////
			  if((shour == 11) && (smin == 30 )&&( ssec == 3))
				  OnBnClickedStart();

			 if(m_timeoption == 1)
			 {
				 strPrice2.Format(_T("%d"),cuprice);
			//	 SetDlgItemText(IDC_EDIT3,strPrice);			

				 if(startpp)
				 {

					 if(confirmpp)
					 {
						 if(m_Pre100 && (Confirmprice == (cuprice + 400)))  //提前100出价
						 {
							 Write_Log(strsystime,strPrice2,2);
							 confirmpp =false;
							 hwnd2mat(this->GetDlgItem(IDC_EXPLORER1)->GetSafeHwnd(),true);
							 Do_Final();							 
						 }
						 else
						 {
							 if((shour == 11) && (smin == 29 )&&( ssec == m_ConfirmTime))
							 {
								 if(m_ConfirmS == sms)
								 {
									 Write_Log(strsystime,strPrice2,2);
									 confirmpp =false;
									 hwnd2mat(this->GetDlgItem(IDC_EXPLORER1)->GetSafeHwnd(),true);
									 Do_Final();
								 }
								 else
								 {								
									 Write_Log(strsystime,strPrice2,0);
								 }
							 }
							 else
								 Write_Log(strsystime,strPrice2,0);
						 }

					 }
					 else
					 {
						 // int start_time = 112900+m_Begintime;
						 if((shour == 11) && (smin == 29) && (ssec == m_Begintime) )
						 {
							 confirmpp = true;
							  Deal_Go(m_AddMoney,cuprice);
							  Write_Log(strsystime,strPrice2,1);
							
						 }
						 else
							 Write_Log(strsystime,strPrice2,0);
					 }
				 }
			 }
			 
			 break;		
		 }
	 case GET_WEB_TIME:
		 {
			 hwnd2mat(this->GetDlgItem(IDC_EXPLORER1)->GetSafeHwnd(),false);
			 int nowtime[6] = {0,0,0,0,0,0};

			 nowtime[0] = cutime/100000;
			 nowtime[1] = (cutime-nowtime[0]*100000)/10000;
			 nowtime[2] = (cutime-nowtime[0]*100000-nowtime[1]*10000)/1000;
			 nowtime[3] = (cutime-nowtime[0]*100000-nowtime[1]*10000-nowtime[2]*1000)/100;
			 nowtime[4] = (cutime-nowtime[0]*100000-nowtime[1]*10000-nowtime[2]*1000-nowtime[3]*100)/10;
			 nowtime[5] = (cutime-nowtime[0]*100000-nowtime[1]*10000-nowtime[2]*1000-nowtime[3]*100-nowtime[4]*10);

			 strwebtime.Format(_T("%d%d:%d%d:%d%d"),nowtime[0],nowtime[1],nowtime[2],nowtime[3],nowtime[4],nowtime[5]);

			 SetDlgItemText(IDC_EDIT2,strwebtime);

			 strPrice.Format(_T("%d"),cuprice);
			 SetDlgItemText(IDC_EDIT3,strPrice);	

			  ///////////////////用于跳价检测////////////////////
			 if(cutime == 112940)
				 price_40s = cuprice;
			 if(cutime == 112945)
				 price_45s = cuprice;
			 if(cutime == 112950)
			 {
				price_50s = cuprice;
				SetTimer(FINISH_DONE,15000,NULL);
			 }
			 if(cutime == 112955)
				 price_55s = cuprice;
			 /////////////////////////////////////////////////////

			 if(m_timeoption == 0)
			 {
				 if(startpp)
				 {
					 if(confirmpp)
					 {
						 if(m_Pre100 && (Confirmprice == (cuprice + 400)))  //提前100出价
						 {
							 Write_Log(strwebtime,strPrice,2);
							 confirmpp =false;
							 ppdone = true;
							 hwnd2mat(this->GetDlgItem(IDC_EXPLORER1)->GetSafeHwnd(),true);
							 Do_Final();						 		
						 }
						 else
						 {
						
							 if(m_ConfirmTime == (cutime-112900))
							 {
								 if(m_ConfirmS == m_ms)      //指定时间出价
								 {
									 if((Confirmprice - cuprice)>500 && (m_ConfirmTime < 57) && m_Price_Check)
									 {
										  Write_Log(strwebtime,strPrice,0);
										  if((Confirmprice - cuprice)>600)
										  {	  
											  m_ConfirmTime += 2;
											  m_ConfirmS = 0;
										  }
										  else
											  m_ConfirmTime +=1;
									
										  if(m_ConfirmTime > 57)
											  m_ConfirmTime =  57;
										  m_ms = 0;
										  UpdateData(FALSE);
									 }
									 else
									 {
										Write_Log(strwebtime,strPrice,2);
										confirmpp =false;
										ppdone = true;
										hwnd2mat(this->GetDlgItem(IDC_EXPLORER1)->GetSafeHwnd(),true);
										Do_Final();
									 }
							
								 }
								 else
								 {
									 m_ms ++;
									 Write_Log(strwebtime,strPrice,0);

								 }
							 }
							 else
								 Write_Log(strwebtime,strPrice,0);

							 if((cutime-112900)> m_ConfirmTime)  //如果发生跳秒，没检测到秒数，立即出价
							 {
								 Write_Log(strwebtime,strPrice,2);
								 confirmpp =false;
								 ppdone = true;
								 hwnd2mat(this->GetDlgItem(IDC_EXPLORER1)->GetSafeHwnd(),true);
								 Do_Final();	
							 }
						 }					 

					 }
					 else
					 {
						 // int start_time = 112900+m_Begintime;
						 if(m_Begintime == (cutime-112900))
						 {
							 confirmpp = true;
							 m_ms = 0;
							 Deal_Go(m_AddMoney,cuprice);
							 Write_Log(strwebtime,strPrice,1);
							 
						 }
						 else
							 Write_Log(strwebtime,strPrice,0);

						 if((cutime-112900)>m_Begintime && (ppdone ==false))   //如果发生跳秒，没检测到秒数，立即出价
						 {
							 confirmpp = true;
							 m_ms = 0;
							 Deal_Go(m_AddMoney,cuprice);
							 Write_Log(strwebtime,strPrice,1);
						 }
					 }
				 }
			 }
			 break;
		 }
	 case DO_ENTER_PRICE:
		 {
			 KillTimer(DO_ENTER_PRICE);
			 //MouseLeftClick();
			 mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
			 mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
			 break;
		
		 }
	 case FINISH_DONE:
		 {
			KillTimer(FINISH_DONE);
			OnBnClickedStart();
			break;
		 }
	 default: break;
	 
	 }
     //显示系统时间
	// if(nIDEvent == GET_SYS_TIME)
	// {
	//	 ::GetLocalTime(&stLocal); 
 //        //显示时间的间隔。
 //
	//      strsystime.Format(_T("%02d:%02d:%02d.%d"), stLocal.wHour, stLocal.wMinute, stLocal.wSecond,(stLocal.wMilliseconds/100));
	//	
	//	 SetDlgItemText(IDC_EDIT1,strsystime);
	///*	 if(startpp)
	//	 {
	//		 confirmpp = true;
	//		 if(m_Begintime == stLocal.wSecond)
	//		 {

	//		 }
	//		 startpp = false;
	//	 }
	//	 if(confirmpp)
	//	 {
	//		 if(( stLocal.wSecond== m_ConfirmTime) && (stLocal.wMilliseconds == m_ConfirmS*100)) 
	//		 {

	//		 }
	//	 }*/
	// }
	 /* if(nIDEvent == GET_WEB_TIME)
	 {
        hwnd2mat(this->GetDlgItem(IDC_EXPLORER1)->GetSafeHwnd(),false);
		int nowtime[6] = {0,0,0,0,0,0};

		nowtime[0] = cutime/100000;
		nowtime[1] = (cutime-nowtime[0]*100000)/10000;
		nowtime[2] = (cutime-nowtime[0]*100000-nowtime[1]*10000)/1000;
		nowtime[3] = (cutime-nowtime[0]*100000-nowtime[1]*10000-nowtime[2]*1000)/100;
		nowtime[4] = (cutime-nowtime[0]*100000-nowtime[1]*10000-nowtime[2]*1000-nowtime[3]*100)/10;
		nowtime[5] = (cutime-nowtime[0]*100000-nowtime[1]*10000-nowtime[2]*1000-nowtime[3]*100-nowtime[4]*10);

		strwebtime.Format(_T("%d%d:%d%d:%d%d"),nowtime[0],nowtime[1],nowtime[2],nowtime[3],nowtime[4],nowtime[5]);

		SetDlgItemText(IDC_EDIT2,strwebtime);

		strPrice.Format(_T("%d"),cuprice);
		SetDlgItemText(IDC_EDIT3,strPrice);
	 }*/
	  //if(nIDEvent == 5)
	  //{
		 // KillTimer(5);
		 // MouseLeftClick();
	  //}


	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CPai1PaiDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID()==IDC_EDIT1)
	{
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(0,255,0));
		hbr=(HBRUSH)GetStockObject(BLACK_BRUSH);
		//return hbr;
	}
	if (pWnd->GetDlgCtrlID()==IDC_EDIT2)
	{
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(255,0,0));
		hbr=(HBRUSH)GetStockObject(BLACK_BRUSH);
	//	return hbr;
	}

		if (pWnd->GetDlgCtrlID()==IDC_EDIT3)
	{
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(0x0b,0xc4,0xde));
		hbr=(HBRUSH)GetStockObject(BLACK_BRUSH);
	//	return hbr;
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

UINT PaiPaiThread(LPVOID pParam)
{
	CPai1PaiDlg *ppdlg = (CPai1PaiDlg *)pParam;

//	while(ppdlg->startpp)
	//{
		ppdlg->SetDlgItemTextW(IDOK,_T("停止拍牌"));		
		ppdlg->startpp = true;

//		SetTimer(ppdlg->GetSafeHwnd(),GET_WEB_TIME,500,NULL);	
	//}

	return true;

}



void CPai1PaiDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	UpdateData(TRUE);
	CTime begintm = CTime::GetCurrentTime();
	GetDlgItem(IDC_EXPLORER1)->SetForegroundWindow();
	if(startpp)
	{
		KillTimer(GET_WEB_TIME);
		this->SetDlgItemTextW(IDOK,_T("启动拍牌"));		
		startpp = false;
		confirmpp = false;
		ppdone = false;
		fclose(flog);
		flog = NULL;
		return;
	}
	else
	{
		//mythread = AfxBeginThread(PaiPaiThread,this,THREAD_PRIORITY_NORMAL,0,0);		
		memset(logfilename,0x00,255);
		memset(bmpname,0x00,255);
		sprintf(logfilename,".\\ppLog\\%d_%02d_%02d_%02d_%02d_%02d_Log.txt",begintm.GetYear(),begintm.GetMonth(),begintm.GetDay(),
			begintm.GetHour(),begintm.GetMinute(),begintm.GetSecond());
		//flog.Open(logfilename,CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone,NULL);
		flog = fopen(logfilename,"w+b");
		SetDlgItemTextW(IDOK,_T("停止拍牌"));		
		startpp = true;
    	SetTimer(GET_WEB_TIME,100,NULL);			
		return;
	}

	
}

void CPai1PaiDlg::MouseLeftClick()
{
	INPUT minput[2];
	ZeroMemory( &minput, sizeof(INPUT)*2);
	minput[0].type=INPUT_MOUSE;
	minput[0].mi.dx=0;
	minput[0].mi.dy=0;
	minput[0].mi.mouseData=0;
	minput[0].mi.dwFlags=MOUSEEVENTF_LEFTDOWN;

	minput[1].type=INPUT_MOUSE;
	minput[1].mi.dx=0;
	minput[1].mi.dy=0;
	minput[1].mi.mouseData=0;
	minput[1].mi.dwFlags=MOUSEEVENTF_LEFTUP;

	SendInput( 2, minput, sizeof(INPUT) );
}

void CPai1PaiDlg::inputKey(int keydata)
{

	//::SetForegroundWindow(hWnd);//把接收窗口放在最前，同时使窗口获取焦点（好吧，说的像android，获取焦点。。。）
	INPUT keyEvent;
	memset(&keyEvent, 0,  sizeof(INPUT));
	
	keyEvent.type = INPUT_KEYBOARD;//如果是鼠标设置鼠标的INPUT_MOUSE
	keyEvent.ki.wVk = keymap[keydata];//字符A
	keyEvent.ki.wScan = MapVirtualKey(scankey[keydata], MAPVK_VK_TO_VSC);
	SendInput(1, &keyEvent, sizeof(keyEvent));
//	Sleep(200); 
	//keyEvent[1].type = INPUT_KEYBOARD;//如果是鼠标设置鼠标的INPUT_MOUSE
	//keyEvent[1].ki.wVk = keymap[keydata];//字符A
	//keyEvent[1].ki.wScan = MapVirtualKey(scankey[keydata], MAPVK_VK_TO_VSC);
	keyEvent.ki.dwFlags = KEYEVENTF_KEYUP;//默认keyEvent.ki.dwFlags  = 0 ，即 KEYEVENTF_KEYDOWN
	SendInput(1, &keyEvent, sizeof(keyEvent));
}


void CPai1PaiDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	//font.DeleteObject();  
	KillTimer(GET_SYS_TIME);
	if(flog != NULL)
		fclose(flog);
	//if(flog.m_hFile != NULL)
	//	flog.Close();

	// TODO: 在此处添加消息处理程序代码
}


void CPai1PaiDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
		CDialogEx::OnCancel();

}


void CPai1PaiDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	COleVariant varEmpty;

	CString str("http://moni.51hupai.com/");

	COleVariant varUrl(str);

	m_hupaiweb.Navigate2(varUrl,varEmpty, varEmpty,varEmpty, varEmpty);
	
//	UpdateData(TRUE);

//	int current_confirm_price = cuprice + m_AddMoney;
//
//	int nowprice[6] = {0,0,0,0,0,0};
//
//	if(current_confirm_price > 100000)
//	{
//		nowprice[0] = current_confirm_price/100000;
//	}
//
//	nowprice[1] = (current_confirm_price - nowprice[0]*100000)/10000;
//	nowprice[2] = (current_confirm_price - nowprice[0]*100000-nowprice[1]*10000)/1000;
//	nowprice[3] =  (current_confirm_price - nowprice[0]*100000-nowprice[1]*10000 - nowprice[2]*1000)/100;
//	nowprice[4] = 0;
//	nowprice[5] = 0;
//
//
//	RECT rcIE;
//	CWnd *hwndie;
//	hwndie = this->GetDlgItem(IDC_EXPLORER1);
//
//	hwndie->GetClientRect(&rcIE);
//
//
//
//	//ScreenToClient(&rcIE);
//	ClientToScreen(&rcIE);
////	SetCursorPos(rcIE.left+760,rcIE.top+320);   //加价坐标
//	SetCursorPos(rcIE.left+720,rcIE.top+420);    //直接输价格坐标
//	////////先双击加价框，删除前一次输入价格////////////
//	MouseLeftClick();
//	//Sleep(100);
//	MouseLeftClick();
//	
//	
//	//mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
//	//mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
//	//mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
//	//mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
//	keybd_event(VK_DELETE,MapVirtualKey(46, MAPVK_VK_TO_VSC) , 0, 0);
//	keybd_event(VK_DELETE,MapVirtualKey(46, MAPVK_VK_TO_VSC) , KEYEVENTF_KEYUP, 0);
//	Sleep(100);
//
//
//
//
//
//	if(nowprice[0] >0)
//	{
//		keybd_event(keymap[nowprice[0]],MapVirtualKey(scankey[nowprice[0]], MAPVK_VK_TO_VSC) , 0, 0);	
//		keybd_event(keymap[nowprice[0]],MapVirtualKey(scankey[nowprice[0]], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
//		Sleep(100);
//		//inputKey(nowprice[0]);
//
//	}
////	ASCII
//
//	/*PostMessageA(hwndie->GetSafeHwnd(),WM_KEYDOWN,keymap[nowprice[1]],MAKELPARAM(keymap[nowprice[1]],WM_KEYDOWN) );
//	PostMessageA(hwndie->GetSafeHwnd(),WM_CHAR,keymap[nowprice[1]],MAKELPARAM(keymap[nowprice[1]],WM_KEYDOWN) );
//	PostMessageA(hwndie->GetSafeHwnd(),WM_KEYUP,keymap[nowprice[1]],MAKELPARAM(keymap[nowprice[1]],WM_KEYUP) );
//
//	PostMessageA(hwndie->GetSafeHwnd(),WM_KEYDOWN,keymap[nowprice[2]],MAKELPARAM(keymap[nowprice[2]],WM_KEYDOWN) );
//	PostMessageA(hwndie->GetSafeHwnd(),WM_CHAR,keymap[nowprice[2]],MAKELPARAM(keymap[nowprice[2]],WM_KEYDOWN) );
//	PostMessageA(hwndie->GetSafeHwnd(),WM_KEYUP,keymap[nowprice[2]],MAKELPARAM(keymap[nowprice[2]],WM_KEYUP) );
//
//	PostMessageA(hwndie->GetSafeHwnd(),WM_KEYDOWN,keymap[nowprice[3]],MAKELPARAM(keymap[nowprice[3]],WM_KEYDOWN) );
//	PostMessageA(hwndie->GetSafeHwnd(),WM_CHAR,keymap[nowprice[3]],MAKELPARAM(keymap[nowprice[3]],WM_KEYDOWN) );
//	PostMessageA(hwndie->GetSafeHwnd(),WM_KEYUP,keymap[nowprice[3]],MAKELPARAM(keymap[nowprice[3]],WM_KEYUP) );
//
//	PostMessageA(hwndie->GetSafeHwnd(),WM_KEYDOWN,keymap[nowprice[4]],MAKELPARAM(keymap[nowprice[4]],WM_KEYDOWN) );
//	PostMessageA(hwndie->GetSafeHwnd(),WM_CHAR,keymap[nowprice[4]],MAKELPARAM(keymap[nowprice[4]],WM_KEYDOWN) );
//	PostMessageA(hwndie->GetSafeHwnd(),WM_KEYUP,keymap[nowprice[4]],MAKELPARAM(keymap[nowprice[4]],WM_KEYUP) );
//
//	PostMessageA(hwndie->GetSafeHwnd(),WM_KEYDOWN,keymap[nowprice[5]],MAKELPARAM(keymap[nowprice[5]],WM_KEYDOWN) );
//	PostMessageA(hwndie->GetSafeHwnd(),WM_CHAR,keymap[nowprice[5]],MAKELPARAM(keymap[nowprice[5]],WM_KEYDOWN) );
//	PostMessageA(hwndie->GetSafeHwnd(),WM_KEYUP,keymap[nowprice[5]],MAKELPARAM(keymap[nowprice[5]],WM_KEYUP) );*/
//	//for(int nn = 1;nn<6;nn++)
//	//	inputKey(nowprice[nn]);
//	
//	keybd_event(keymap[nowprice[1]],MapVirtualKey(scankey[nowprice[1]], MAPVK_VK_TO_VSC), 0, 0);//Sleep(100);	
//	keybd_event(keymap[nowprice[1]],MapVirtualKey(scankey[nowprice[1]], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
//	//Sleep(200);
//	
//	keybd_event(keymap[nowprice[2]],MapVirtualKey(scankey[nowprice[2]], MAPVK_VK_TO_VSC), 0, 0);	//Sleep(100);
//	keybd_event(keymap[nowprice[2]],MapVirtualKey(scankey[nowprice[2]], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
//	//Sleep(200);
//	
//	keybd_event(keymap[nowprice[3]],MapVirtualKey(scankey[nowprice[3]], MAPVK_VK_TO_VSC), 0, 0);	//Sleep(100);
//	keybd_event(keymap[nowprice[3]],MapVirtualKey(scankey[nowprice[3]], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
//	//Sleep(200);
//	
//	keybd_event('0',MapVirtualKey(scankey[0], MAPVK_VK_TO_VSC),0,0);//Sleep(100);
//	keybd_event('0',MapVirtualKey(scankey[0], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
////	Sleep(200);
//	
//	keybd_event('0',MapVirtualKey(scankey[0], MAPVK_VK_TO_VSC),0,0);//Sleep(100);
//	keybd_event('0',MapVirtualKey(scankey[0], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
//	//Sleep(200);
//
//	//MouseLeftClick();
//
////	keybd_event(0x0d,MapVirtualKey(0x0d, MAPVK_VK_TO_VSC),0,0);//Sleep(100);
////	keybd_event(0x0d,MapVirtualKey(0x0d, MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
//
////	::GetLocalTime(&stLocalend);
//
////	SetCursorPos(rcIE.left+840,rcIE.top+320);  //点击加价按钮
////	Sleep(1000);	
////	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
////	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
//
////	 ::GetLocalTime(&stLocalbegin);
////	CString strt;
//
////	strt.Format(_T("%02d:%02d:%02d.%03d\r\n %02d:%02d:%02d.%03d"),stLocalbegin.wHour,stLocalbegin.wMinute,stLocalbegin.wSecond,stLocalbegin.wMilliseconds,\
////		stLocalend.wHour,stLocalend.wMinute,stLocalend.wSecond,stLocalend.wMilliseconds);
//
////	SetDlgItemText(IDC_STATIC_INFO,strt);
//
//	//Sleep(1000);
//	SetCursorPos(rcIE.left+840,rcIE.top+425);  //点击出价按钮
//	SetTimer(5,500,NULL);
//	//::SendMessage(hwndie->GetSafeHwnd(),WM_MOUSEMOVE,NULL,MAKELPARAM(rcIE.left+840,rcIE.top+425));
//	//::SendMessage(hwndie->GetSafeHwnd(),WM_LBUTTONDBLCLK,NULL,MAKELPARAM(rcIE.left+840,rcIE.top+425));
////	Sleep(1500);
////	MouseLeftClick();
////	
//	//mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
//
//	//mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
	

}

void CPai1PaiDlg::Deal_Go(int deltaprice,int current_price)
{
//	UpdateData(TRUE);
	
	int current_confirm_price = current_price + deltaprice;
	Confirmprice = current_confirm_price;//加价赋给全局变量

	int nowprice[6] = {0,0,0,0,0,0};

	if(current_confirm_price > 100000)
	{
		nowprice[0] = current_confirm_price/100000;
	}

	nowprice[1] = (current_confirm_price - nowprice[0]*100000)/10000;
	nowprice[2] = (current_confirm_price - nowprice[0]*100000-nowprice[1]*10000)/1000;
	nowprice[3] =  (current_confirm_price - nowprice[0]*100000-nowprice[1]*10000 - nowprice[2]*1000)/100;
	nowprice[4] = 0;
	nowprice[5] = 0;


	RECT rcIE;
	CWnd *hwndie;
	hwndie = this->GetDlgItem(IDC_EXPLORER1);

	hwndie->GetClientRect(&rcIE);

	
	ClientToScreen(&rcIE);

	//SetCursorPos(rcIE.left+720,rcIE.top+420);    //直接输价格坐标
	SetCursorPos(rcIE.left+g_time_x + 560,rcIE.top+g_time_y +20);
	////////先双击加价框，删除前一次输入价格////////////
	//MouseLeftClick();
	//MouseLeftClick();
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
			
	keybd_event(VK_DELETE,MapVirtualKey(46, MAPVK_VK_TO_VSC) , 0, 0);
	keybd_event(VK_DELETE,MapVirtualKey(46, MAPVK_VK_TO_VSC) , KEYEVENTF_KEYUP, 0);
	Sleep(100);

	
	if(nowprice[0] >0)
	{
		keybd_event(keymap[nowprice[0]],MapVirtualKey(scankey[nowprice[0]], MAPVK_VK_TO_VSC) , 0, 0);	
		keybd_event(keymap[nowprice[0]],MapVirtualKey(scankey[nowprice[0]], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
	//	Sleep(100);
	}
	
	keybd_event(keymap[nowprice[1]],MapVirtualKey(scankey[nowprice[1]], MAPVK_VK_TO_VSC), 0, 0);//Sleep(100);	
	keybd_event(keymap[nowprice[1]],MapVirtualKey(scankey[nowprice[1]], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
	//Sleep(200);
	
	keybd_event(keymap[nowprice[2]],MapVirtualKey(scankey[nowprice[2]], MAPVK_VK_TO_VSC), 0, 0);	//Sleep(100);
	keybd_event(keymap[nowprice[2]],MapVirtualKey(scankey[nowprice[2]], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
	//Sleep(200);
	
	keybd_event(keymap[nowprice[3]],MapVirtualKey(scankey[nowprice[3]], MAPVK_VK_TO_VSC), 0, 0);	//Sleep(100);
	keybd_event(keymap[nowprice[3]],MapVirtualKey(scankey[nowprice[3]], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
	//Sleep(200);
	
	keybd_event('0',MapVirtualKey(scankey[0], MAPVK_VK_TO_VSC),0,0);//Sleep(100);
	keybd_event('0',MapVirtualKey(scankey[0], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
//	Sleep(200);
	
	keybd_event('0',MapVirtualKey(scankey[0], MAPVK_VK_TO_VSC),0,0);//Sleep(100);
	keybd_event('0',MapVirtualKey(scankey[0], MAPVK_VK_TO_VSC),KEYEVENTF_KEYUP,0);
	//Sleep(200);

	
	//SetCursorPos(rcIE.left+840,rcIE.top+425);  //点击出价按钮
	SetCursorPos(rcIE.left+g_time_x + 680,rcIE.top+g_time_y +25);
	//CString ttt;
	//ttt.Format(_T("%d   %d  "),g_time_x + 680,g_time_y +25);
	//AfxMessageBox(ttt);

	SetTimer(DO_ENTER_PRICE,500,NULL);
	///https://paimai2.alltobid.com/bid/9bd249c65299488bae01938568a5a178/login.htm
	

}

void CPai1PaiDlg::Do_Final()
{
	RECT rcIE;
	CWnd *hwndie;
	hwndie = this->GetDlgItem(IDC_EXPLORER1);

	hwndie->GetClientRect(&rcIE);


	ClientToScreen(&rcIE);

//	SetCursorPos(rcIE.left+590,rcIE.top+510);    //直接输价格坐标
	SetCursorPos(rcIE.left+g_time_x + 430,rcIE.top + g_time_y +110);
		
	//MouseLeftClick();
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);//点下左键
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//松开左键
}

void CPai1PaiDlg::Write_Log(CString timestr,CString pricestr,int mode)///mode:0,nomal,1,addprice ,2,confirmprice
{
	USES_CONVERSION;
	CString writestr;
	CString tmp;
	switch(mode)
	{
	case 0:{
		writestr = timestr + L"\t\t" + pricestr + L"\r\n";
		break;
		   }
	case 1:{
		tmp.Format(L"%d",(cuprice + m_AddMoney));
		confirmpricestr = tmp;
		writestr = timestr + L"@@" + pricestr + L"@@Price\t" + tmp + L"\r\n";	;
			break;
		   }
	case 2:{
		writestr = timestr + L"@@" + pricestr + L"@@Confirm\t" + confirmpricestr + L"\r\n";	;
		break;
		   }
	default:break;
	}

	
	fwrite(W2A(writestr),1,writestr.GetLength(),flog);
}




void CPai1PaiDlg::OnBnClickedFast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PPOption = 0;
	m_Begintime = 48;
	m_AddMoney = 600;
	m_ConfirmTime = 57;
	m_ConfirmS = 0;
	//if(m_Price_Check == TRUE)
	//	m_Price_Check = TRUE;
	//else
	//	m_Price_Check = FALSE;
	//if(m_Pre100 == TRUE)
	//	m_Pre100 = TRUE;
	//else
	//	m_Pre100 = false;

	UpdateData(FALSE);
}


void CPai1PaiDlg::OnBnClickedSlow()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PPOption = 1;
	m_Begintime = 45;
	m_AddMoney = 1000;
	m_ConfirmTime = 55;
	m_ConfirmS = 5;
	//if(m_Price_Check == TRUE)
	//	m_Price_Check = TRUE;
	//else
	//	m_Price_Check = FALSE;
	//if(m_Pre100 == TRUE)
	//	m_Pre100 = TRUE;
	//else
	//	m_Pre100 = false;
	UpdateData(FALSE);
}


void CPai1PaiDlg::OnBnClickedSelf()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PPOption = 2;
	m_Begintime = 47;
	m_AddMoney = 800;
	m_ConfirmTime = 55;
	m_ConfirmS = 5;
	//if(m_Price_Check == TRUE)
	//	m_Price_Check = TRUE;
	//else
	//	m_Price_Check = FALSE;
	//if(m_Pre100 == TRUE)
	//	m_Pre100 = TRUE;
	//else
	//	m_Pre100 = false;
	UpdateData(FALSE);
}


void CPai1PaiDlg::OnBnClickedAI()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PPOption = 3;
	m_Begintime = 0;
	m_AddMoney = 0;
	m_ConfirmTime = 0;
	m_ConfirmS = 0;
	/*if(m_Price_Check == TRUE)
		m_Price_Check = TRUE;
	else
		m_Price_Check = FALSE;
	if(m_Pre100 == TRUE)
		m_Pre100 = TRUE;
	else
		m_Pre100 = false;*/
	UpdateData(FALSE);
	AfxMessageBox(_T("敬请期待！"));
}





void CPai1PaiDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_Price_Check == TRUE)
		m_Price_Check = FALSE;
	else
		m_Price_Check = TRUE;
	UpdateData(FALSE);
}


void CPai1PaiDlg::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_Pre100 == TRUE)
		m_Pre100 = FALSE;
	else
		m_Pre100 = TRUE;
	UpdateData(FALSE);
}

void CPai1PaiDlg::CreateDir()
{
	CString strPath;
	GetModuleFileName(NULL,strPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	strPath.ReleaseBuffer();
	
	int pos = strPath.ReverseFind('\\');
	strPath = strPath.Left(pos);
	CString strLogPath;
	workpath = strPath;
	strLogPath = strPath + L"\\ppLog";
	if (!PathIsDirectory(strLogPath))
	{	
		CreateDirectory(strLogPath,0);
	}

}





void CPai1PaiDlg::OnBnClickedButton2()//国拍实战
{
	
	COleVariant varEmpty;

	CString str;
	CBidUrl bidurldlg;
	bidurldlg.m_internettype = m_access;
	if(bidurldlg.DoModal()==IDOK)
		str = bidurldlg.urlstr;
	COleVariant varUrl(str);

	m_hupaiweb.Navigate2(varUrl,varEmpty, varEmpty,varEmpty, varEmpty);
}

//UINT AutoThread(LPVOID pParam)
//{
//	CPai1PaiDlg *ppdlg = (CPai1PaiDlg *)pParam;
//
//
//	if(Auto_Pos(ppdlg->GetDlgItem(IDC_EXPLORER1)->GetSafeHwnd()))
//	{
//		AfxMessageBox(_T("自动校准成功"),0,NULL);
//
//	}
//
//	return true;
//
//}


void CPai1PaiDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	beginxpos = 150;
	beginypos = 390;
	if(Auto_Pos(this->GetDlgItem(IDC_EXPLORER1)->GetSafeHwnd()))
	{
		AfxMessageBox(_T("自动校准成功"));

	}
	else
	{
		beginxpos  = 120;
		beginypos = 220;
		if(Auto_Pos(this->GetDlgItem(IDC_EXPLORER1)->GetSafeHwnd()))
		{
			AfxMessageBox(_T("自动校准成功"));

		}
		else
			AfxMessageBox(_T("自动校准失败！！请联系作者！"));
	}
	//AfxBeginThread(AutoThread,0,0,0,0);
	
}
