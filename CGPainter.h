// CGPainter.h : main header file for the CGPAINTER application
//

#if !defined(AFX_CGPAINTER_H__E817D72C_D1CC_4389_AAB4_87E6B58D9E60__INCLUDED_)
#define AFX_CGPAINTER_H__E817D72C_D1CC_4389_AAB4_87E6B58D9E60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCGPainterApp:
// See CGPainter.cpp for the implementation of this class
//

class CCGPainterApp : public CWinApp
{
public:
	CCGPainterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGPainterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCGPainterApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGPAINTER_H__E817D72C_D1CC_4389_AAB4_87E6B58D9E60__INCLUDED_)
