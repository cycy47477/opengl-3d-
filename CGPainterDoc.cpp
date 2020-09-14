// CGPainterDoc.cpp : implementation of the CCGPainterDoc class
//

#include "stdafx.h"
#include "CGPainter.h"

#include "CGPainterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGPainterDoc

IMPLEMENT_DYNCREATE(CCGPainterDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGPainterDoc, CDocument)
	//{{AFX_MSG_MAP(CCGPainterDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGPainterDoc construction/destruction

CCGPainterDoc::CCGPainterDoc()
{
	// TODO: add one-time construction code here

}

CCGPainterDoc::~CCGPainterDoc()
{
}

BOOL CCGPainterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCGPainterDoc serialization

void CCGPainterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCGPainterDoc diagnostics

#ifdef _DEBUG
void CCGPainterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGPainterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGPainterDoc commands
