
// ChildView.h: интерфейс класса CChildView
//


#pragma once

#include <memory>
#include <vector>

const auto COLOR_PIC_BACKGROUND = RGB(0xFF, 0xFF, 0xE0);
using ImagePtr = std::shared_ptr<CImage>;

// Окно CChildView

class CChildView : public CWnd
{
private:
    int m_currView = -1;
    std::vector<ImagePtr> m_images;

public:
	CChildView();

public:
    void viewPicFromFile(const CString aFileName);
    void viewPicFromFolder(const CString aFolderName);

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    
public:
	virtual ~CChildView();

protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
    void freeResources();

public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

