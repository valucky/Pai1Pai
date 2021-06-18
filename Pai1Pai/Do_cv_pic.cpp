#include "stdafx.h"


#define _AFXDLL//为了方便是用mfc类    
#include<afxwin.h>  
#include<cv.h>    
#include<highgui.h>    
#include<stdio.h>    
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
#include <conio.h>
#include <Windows.h>
#include <shlguid.h>
using namespace cv;  
using namespace std;  
#define WINDOW_NAME "51沪牌模拟拍牌系统 - Internet Explorer"    
  
void crop_predit();  
void on_Threshold( int, void* );  
void on_setROI( int, void* );  
//void hwnd2mat();  
void predit(Mat noImg);  
void putNo(Rect rc);  
  
int m_os_type=0;
int cuprice = 0;
int cutime = 0;
int cuprice_range = 0;
int price =0;
Point minLoc,strPoint;  
Size strSize;  
Mat screenImg,imgROI,image,timeImg;  
int g_nThresholdValue = 165;  
int g_nThresholdType = 1;  
int g_roi_x = 188;  
int g_roi_y = 416;  
int g_roi_width = 43;  
int g_roi_height = 14;  
int g_time_x = 161;
int g_time_y = 400;
int g_time_w = 66; 
int g_time_h = 14;
Mat g_srcImage, g_grayImage, g_dstImage;  
int sWidth=43;    
int sHeight=14;  
char myWindowsTitle[256];
char bmpname[255];
bool autopos = false;
int beginxpos,beginypos;
//CString webtim,currentprice;
/*void drawText(Mat & image);


int _tmain(int argc, _TCHAR* argv[])
{
	

    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat image;
    VideoCapture capture;
    capture.open(0);
    if(capture.isOpened())
    {
        cout << "Capture is opened" << endl;
        for(;;)
        {
            capture >> image;
            if(image.empty())
                break;
            drawText(image);
            imshow("Sample", image);
            if(waitKey(10) >= 0)
                break;
        }
    }
    else
    {
        cout << "No capture" << endl;
        image = Mat::zeros(480, 640, CV_8UC1);
        drawText(image);
        imshow("Sample", image);
        waitKey(0);
    }
    return 0;
}

void drawText(Mat & image)
{
    putText(image, "Hello OpenCV",
            Point(20, 50),
            FONT_HERSHEY_COMPLEX, 1, // font face and scale
            Scalar(255, 255, 255), // white
            1, LINE_AA); // line thickness and type
}
*/



struct con{
    double x,y;                    //轮廓位置
    int order;                      //轮廓向量contours中的第几个

    bool operator<(con &m){                //from left to right , resolve win7 number 4 
        if(x > m.x) return false;    
        else  if( x == m.x){
            if(y < m.y) return true;
            else return false;
        }                           
        else return true;
    }

	//bool operator<(con &m){          //from top to bottom
	//	if(y > m.y) return false;    
	//	else  if( y == m.y){
	//		if(x < m.x) return true;
	//		else return false;
	//	}                           
	//	else return true;
	//}

}con[15];

struct result{
    double bi;
    int num;

    bool operator<(result &m){
        if(bi < m.bi)return true;
        else return false;
    }
}result[15];

Mat num[15];
Mat sample;
void deal(Mat &src,int order);
double compare(Mat &src, Mat &sample);
void Threshold(Mat &src,Mat &sample,int m);

void Threshold(Mat &src, Mat &sample, int m)
{
	cvtColor(sample, sample, COLOR_BGR2GRAY);
	threshold(sample, sample, 128, 255, CV_THRESH_BINARY_INV);
	//imshow("test",sample);
	result[m].bi = compare(src, sample);
	result[m].num = m;
}

void deal(Mat &src, int order)
{
	if(m_os_type)      //////////windows 10
	{
		sample = imread(".\\sample10\\0.png");
		Threshold(src, sample, 0);

		sample = imread(".\\sample10\\1.png");
		Threshold(src, sample, 1);

		sample = imread(".\\sample10\\2.png");
		Threshold(src, sample, 2);

		sample = imread(".\\sample10\\3.png");
		Threshold(src, sample, 3);

		sample = imread(".\\sample10\\4.png");
		Threshold(src, sample, 4);

		sample = imread(".\\sample10\\5.png");
		Threshold(src, sample, 5);

		sample = imread(".\\sample10\\6.png");
		Threshold(src, sample, 6);

		sample = imread(".\\sample10\\7.png");
		Threshold(src, sample, 7);

		sample = imread(".\\sample10\\8.png");
		Threshold(src, sample, 8);

		sample = imread(".\\sample10\\9.png");
		Threshold(src, sample, 9);

		sample = imread(".\\sample10\\s1.png");
		Threshold(src, sample, 10);

	}
	else     ///////windowss 7
	{
		sample = imread(".\\sample7\\0.png");
		Threshold(src, sample, 0);

		sample = imread(".\\sample7\\1.png");
		Threshold(src, sample, 1);

		sample = imread(".\\sample7\\2.png");
		Threshold(src, sample, 2);

		sample = imread(".\\sample7\\3.png");
		Threshold(src, sample, 3);

		sample = imread(".\\sample7\\4.png");
		Threshold(src, sample, 4);

		sample = imread(".\\sample7\\5.png");
		Threshold(src, sample, 5);

		sample = imread(".\\sample7\\6.png");
		Threshold(src, sample, 6);

		sample = imread(".\\sample7\\7.png");
		Threshold(src, sample, 7);

		sample = imread(".\\sample7\\8.png");
		Threshold(src, sample, 8);

		sample = imread(".\\sample7\\9.png");
		Threshold(src, sample, 9);

		sample = imread(".\\sample7\\s1.png");
		Threshold(src, sample, 10);

	}
	

	sort(result, result + 11);

	if ((result[10].bi > 0.6) && (result[10].num <10))
	{
		price = price * 10 + result[10].num;
		//    cout << "第" << order << "个数字为 "<< result[9]. num<<endl;
		//    cout << "识别精度为 " << result[9].bi <<endl;
	}
	else if (result[10].num == 10)
	{
		//	 cout << price <<endl;
		//	 price = 0;		
		//	cout << "第" << order << "位为 :"<<endl;
	}
	else
		cout << "第" << order << "个数字无法识别" << endl;
}

double compare(Mat &src, Mat &sample)
{
	double same = 0.0, difPoint = 0.0;
	Mat now;
	resize(sample, now, src.size());
	int row = now.rows;
	int col = now.cols *  now.channels();
	for (int i = 0; i < 1; i++){
		uchar * data1 = src.ptr<uchar>(i);
		uchar * data2 = now.ptr<uchar>(i);
		for (int j = 0; j < row * col; j++){
			int  a = data1[j];
			int b = data2[j];
			if (a == b)same++;
			else difPoint++;
		}
	}
	return same / (same + difPoint);
}



void do_time(Mat srcImage)
{
	//cutime = cuprice = 0;
	Mat dstImage, grayImage, Image, sImg;
	double fScale = 5;      //缩放倍数  
	CvSize czSize;              //目标图像尺寸  

	
	srcImage.copyTo(dstImage);
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	threshold(grayImage, Image, 128, 255, CV_THRESH_BINARY_INV);
	//Mat dstImage, grayImage, Image; 
	/*vector<Mat> contours(100);
	Mat hierarchy;
	findContours(Image,contours,hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE );*/
	vector<vector<Point>> contours;

	vector<Vec4i> hierarchy;
	findContours(Image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	int i = 0;
	Point2f pp[12][18];
	vector<vector<Point>>::iterator It;
//	vector<Mat>::iterator It;
	Rect rect[15];
	for (It = contours.begin(); It < contours.end(); It++)
	{                        //画出可包围数字的最小矩形
		Point2f vertex[4];
		rect[i] = boundingRect(*It);
		vertex[0] = rect[i].tl();                                                           //矩阵左上角的点
		vertex[1].x = (float)rect[i].tl().x, vertex[1].y = (float)rect[i].br().y;           //矩阵左下方的点
		vertex[2] = rect[i].br();                                                           //矩阵右下角的点
		vertex[3].x = (float)rect[i].br().x, vertex[3].y = (float)rect[i].tl().y;           //矩阵右上方的点

		for (int j = 0; j < 4; j++)
			line(dstImage, vertex[j], vertex[(j + 1) % 4], Scalar(0, 0, 255), 1);

		con[i].x = (vertex[0].x + vertex[1].x + vertex[2].x + vertex[3].x) / 4.0;                  //根据中心点判断图像的位置
		con[i].y = (vertex[0].y + vertex[1].y + vertex[2].y + vertex[3].y) / 4.0;
		con[i].order = i;
		i++;
	}
	sort(con, con + i);

	for (int j = 0; j < i; j++){
		int k = con[j].order;
		dstImage(rect[k]).copyTo(num[j]);
		cvtColor(num[j], num[j], COLOR_BGR2GRAY);
		threshold(num[j], num[j], 128, 255, CV_THRESH_BINARY_INV);
		
		deal(num[j], j + 1);
	}

	if (i > 9)
		cutime = price; 
	else
		cuprice =  price;

	price = 0;
}



//(CWnd* pWnd)
void hwnd2mat(HWND hwnd,bool savefile){  
  
	//	HWND hwnd =  pWnd->GetSafeHwnd();
	//pwnd = GetActiveWindow();

	//  RECT rect;  
    //::GetWindowRect(hwnd, &rect);  

    HDC hwindowDC,hwindowCompatibleDC;  
  
    int height,width,srcheight,srcwidth;  
    HBITMAP hbwindow;  
    Mat src;  
    BITMAPINFOHEADER  bi;  

	//hwindowDC= GetWindowDC(hwnd);
  
    hwindowDC=GetDC(hwnd);  
    hwindowCompatibleDC=CreateCompatibleDC(hwindowDC);  
    SetStretchBltMode(hwindowCompatibleDC,COLORONCOLOR);    
  
    RECT windowsize;    // get the height and width of the screen  
    GetClientRect(hwnd, &windowsize); 
	//GetWindowRect(hwnd,&windowsize);
  
    srcheight = windowsize.bottom;  
    srcwidth = windowsize.right;  
    height = windowsize.bottom;  //change this to whatever size you want to resize to  
    width = windowsize.right;  
  
    src.create(height,width,CV_8UC4);  
  
    // create a bitmap  
    hbwindow = CreateCompatibleBitmap( hwindowDC, width, height);  
    bi.biSize = sizeof(BITMAPINFOHEADER);     
    bi.biWidth = width;      
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not  
    bi.biPlanes = 1;      
    bi.biBitCount = 32;      
    bi.biCompression = BI_RGB;      
    bi.biSizeImage = 0;    
    bi.biXPelsPerMeter = 0;      
    bi.biYPelsPerMeter = 0;      
    bi.biClrUsed = 0;      
    bi.biClrImportant = 0;  
  
    // use the previously created device context with the bitmap  
    SelectObject(hwindowCompatibleDC, hbwindow);  
    // copy from the window device context to the bitmap device context  
    StretchBlt( hwindowCompatibleDC, 0,0, width, height, hwindowDC, 0, 0,srcwidth,srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !  
    GetDIBits(hwindowCompatibleDC,hbwindow,0,height,src.data,(BITMAPINFO *)&bi,DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow  
  
	//if(savefile)
	//{
	//	fi = fopen("test.bmp","w+b");
	//	fwrite(&bi,1,bi.biSize,fi);
	//	fwrite(src.data,1,height*width,fi);
	//	fclose(fi);
	//}
    // avoid memory leak,非常重要，特别是实时提取需要循环时，不添加会使内存消耗至full，并使程序卡死  
    DeleteObject (hbwindow); 
	DeleteDC(hwindowCompatibleDC); 
	ReleaseDC(hwnd, hwindowDC);  
	//imshow("test",src);
	if(savefile)
		{
			CTime tt = CTime::GetCurrentTime();
			sprintf(bmpname,".\\ppLog\\%d_%02d_%02d_%02d_%02d_%02d_Confirm.bmp",tt.GetYear(),tt.GetMonth(),tt.GetDay(),
				tt.GetHour(),tt.GetMinute(),tt.GetSecond());
			imwrite(bmpname,src);
			return;
	}
	
		screenImg=src(Rect(g_roi_x,g_roi_y,g_roi_width,g_roi_height));//通过GetDIBits将数据流从Bitmap copy到Mat  
		//imshow("test",screenImg);
		//waitKey();
		do_time(screenImg);
		timeImg = src(Rect(g_time_x,g_time_y,g_time_w,g_time_h));
	//	imshow("test",timeImg);
	//	waitKey();
		do_time(timeImg);
	    
}

bool Auto_Pos(HWND hwnd){  

	HDC hwindowDC,hwindowCompatibleDC;  

	int height,width,srcheight,srcwidth;  
	HBITMAP hbwindow;  
	Mat src;  
	BITMAPINFOHEADER  bi;  
	int posx,posy;

	char kstr[255];

	//hwindowDC= GetWindowDC(hwnd);

	hwindowDC=GetDC(hwnd);  
	hwindowCompatibleDC=CreateCompatibleDC(hwindowDC);  
	SetStretchBltMode(hwindowCompatibleDC,COLORONCOLOR);    

	RECT windowsize;    // get the height and width of the screen  
	GetClientRect(hwnd, &windowsize); 
	//GetWindowRect(hwnd,&windowsize);

	srcheight = windowsize.bottom;  
	srcwidth = windowsize.right;  
	height = windowsize.bottom;  //change this to whatever size you want to resize to  
	width = windowsize.right;  

	src.create(height,width,CV_8UC4);  

	// create a bitmap  
	hbwindow = CreateCompatibleBitmap( hwindowDC, width, height);  
	bi.biSize = sizeof(BITMAPINFOHEADER);     
	bi.biWidth = width;      
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not  
	bi.biPlanes = 1;      
	bi.biBitCount = 32;      
	bi.biCompression = BI_RGB;      
	bi.biSizeImage = 0;    
	bi.biXPelsPerMeter = 0;      
	bi.biYPelsPerMeter = 0;      
	bi.biClrUsed = 0;      
	bi.biClrImportant = 0;  

	// use the previously created device context with the bitmap  
	SelectObject(hwindowCompatibleDC, hbwindow);  
	// copy from the window device context to the bitmap device context  
	StretchBlt( hwindowCompatibleDC, 0,0, width, height, hwindowDC, 0, 0,srcwidth,srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !  
	GetDIBits(hwindowCompatibleDC,hbwindow,0,height,src.data,(BITMAPINFO *)&bi,DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow  

	// avoid memory leak,非常重要，特别是实时提取需要循环时，不添加会使内存消耗至full，并使程序卡死  
	DeleteObject (hbwindow); 
	DeleteDC(hwindowCompatibleDC); 
	ReleaseDC(hwnd, hwindowDC);  
	//imshow("test",src);


	for(posx = 150;posx < 180;posx ++)
	{
		for(posy = 390;posy < 430;posy ++)
		{
			g_dstImage = src(Rect(posx,posy,16,12));
			do_time(g_dstImage);
			if(cuprice == 10 || cuprice == 11)
			{
				if(m_os_type == 0)
					posy -=1;
				g_time_x = posx;
				g_time_y = posy;
				g_roi_x = posx+27;
				g_roi_y = posy+16;
				memset(kstr,0x00,255);
				sprintf(kstr,"time_x = %d   time_y = %d   roi_x = %d    roi_y = %d",g_time_x,g_time_y,g_roi_x,g_roi_y);
				AfxMessageBox(CString(kstr),0,NULL);
				autopos = true;
				return true;
			}
		}

	}

	return false;

}