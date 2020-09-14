// CGPainterView.cpp : implementation of the CCGPainterView class
//

#include "stdafx.h"
#include "CGPainter.h"
#include "GlobalVariables.h"
#include "math.h"

#include "CGPainterDoc.h"
#include "CGPainterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGPainterView

IMPLEMENT_DYNCREATE(CCGPainterView, CView)

BEGIN_MESSAGE_MAP(CCGPainterView, CView)
	//{{AFX_MSG_MAP(CCGPainterView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGPainterView construction/destruction

CCGPainterView::CCGPainterView()
{
	m_pMemDC=new CDC;
	m_pBitmap=new CBitmap;
	m_nMaxX=GetSystemMetrics(SM_CXSCREEN);
	m_nMaxY=GetSystemMetrics(SM_CYSCREEN);

	G_iDrawState = DRAW_NOTHING;
	G_cLineColor = RGB(0,0,0);

	G_iMouseState = NO_BUTTON;
}

CCGPainterView::~CCGPainterView()
{
	delete m_pMemDC;
	delete m_pBitmap;
}

BOOL CCGPainterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCGPainterView drawing

void CCGPainterView::OnDraw(CDC* pDC)
{
	CCGPainterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	/////////////////////////////////////////
	CBitmap* pOldBitmap = m_pMemDC->SelectObject(m_pBitmap);
	pDC->BitBlt(0,0,m_nMaxX,m_nMaxY,m_pMemDC,0,0,SRCCOPY);
	m_pMemDC->SelectObject(pOldBitmap);
}

/////////////////////////////////////////////////////////////////////////////
// CCGPainterView printing

BOOL CCGPainterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGPainterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGPainterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCGPainterView diagnostics

#ifdef _DEBUG
void CCGPainterView::AssertValid() const
{
	CView::AssertValid();
}

void CCGPainterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGPainterDoc* CCGPainterView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGPainterDoc)));
	return (CCGPainterDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGPainterView message handlers

void CCGPainterView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	G_iMouseState = MOUSE_LEFT_BUTTON;
	m_ptStart=point;
	m_ptOld=point;
}

void CCGPainterView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	G_iMouseState = NO_BUTTON;

	if(G_iDrawState == DRAW_NOTHING)
		return;
	
	//set the drawing context
	CDC* pDC=GetDC();
	CBitmap* pOldBitmap=m_pMemDC->SelectObject(m_pBitmap);
	
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, G_cLineColor);
	CPen* pOldPen=m_pMemDC->SelectObject(&pen);
	m_pMemDC->SelectObject(&pen);

	CBrush* pOldBrush=(CBrush*)m_pMemDC->SelectStockObject(NULL_BRUSH);
	m_pMemDC->SelectStockObject(NULL_BRUSH);

	//draw graph
	if(G_iDrawState == DRAW_LINE)
		DrawLine(m_pMemDC, m_ptStart, point, G_cLineColor);
	else if(G_iDrawState == DRAW_CIRCLE)
	{
		CPoint dist = point - m_ptStart;
		int radius = int(sqrt(float(dist.x*dist.x + dist.y*dist.y)) + 0.5);
		DrawCircle(m_pMemDC, m_ptStart, radius, G_cLineColor);
	}	

	//retrieve the old contex
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	m_pMemDC->SelectObject(pOldBitmap);
	m_pMemDC->SelectObject(pOldPen);
	m_pMemDC->SelectObject(pOldBrush);
	ReleaseDC(pDC);
}

void CCGPainterView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(G_iDrawState == DRAW_NOTHING)
		return;
	
	if(G_iMouseState != MOUSE_LEFT_BUTTON)
		return;

	//set drawing context
	CDC* pDC=GetDC();
	CBitmap* pOldBitmap = m_pMemDC->SelectObject(m_pBitmap);
	
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, G_cLineColor);
	CPen* pOldPen=m_pMemDC->SelectObject(&pen);
	pDC->SelectObject(&pen);
	
	CBrush* pOldBrush=(CBrush*)m_pMemDC->SelectStockObject(NULL_BRUSH);
	pDC->SelectStockObject(NULL_BRUSH);

	//wipe the screen. This is used to realize the "elastic band" effect.
	CRect wipeRect(m_ptStart, m_ptOld);
	int radius;
	if(G_iDrawState == DRAW_CIRCLE)		//if drawing circle, the wipeRect is larger
	{
		CPoint dist = m_ptOld - m_ptStart;
		radius = int(sqrt(float(dist.x*dist.x + dist.y*dist.y)) + 0.5);

		CPoint ptLeftTop(m_ptStart.x - radius, m_ptStart.y - radius);
		CPoint ptRightBottom(m_ptStart.x + radius, m_ptStart.y + radius);
		wipeRect = CRect(ptLeftTop, ptRightBottom);
	}
	wipeRect.NormalizeRect();
	wipeRect.InflateRect(2, 2);
	pDC->BitBlt(wipeRect.left, wipeRect.top,
				wipeRect.Width(), wipeRect.Height(),
				m_pMemDC,
				wipeRect.left,wipeRect.top,
				SRCCOPY);

	//draw graph
	if(G_iDrawState == DRAW_LINE)
		DrawLine(pDC, m_ptStart, point, G_cLineColor);
	else if(G_iDrawState == DRAW_CIRCLE)
	{
		CPoint dist = point - m_ptStart;
		int radius = int(sqrt(float(dist.x*dist.x + dist.y*dist.y)) + 0.5);
		DrawCircle(pDC, m_ptStart, radius, G_cLineColor);
	}
	
	//retrieve the old contex
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	m_pMemDC->SelectObject(pOldBitmap);
	m_pMemDC->SelectObject(pOldPen);
	m_pMemDC->SelectObject(pOldBrush);
	ReleaseDC(pDC);
	m_ptOld=point;
}

void CCGPainterView::DrawLine(CDC *pDC, CPoint ptStartPoint, CPoint ptEndPoint, COLORREF cLineColor)
{
//	pDC->MoveTo(ptStartPoint);
//	pDC->LineTo(ptEndPoint);
/*************************************************************
 write the Bresenham' line algorithm for drawing the line
 use function: pDC->SetPixelV(point, cLineColor); to drawing a pixel
编码直线生成算法，调用函数pDC->SetPixelV(point, cLineColor)画像素。
*************************************************************/
	int x1=ptStartPoint.x,y1=ptStartPoint.y,x2= ptEndPoint.x,y2= ptEndPoint.y;  
	float x,y,i,delta_x,delta_y;
	float dx,dy,k;
	dx=(float)(x2-x1);
	dy=(float)(y2-y1);
	if(abs(dx)>abs(dy))
	{
		k=abs(dx);
	}
	else
	{
		k=abs(dy);
	}
	delta_x=dx/k;
	delta_y=dy/k;
	x=ptStartPoint.x;
	y=ptStartPoint.y;
	for(i=1;i<=k;i++)
	{
		x += delta_x;
		y += delta_y;
		pDC->SetPixel(x,y,cLineColor);
	}
	//k=dy/dx;
	//y=y1;
	//x=x1;
	/*if(abs(k)<1)
	{
		for(;x<=x1;x++)
		{
			pDC->SetPixel(x,int(y+0.5),cLineColor);
			y=y+k;
		}
	}
	if(abs(k)>=1)
	{
		for(;y<=y1;y++)
		{
			pDC->SetPixel(int(x+0.5),y,cLineColor);
			x=x+1/k;
		}
	} */ 
}

int CCGPainterView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CDC* pDC=GetDC();
	m_pMemDC->CreateCompatibleDC(pDC);
	m_pBitmap->CreateCompatibleBitmap(pDC,m_nMaxX,m_nMaxY); 
	CBitmap* pOldBitmap=m_pMemDC->SelectObject(m_pBitmap);
	CBrush brush;
	brush.CreateStockObject(WHITE_BRUSH);
	CRect rect(-1,-1,m_nMaxX,m_nMaxY);
	m_pMemDC->FillRect(rect,&brush);
	
	m_pMemDC->SelectObject(pOldBitmap);
	ReleaseDC(pDC);
	
	return 0;
}

void CCGPainterView::DrawCircle(CDC *pDC, CPoint ptOrigin, int iRadius, COLORREF cLineColor)
{
//	CPoint ptLeftTop(ptOrigin.x - iRadius, ptOrigin.y - iRadius);
//	CPoint ptRightBottom(ptOrigin.x + iRadius, ptOrigin.y + iRadius);
//	CRect circleRect(ptLeftTop, ptRightBottom);
//	pDC->Ellipse(circleRect);

/*************************************************************
write the circle algorithm for drawing the circle
use function: pDC->SetPixelV(point, cLineColor); to drawing a pixel
编码圆弧生成算法，调用函数pDC->SetPixelV(point, cLineColor)画像素。
*************************************************************/
   int x,y,delta1,delta2;
	float x0,y0;
	x=0;
	y=iRadius;
	x0=ptOrigin.x;
	y0=ptOrigin.y;
	delta1=(x+1)*(x+1)+(y-1)*(y-1)-iRadius*iRadius;
	while(y>=0)
	{
		 pDC->SetPixel(x0+x,y0+y,cLineColor);
		 pDC->SetPixel(x0+x,y0-y,cLineColor);
		 pDC->SetPixel(x0-x,y0+y,cLineColor);
		 pDC->SetPixel(x0-x,y0-y,cLineColor);
		 if(delta1<0)
		 {
			 delta2=2*delta1+2*y-1;
			 if(delta2<=0)
			 {
				 x=x+1;
				 delta1=delta1+2*x+1;
			 }
			 else
			 {
				 x=x+1;
				 y=y-1;
				 delta1=delta1+2*x-2*y+2;
			 }
		 }
		 else if(delta1>0)
		 {
			 delta2=2*delta1-2*x-1;
			 if(delta2<=0)
			 {
				 x=x+1;
				 y=y-1;
				delta1=delta1+2*x-2*y+2;
			 }
			 else
			 {
				 y=y-1;
				 delta1=delta1-2*y+1;
			 }
		 }
		 else
		 {
			 x=x+1;
			 y=y-1;
			 delta1=delta1+2*x-2*y+2;
		 }
	}
}
