// MF2View.h : CMF2View ��Ľӿ�
//


#pragma once


class CMF2View : public CView
{
protected: // �������л�����
	CMF2View();
	DECLARE_DYNCREATE(CMF2View)

// ����
public:
	CMF2Doc* GetDocument() const;

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
	virtual ~CMF2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MF2View.cpp �еĵ��԰汾
inline CMF2Doc* CMF2View::GetDocument() const
   { return reinterpret_cast<CMF2Doc*>(m_pDocument); }
#endif

