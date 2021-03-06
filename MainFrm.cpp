
// MainFrm.cpp: реализация класса CMainFrame
//

#include "stdafx.h"
#include "MFC_Pictures.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
    ON_COMMAND(ID_VIEW_PIC, &CMainFrame::OnViewPic)
    ON_UPDATE_COMMAND_UI(ID_VIEW_PIC, &CMainFrame::OnUpdateCmd)
    ON_COMMAND(ID_VIEW_FOLDER, &CMainFrame::OnViewFolder)
    ON_UPDATE_COMMAND_UI(ID_VIEW_FOLDER, &CMainFrame::OnUpdateCmd)
END_MESSAGE_MAP()

// Создание или уничтожение CMainFrame

CMainFrame::CMainFrame() noexcept
{
	// TODO: добавьте код инициализации члена
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// создать представление для размещения рабочей области рамки
	if (!m_wndView.Create(nullptr, nullptr, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, nullptr))
	{
		TRACE0("Не удалось создать окно представлений\n");
		return -1;
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// Диагностика CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// Обработчики сообщений CMainFrame

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnUpdateCmd(CCmdUI *pCmdUI)
{
    pCmdUI->Enable();
}

void CMainFrame::OnViewPic()
{
    CFileDialog dlg(TRUE, nullptr, nullptr, 6UL, _T("Графические файлы|*.jpg;*.jpeg;*.bmp|"), this);
    if (dlg.DoModal() == IDOK)
    {                
        m_wndView.viewPicFromFile(dlg.GetFolderPath() + _T("\\") + dlg.GetFileName());
    }
}

//#include <thread>

void CMainFrame::OnViewFolder()
{
    CFolderPickerDialog dlg(nullptr, 0, this);
    if (dlg.DoModal() == IDOK)
    {
        //auto func = std::bind(&CChildView::viewPicFromFolder, &m_wndView, dlg.GetFolderPath());
        //std::thread thrd(func);
        //thrd.join();
        m_wndView.viewPicFromFolder(dlg.GetFolderPath());
    }
}
