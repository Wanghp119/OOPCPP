// DisplayRSImageView.h : CDisplayRSImageView ��Ľӿ�
//


#pragma once


class CDisplayRSImageView : public CScrollView
{
protected: // �������л�����
	CDisplayRSImageView();
	DECLARE_DYNCREATE(CDisplayRSImageView)

	// ����
public:
	CDisplayRSImageDoc* GetDocument() const;

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
	virtual ~CDisplayRSImageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

/************************************************************************/
/* ���ڻ���ͼ��Ľӿں�����                                             */
/************************************************************************/
protected:
	void	DrawImage(CDC* pDC);			//����ͼ��
	void	DrawImgInfo(CDC* pDC);			//����ͼ����Ϣ
	void	ReadRaster();					//��ͼ�����ݣ�����
	bool	InitBuffer(double dRatio = 0.);	//��ʼ��λͼ����

protected:
	void*	m_pRBuff;			// R ���ε����ݣ����棩
	void*	m_pGBuff;			// G ���ε����ݣ����棩
	void*	m_pBBuff;			// B ���ε����ݣ����棩
	int		m_nBuffWidth;		// �����X Size��һ����ڴ��ڵĿ��
	int		m_nBuffHeight;		// �����Y size��һ����ڴ��ڵĸ߶�
	BYTE*	m_pbyRGB;			// λͼRGB���棬BIP���
	int		m_nRGBWidth;		// λͼ�Ŀ��
	int		m_nRGBHeight;		// λͼ�ĸ߶�
	double	m_dRatio;			// ��ʾ������ͼ�񴰿ڴ�С/����ֵ
	int		m_nRBandIdx;		// R��������
	int		m_nGBandIdx;		// G��������
	int		m_nBBandIdx;		// B��������
	BITMAP	m_bitmap;			// ������ʾ��λͼ����
	HBITMAP	m_hBitmap;			// �û���ʾ��λͼ���

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DisplayRSImageView.cpp �еĵ��԰汾
inline CDisplayRSImageDoc* CDisplayRSImageView::GetDocument() const
   { return reinterpret_cast<CDisplayRSImageDoc*>(m_pDocument); }
#endif

