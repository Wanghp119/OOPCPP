// MyAppDoc.h : CMyAppDoc ��Ľӿ�
//


#pragma once


class CMyAppDoc : public CDocument
{
protected: // �������л�����
	CMyAppDoc();
	DECLARE_DYNCREATE(CMyAppDoc)

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
	virtual ~CMyAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


