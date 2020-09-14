// CGPainterDoc.h : interface of the CCGPainterDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGPAINTERDOC_H__E5ECD4E4_E240_40C1_8101_531C4E2969D0__INCLUDED_)
#define AFX_CGPAINTERDOC_H__E5ECD4E4_E240_40C1_8101_531C4E2969D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGPainterDoc : public CDocument
{
protected: // create from serialization only
	CCGPainterDoc();
	DECLARE_DYNCREATE(CCGPainterDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGPainterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCGPainterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGPainterDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGPAINTERDOC_H__E5ECD4E4_E240_40C1_8101_531C4E2969D0__INCLUDED_)
