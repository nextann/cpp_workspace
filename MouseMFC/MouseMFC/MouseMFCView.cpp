
// MouseMFCView.cpp : CMouseMFCView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MouseMFC.h"
#endif

#include "MouseMFCDoc.h"
#include "MouseMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseMFCView

IMPLEMENT_DYNCREATE(CMouseMFCView, CView)

BEGIN_MESSAGE_MAP(CMouseMFCView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMouseMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMouseMFCView ����/�Ҹ�

CMouseMFCView::CMouseMFCView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMouseMFCView::~CMouseMFCView()
{
}

BOOL CMouseMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMouseMFCView �׸���

void CMouseMFCView::OnDraw(CDC* /*pDC*/)
{
	CMouseMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CClientDC dc(this);
	CString strPoint;
	strPoint.Format(_T("���콺 ��ǥ (%4d, %4d)"), m_Pos.x, m_Pos.y);
	dc.TextOutW(0, 0, strPoint);
}


// CMouseMFCView �μ�


void CMouseMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMouseMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMouseMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMouseMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CMouseMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMouseMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMouseMFCView ����

#ifdef _DEBUG
void CMouseMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMouseMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMouseMFCDoc* CMouseMFCView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMouseMFCDoc)));
	return (CMouseMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMouseMFCView �޽��� ó����


void CMouseMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_Pos = point;
	Invalidate();

	CView::OnMouseMove(nFlags, point);
}
