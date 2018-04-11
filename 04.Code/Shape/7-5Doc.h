// 7-5Doc.h : CMy75Doc ��Ľӿ�
//


#pragma once

#include <list>
#include <memory>
using namespace std;

class CShape;

class CMy75Doc : public CDocument
{
protected: // �������л�����
	CMy75Doc();
	DECLARE_DYNCREATE(CMy75Doc)

// ����
public:
	list<CShape*>	m_lstShape;

// ����
public:
	void	RemoveAllShape();

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
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

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


