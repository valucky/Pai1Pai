
// Pai1Pai.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPai1PaiApp:
// �йش����ʵ�֣������ Pai1Pai.cpp
//

class CPai1PaiApp : public CWinApp
{
public:
	CPai1PaiApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPai1PaiApp theApp;