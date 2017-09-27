// RSImageView.h : CRSImageView ��Ľӿ�
//


#pragma once

#include "RSImageDef.h"

class CRSImageView : public CView
{
protected: // �������л�����
	CRSImageView();
	DECLARE_DYNCREATE(CRSImageView)

// ����
public:
	CRSImageDoc* GetDocument() const;
	double GetDispRate() const {return m_dDispRate;}
	
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CRSImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	double	m_dDispRate;	//��ʾ����
	int		m_iX0, m_iY0;	//ͼ��ƫ�Ƶ�λ��
	int		m_iRasXSize, m_iRasYSize;
	void*	m_ptrRedBuff;
	void*	m_ptrGrnBuff;
	void*	m_ptrBluBuff;
	int		m_nXBuffSize;
	int		m_nYBuffSize;
	int		m_nRgbList[3];

	BITMAP	m_oBitmap;
	BYTE*	m_ptRGBBitmap;
	int		m_nBitmapWidth;
	int		m_nBitmapHeight;

	eDispType	m_eDispType;	//��ʾ����
	eEnhanceStyle	m_eEnhanceStyle;	//��ǿ��ʽ

	bool InitDispPara();	//��ʼ����ʾ����	
	bool InitDispBuffer();	//2. ��ʼ����ʾ����	
	bool GenDispBitmap();	//3. ������ʾλͼ
	void DrawRaster(CDC* pDC);

	void ReleaseBuff();

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // RSImageView.cpp �еĵ��԰汾
inline CRSImageDoc* CRSImageView::GetDocument() const
   { return reinterpret_cast<CRSImageDoc*>(m_pDocument); }
#endif

