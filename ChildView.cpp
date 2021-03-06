
// ChildView.cpp: реализация класса CChildView
//

#include "stdafx.h"
#include "MFC_Pictures.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW), nullptr);

	return TRUE;
}

void CChildView::viewPicFromFile(const CString aFileName)
{
    freeResources();
    ImagePtr img = std::make_shared<CImage>();
    if (img->Load(aFileName) != S_OK)
        ::AfxMessageBox(CString(_T("Невозможно загрузить файл: ")) + aFileName, MB_ICONERROR + MB_OK);
    else
    {
        m_images.push_back(img);
        m_currView = 0;
        Invalidate();
    }
}

void getListFiles(const CString aMask, CStringArray& aList)
{
    CFileFind find;
    bool isWorking = find.FindFile(aMask);
    while(isWorking)
    {
        isWorking = find.FindNextFileW();
        if (find.IsDots() | find.IsDirectory()) 
            continue;
        aList.Add(find.GetFilePath());
    }
}

void CChildView::viewPicFromFolder(const CString aFolderName)
{
    freeResources();
    CStringArray list;
    getListFiles(aFolderName + _T("\\*.jpeg"), list);
    getListFiles(aFolderName + _T("\\*.jpg"), list);
    getListFiles(aFolderName + _T("\\*.bmp"), list);
    for (int i = 0; i < list.GetCount(); i++)
    {
        ImagePtr img = std::make_shared<CImage>();
        if (img->Load(list[i]) == S_OK)
            m_images.push_back(img);
    }
    if (m_images.size() > 0)
    {
        m_currView = 0;
        if (m_images.size() > 1)
            SetTimer(NULL, 2000, nullptr);
        Invalidate();
    }
}

void insertRectFromTo(const CRect aFrom, CRect& aTo)
{
    float scale = min((float)aTo.Width() / aFrom.Width(), (float)aTo.Height() / aFrom.Height());
    CRect rNew{ 0, 0, int(aFrom.Width() * scale), int(aFrom.Height() * scale) };
    rNew.OffsetRect((aTo.Width() - rNew.Width()) / 2, (aTo.Height() - rNew.Height()) / 2);
    aTo = rNew;
}

void CChildView::OnPaint()
{
    CPaintDC paintDC(this);
    CMemDC memDC(paintDC, this);
    CDC& dc = memDC.GetDC();
    
    CRect rDst;
    GetClientRect(rDst);
    dc.FillSolidRect(rDst, COLOR_PIC_BACKGROUND);
    if (m_currView < 0)
    {
        dc.DrawText(_T("П У С Т О"), rDst, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        return;
    }
    ImagePtr img = m_images[m_currView];
    if (img->IsNull())
    {
        dc.DrawText(_T("НЕТ КАРТИНКИ"), rDst, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        return;
    }
    CRect rSrc{ 0, 0, img->GetWidth(), img->GetHeight() };
    insertRectFromTo(rSrc, rDst);

    dc.SetStretchBltMode(HALFTONE);
    img->StretchBlt(dc, rDst, SRCCOPY);
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    if (++m_currView >= (int)m_images.size())
        m_currView = 0;
    Invalidate();
    CWnd::OnTimer(nIDEvent);
}

void CChildView::freeResources()
{
    KillTimer(NULL);
    m_currView = -1;
    m_images.clear();
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}

void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    freeResources();
    Invalidate();
    CWnd::OnLButtonDblClk(nFlags, point);
}

