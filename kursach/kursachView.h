
// kursachView.h : interface of the CkursachView class
//

#pragma once
#include "kursachDoc.h"

class CkursachView : public CView
{
protected: // create from serialization only
	CkursachView() noexcept;
	DECLARE_DYNCREATE(CkursachView)

// Attributes
public:
	CkursachDoc* GetDocument() const;
	void OnPaint();
	void DisplayImage();
	void DisplayImage2();

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	afx_msg void OnSize(UINT nType, int cx, int cy);

// Implementation
public:
	virtual ~CkursachView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in kursachView.cpp
inline CkursachDoc* CkursachView::GetDocument() const
   { return reinterpret_cast<CkursachDoc*>(m_pDocument); }
#endif

