// 7-5Doc.cpp : CMy75Doc ���ʵ��
//

#include "stdafx.h"
#include "7-5.h"

#include "7-5Doc.h"

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy75Doc

IMPLEMENT_DYNCREATE(CMy75Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy75Doc, CDocument)
END_MESSAGE_MAP()


// CMy75Doc ����/����

CMy75Doc::CMy75Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CMy75Doc::~CMy75Doc()
{
}

BOOL CMy75Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMy75Doc ���л�

void CMy75Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMy75Doc ���

#ifdef _DEBUG
void CMy75Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy75Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy75Doc ����

void CMy75Doc::RemoveAllShape()
{
	list<CShape*>::iterator	iter;
	for (iter=m_lstShape.begin(); iter!=m_lstShape.end(); ++iter)
	{
		if ((*iter) != NULL)
			delete (*iter);
	}
	m_lstShape.clear();
}

void CMy75Doc::DeleteContents()
{
	RemoveAllShape();

	CDocument::DeleteContents();
}

BOOL CMy75Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
//	return CDocument::OnOpenDocument(lpszPathName);

	ifstream	ifs(lpszPathName, ios::in);
	if (!ifs.is_open())
		return FALSE;

	DeleteContents();
	SetModifiedFlag();

	CCircle*	pCircle = NULL;
	CRectangle*	pRect = NULL;
	CTriangle*	pTri = NULL;

	string		strLine;
	while(getline(ifs, strLine))
	{
		if (strLine.size() > 0)
		{
			stringstream	ss(strLine);

			// ������
			int		nShapeType;
			ss >> nShapeType;

			switch(nShapeType)
			{
			case 0:	//CIRCLE
				pCircle = new CCircle();
				ss >> (*pCircle);	//x,y,r
				m_lstShape.push_back(pCircle);
				break;
			case 1:	//Rectangle
				pRect = new CRectangle();
				ss >> (*pRect);	//x1,y1,x2,y2
				m_lstShape.push_back(pRect);
				break;
			case 2:	//Triangle
				pTri = new CTriangle();
				ss >> (*pTri);
				m_lstShape.push_back(pTri);
				break;
			default:
				break;
			}			
		}
	}

	ifs.close();

	SetModifiedFlag(FALSE);

	return TRUE;
}

BOOL CMy75Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
//	return CDocument::OnSaveDocument(lpszPathName);
	ofstream	ofs(lpszPathName, ios::out);
	if (!ofs.is_open())
		return FALSE;

	list<CShape*>::iterator	iter;
	CCircle*	pCircle;
	CRectangle*	pRect;
	CTriangle*	pTri;

	for (iter=m_lstShape.begin(); iter!=m_lstShape.end(); ++iter)
	{
		if ((pCircle = dynamic_cast<CCircle*>(*iter)))
			ofs << (*pCircle) << endl;
		else if ((pRect = dynamic_cast<CRectangle*>(*iter)))
			ofs << (*pRect) << endl;
		else if ((pTri = dynamic_cast<CTriangle*>(*iter)))
			ofs << (*pTri) << endl;
	}

	ofs.close();

	SetModifiedFlag(FALSE);

	return TRUE;
}
