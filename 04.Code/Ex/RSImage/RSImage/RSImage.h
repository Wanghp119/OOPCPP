// RSImage.h : RSImage Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CRSImageApp:
// �йش����ʵ�֣������ RSImage.cpp
//

class CRSImageApp : public CWinApp
{
public:
	CRSImageApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRSImageApp theApp;