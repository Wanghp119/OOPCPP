// MyAppView.h : CMyAppView ��Ľӿ�
//


#pragma once


class CMyAppView : public CView
{
protected: // �������л�����
	CMyAppView();
	DECLARE_DYNCREATE(CMyAppView)

// ����
public:
	CMyAppDoc* GetDocument() const;

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
	virtual ~CMyAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MyAppView.cpp �еĵ��԰汾
inline CMyAppDoc* CMyAppView::GetDocument() const
   { return reinterpret_cast<CMyAppDoc*>(m_pDocument); }
#endif

