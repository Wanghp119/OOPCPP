// DisplayRSImage.h : DisplayRSImage Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDisplayRSImageApp:
// �йش����ʵ�֣������ DisplayRSImage.cpp
//

class CDisplayRSImageApp : public CWinApp
{
public:
	CDisplayRSImageApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	DECLARE_MESSAGE_MAP()
};

extern CDisplayRSImageApp theApp;