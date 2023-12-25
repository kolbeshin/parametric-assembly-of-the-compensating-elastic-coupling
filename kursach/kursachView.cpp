
// kursachView.cpp : implementation of the CkursachView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "kursach.h"
#endif

#include "kursachDoc.h"
#include "kursachView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CkursachView

IMPLEMENT_DYNCREATE(CkursachView, CView)

BEGIN_MESSAGE_MAP(CkursachView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_SIZE()
END_MESSAGE_MAP()

// CkursachView construction/destruction

CkursachView::CkursachView() noexcept
{
	// TODO: add construction code here

}

CkursachView::~CkursachView()
{
}

BOOL CkursachView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CkursachView drawing

void CkursachView::OnDraw(CDC* /*pDC*/)
{
	CkursachDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CkursachView printing

BOOL CkursachView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CkursachView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CkursachView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CkursachView diagnostics

#ifdef _DEBUG
void CkursachView::AssertValid() const
{
	CView::AssertValid();
}

void CkursachView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CkursachDoc* CkursachView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CkursachDoc)));
	return (CkursachDoc*)m_pDocument;
}
#endif //_DEBUG


// CkursachView message handlers

void CkursachView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    // Вызываем функцию отображения изображений при изменении размера окна
    DisplayImage();
    Invalidate();
    UpdateWindow();
    /*UpdateData(TRUE);*/
}

//void CkursachView::DisplayImage()
//{
//    CClientDC dc(this);
//
//    CRect clientRect;
//    GetClientRect(&clientRect);
//
//    CImage image;
//    if (image.Load(_T("C:/Users/senyashago/source/repos/kursach/1isp.jpg")) == S_OK)
//    {
//        int targetWidth, targetHeight;
//        int imageWidth = image.GetWidth();
//        int imageHeight = image.GetHeight();
//
//        // Определяем, какое измерение меньше, ширина или высота
//        if (clientRect.Width() * imageHeight < clientRect.Height() * imageWidth)
//        {
//            targetWidth = clientRect.Width();
//            targetHeight = MulDiv(targetWidth, imageHeight, imageWidth);
//        }
//        else
//        {
//            targetHeight = clientRect.Height();
//            targetWidth = MulDiv(targetHeight, imageWidth, imageHeight);
//        }
//
//        int x = (clientRect.Width() - targetWidth) / 2;
//        int y = (clientRect.Height() - targetHeight) / 2;
//
//        // Рисуем изображение
//        image.StretchBlt(dc, x, y, targetWidth, targetHeight, 0, 0, imageWidth, imageHeight, SRCCOPY);
//    }
//    else
//    {
//        OutputDebugString(_T("Не удалось загрузить изображение\n"));
//    }
//}


//void CkursachView::DisplayImage()
//{
//    CClientDC dc(this);
//
//    CRect clientRect;
//    GetClientRect(&clientRect);
//
//    CImage image1, image2;
//
//    // Загрузка первой картинки
//    if (image1.Load(_T("C:/Users/senyashago/source/repos/kursach/1isp.jpg")) != S_OK)
//    {
//        OutputDebugString(_T("Не удалось загрузить первую картинку\n"));
//        return;
//    }
//
//    // Загрузка второй картинки
//    if (image2.Load(_T("C:/Users/senyashago/source/repos/kursach/1isp_2.jpg")) != S_OK)
//    {
//        OutputDebugString(_T("Не удалось загрузить вторую картинку\n"));
//        return;
//    }
//
//    int targetWidth, targetHeight;
//    int imageWidth = image1.GetWidth();
//    int imageHeight = image1.GetHeight();
//
//    // Определяем размер для первой картинки
//    if (clientRect.Width() * imageHeight < clientRect.Height() * imageWidth)
//    {
//        targetWidth = clientRect.Width();
//        targetHeight = MulDiv(targetWidth, imageHeight, imageWidth);
//    }
//    else
//    {
//        targetHeight = clientRect.Height();
//        targetWidth = MulDiv(targetHeight, imageWidth, imageHeight);
//    }
//
//    int x1 = (clientRect.Width() - targetWidth) / 2;
//    int y1 = (clientRect.Height() - targetHeight) / 2;
//
//    // Определяем размер для второй картинки (например, половина от размеров первой картинки)
//    int x2 = x1;
//    int y2 = y1 + targetHeight;
//    int targetWidth2 = targetWidth;
//    int targetHeight2 = targetHeight / 2;
//
//    // Рисуем первую картинку
//    image1.StretchBlt(dc, x1, y1, targetWidth, targetHeight, 0, 0, imageWidth, imageHeight, SRCCOPY);
//
//    // Рисуем вторую картинку
//    image2.StretchBlt(dc, x2, y2, targetWidth2, targetHeight2, 0, 0, image2.GetWidth(), image2.GetHeight(), SRCCOPY);
//
//    /*Invalidate();
//    UpdateWindow();*/
//}



void CkursachView::DisplayImage()
{
    CClientDC dc(this);

    CRect clientRect;
    GetClientRect(&clientRect);

    CImage image1, image2;

    // Очистка области рисования
    dc.FillSolidRect(&clientRect, dc.GetBkColor());

    // Загрузка первой картинки
    if (image1.Load(_T("C:\\Users\\kolbe\\source\\repos\\parametric-assembly-of-the-compensating-elastic-coupling\\1isp.jpg")) != S_OK)
    {
        OutputDebugString(_T("Не удалось загрузить первую картинку\n"));
        return;
    }

    // Загрузка второй картинки
    if (image2.Load(_T("C:\\Users\\kolbe\\source\\repos\\parametric-assembly-of-the-compensating-elastic-coupling\\1isp_2.jpg")) != S_OK)
    {
        OutputDebugString(_T("Не удалось загрузить вторую картинку\n"));
        return;
    }

    // Увеличиваем исходные размеры картинок в 1.5 раза
    int newWidth1 = static_cast<int>(image1.GetWidth() );
    int newHeight1 = static_cast<int>(image1.GetHeight() );
    int newWidth2 = static_cast<int>(image2.GetWidth() );
    int newHeight2 = static_cast<int>(image2.GetHeight() );

    // Определяем размер для первой картинки
    int x1 = 0;
    int y1 = 0;
    int targetWidth1 = newWidth1;
    int targetHeight1 = newHeight1;

    // Определяем размер для второй картинки
    int x2 = 0;
    int y2 = targetHeight1;  // Поместим вторую картинку под первой
    int targetWidth2 = newWidth2;
    int targetHeight2 = newHeight2;


    // Рисуем первую картинку
    image1.Draw(dc, x1, y1, targetWidth1, targetHeight1);

    // Рисуем вторую картинку
    image2.Draw(dc, x2, y2, targetWidth2, targetHeight2);

    UpdateData(FALSE);
}


void CkursachView::DisplayImage2()
{
    CClientDC dc(this);

    CRect clientRect;
    GetClientRect(&clientRect);

    CImage image1, image2;

    // Очистка области рисования
    dc.FillSolidRect(&clientRect, dc.GetBkColor());

    // Загрузка первой картинки
    if (image1.Load(_T("C:\\Users\\kolbe\\source\\repos\\parametric-assembly-of-the-compensating-elastic-coupling\\2isp.jpg")) != S_OK)
    {
        OutputDebugString(_T("Не удалось загрузить первую картинку\n"));
        return;
    }

    // Загрузка второй картинки
    if (image2.Load(_T("C:\\Users\\kolbe\\source\\repos\\parametric-assembly-of-the-compensating-elastic-coupling\\2isp_2.jpg")) != S_OK)
    {
        OutputDebugString(_T("Не удалось загрузить вторую картинку\n"));
        return;
    }

    // Увеличиваем исходные размеры картинок в 1.5 раза
    int newWidth1 = static_cast<int>(image1.GetWidth() );
    int newHeight1 = static_cast<int>(image1.GetHeight() );
    int newWidth2 = static_cast<int>(image2.GetWidth() );
    int newHeight2 = static_cast<int>(image2.GetHeight() );

    // Определяем размер для первой картинки
    int x1 = 0;
    int y1 = 0;
    int targetWidth1 = newWidth1;
    int targetHeight1 = newHeight1;

    // Определяем размер для второй картинки
    int x2 = 0;
    int y2 = targetHeight1;  // Поместим вторую картинку под первой
    int targetWidth2 = newWidth2;
    int targetHeight2 = newHeight2;


    // Рисуем первую картинку
    image1.Draw(dc, x1, y1, targetWidth1, targetHeight1);

    // Рисуем вторую картинку
    image2.Draw(dc, x2, y2, targetWidth2, targetHeight2);

    UpdateData(FALSE);
}



