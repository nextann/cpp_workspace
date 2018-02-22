
// MouseMFCView.h : CMouseMFCView Ŭ������ �������̽�
//

#pragma once


class CMouseMFCView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMouseMFCView();
	DECLARE_DYNCREATE(CMouseMFCView)

// Ư���Դϴ�.
public:
	CMouseMFCDoc* GetDocument() const;

	///////////////////////////////////
	CPoint m_Pos;
	//////////////////////////////////

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMouseMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MouseMFCView.cpp�� ����� ����
inline CMouseMFCDoc* CMouseMFCView::GetDocument() const
   { return reinterpret_cast<CMouseMFCDoc*>(m_pDocument); }
#endif

