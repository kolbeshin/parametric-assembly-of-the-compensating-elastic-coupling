// CMyTreeView.cpp : implementation file
//

#include "pch.h"
#include "kursach.h"
#include "CMyTreeView.h"
#include "kursachDoc.h"
#include "CNewDialog.h"
#include "CNewDialog2.h"


// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}
//
//BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
//END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CMyTreeView::OnTvnSelchanged)
END_MESSAGE_MAP()

// CMyTreeView diagnostics

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyTreeView message handlers
void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_hKursach = tree.InsertItem(L"Муфты", -1, -1, NULL, TVI_FIRST);
    m_hSecondIsp = tree.InsertItem(L"2 исполнение", -1, -1, m_hKursach, TVI_FIRST);
    m_hBuild2 = tree.InsertItem(L"Построить", -1, -1, m_hSecondIsp, TVI_FIRST);
	m_hFirstIsp = tree.InsertItem(L"1 исполнение", -1, -1, m_hKursach, TVI_FIRST);
    m_hBuild = tree.InsertItem(L"Построить", -1, -1, m_hFirstIsp, TVI_FIRST);




	//делает сразу развернутый список
	/*tree.Expand(m_hKursach, TVE_EXPAND);*/
}

void CMyTreeView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

    HTREEITEM hSelectedItem = pNMTreeView->itemNew.hItem;

    if (hSelectedItem == m_hFirstIsp)
    {
        // Выбран "1 исполнение", здесь можно отобразить вашу картинку
        // например, вызвать функцию отображения из вашего представления (CkursachView)
        if (m_pDoc)
        {
            m_pDoc->DisplayImageForFirstIsp();
        }
    }

    if (hSelectedItem == m_hBuild)
    {
        // Создаем новое диалоговое окно
        CNewDialog newDialog;

        // Показываем диалоговое окно
        newDialog.DoModal();
    }

    if (hSelectedItem == m_hSecondIsp)
    {
        // Выбран "2 исполнение", здесь можно отобразить вашу картинку
        // например, вызвать функцию отображения из вашего представления (CkursachView)
        if (m_pDoc)
        {
            m_pDoc->DisplayImageForSecondIsp();
        }
    }

    if (hSelectedItem == m_hBuild2)
    {
        // Создаем новое диалоговое окно
        CNewDialog2 newDialog2;

        // Показываем диалоговое окно
        newDialog2.DoModal();
    }

    *pResult = 0;
}