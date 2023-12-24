
// kursachDoc.cpp : implementation of the CkursachDoc class
//

#include "pch.h"
#include "framework.h"
#include "MainFrm.h"
#include "CMyTreeView.h"
#include "kursachView.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "kursach.h"
#endif

#include "kursachDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CkursachDoc

IMPLEMENT_DYNCREATE(CkursachDoc, CDocument)

BEGIN_MESSAGE_MAP(CkursachDoc, CDocument)
END_MESSAGE_MAP()


// CkursachDoc construction/destruction

CkursachDoc::CkursachDoc() noexcept
{
	// TODO: add one-time construction code here

}

CkursachDoc::~CkursachDoc()
{
}

BOOL CkursachDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	/*В данном коде мы сначала проверяем на валидность указатель на главное окно приложения.
	Если указатель валиден, значит это не запуск приложения а открытие очередного документа и можно через указатель
	на главное получить доступ к сплиттеру и его содержимому, инициализировав все что необходимо.
	Если же указатель на главное окно приложения нулевой,
	то значит приложение только стартует и все первичные инициализации произойдут
	в CMainFrame::OnCreateClient.Метод FillTree класса древовидного списка вызывается в любом случае.*/
	CWnd* MainWnd = AfxGetMainWnd();

	if (MainWnd)
	{

		pTree = (CMyTreeView*)((CMainFrame*)MainWnd)->m_wndSplitter.GetPane(0, 0);

		pTree->m_pDoc = this;
		pView = (CkursachView*)((CMainFrame*)MainWnd)->m_wndSplitter.GetPane(0, 1);

	}
	pTree->FillTree();

	return TRUE;
}

void CkursachDoc::DisplayImageForFirstIsp()
{
	if (pView)
	{
		// Здесь добавьте код для отображения картинки в вашем представлении (CkursachView)
		// Например, используйте функции для рисования или загрузки изображения
		
		pView->DisplayImage();
	}
}

void CkursachDoc::DisplayImageForSecondIsp()
{
	if (pView)
	{
		// Здесь добавьте код для отображения картинки в вашем представлении (CkursachView)
		// Например, используйте функции для рисования или загрузки изображения
		pView->DisplayImage2();
	}
}



// CkursachDoc serialization

void CkursachDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CkursachDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CkursachDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CkursachDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CkursachDoc diagnostics

#ifdef _DEBUG
void CkursachDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CkursachDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CkursachDoc commands
