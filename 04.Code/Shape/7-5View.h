// 7-5View.h : CMy75View ��Ľӿ�
//


#pragma once

class CShape;

class CMy75View : public CView
{
protected: // �������л�����
	CMy75View();
	DECLARE_DYNCREATE(CMy75View)

// ����
public:
	CMy75Doc* GetDocument() const;

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
	virtual ~CMy75View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShapeDisplay();
	afx_msg void OnShapeTest();
	afx_msg void OnInitUpdate();
};

#ifndef _DEBUG  // 7-5View.cpp �еĵ��԰汾
inline CMy75Doc* CMy75View::GetDocument() const
   { return reinterpret_cast<CMy75Doc*>(m_pDocument); }
#endif

