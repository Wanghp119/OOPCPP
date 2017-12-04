// RSProcView.h : CRSProcView ��Ľӿ�
//


#pragma once


class CRSProcView : public CView
{
protected: // �������л�����
	CRSProcView();
	DECLARE_DYNCREATE(CRSProcView)

// ����
public:
	CRSProcDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CRSProcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // RSProcView.cpp �еĵ��԰汾
inline CRSProcDoc* CRSProcView::GetDocument() const
   { return reinterpret_cast<CRSProcDoc*>(m_pDocument); }
#endif

