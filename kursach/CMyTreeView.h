#pragma once
#include "afxcview.h"

// CMyTreeView view
class CkursachDoc;

class CMyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CMyTreeView)

protected:
	CMyTreeView();           // protected constructor used by dynamic creation
	virtual ~CMyTreeView();

public:
	HTREEITEM m_hKursach, m_hFirstIsp, m_hBuild, m_hSecondIsp, m_hBuild2;
	void FillTree();
	CkursachDoc* m_pDoc;
	void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


