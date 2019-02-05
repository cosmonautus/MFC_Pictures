
// MFC_Pictures.h: основной файл заголовка для приложения MFC_Pictures
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CMFCPicturesApp:
// Сведения о реализации этого класса: MFC_Pictures.cpp
//

class CMFCPicturesApp : public CWinApp
{
public:
	CMFCPicturesApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCPicturesApp theApp;
