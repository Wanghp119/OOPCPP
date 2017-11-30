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
	inline void SetDrawImage(CRSImage* pImage) {m_pDispImage = pImage;}

protected:
	void DrawImage(CDC* pDC, CRSImage* pImage);

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
	CRSImage*	m_pDispImage;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // RSProcView.cpp �еĵ��԰汾
inline CRSProcDoc* CRSProcView::GetDocument() const
   { return reinterpret_cast<CRSProcDoc*>(m_pDocument); }
#endif

