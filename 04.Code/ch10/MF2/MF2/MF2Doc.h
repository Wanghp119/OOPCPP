// MF2Doc.h : CMF2Doc ��Ľӿ�
//


#pragma once


class CMF2Doc : public CDocument
{
protected: // �������л�����
	CMF2Doc();
	DECLARE_DYNCREATE(CMF2Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CMF2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


