// MyApp.h : MyApp Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyAppApp:
// �йش����ʵ�֣������ MyApp.cpp
//

class CMyAppApp : public CWinApp
{
public:
	CMyAppApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew1();
	DECLARE_MESSAGE_MAP()
};

extern CMyAppApp theApp;