// 7-5Doc.h : CMy75Doc ��Ľӿ�
//


#pragma once

class CShape;

class CMy75Doc : public CDocument
{
protected: // �������л�����
	CMy75Doc();
	DECLARE_DYNCREATE(CMy75Doc)

// ����
public:
	CShape**	m_ptShapeAry;
	int			m_nShapeCount;

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();

// ʵ��
public:
	virtual ~CMy75Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void OnShapeDisplay();

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


