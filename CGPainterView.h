// CGPainterView.h : interface of the CCGPainterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGPAINTERVIEW_H__BC739994_9B7B_4098_A2E1_45E46923A426__INCLUDED_)
#define AFX_CGPAINTERVIEW_H__BC739994_9B7B_4098_A2E1_45E46923A426__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGPainterView : public CView
{
protected: // create from serialization only
	CCGPainterView();
	DECLARE_DYNCREATE(CCGPainterView)

// Attributes
public:
	CCGPainterDoc* GetDocument();
	CDC* m_pMemDC;
	CBitmap* m_pBitmap;

	int m_nMaxY;
	int m_nMaxX;

	CPoint m_ptOld;
	CPoint m_ptStart;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGPainterView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawCircle(CDC *pDC, CPoint ptOrigin, int iRadius, COLORREF cLineColor);
	void DrawLine(CDC* pDC, CPoint ptStartPoint, CPoint ptEndPoint, COLORREF cLineColor);
	virtual ~CCGPainterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGPainterView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CGPainterView.cpp
inline CCGPainterDoc* CCGPainterView::GetDocument()
   { return (CCGPainterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGPAINTERVIEW_H__BC739994_9B7B_4098_A2E1_45E46923A426__INCLUDED_)
