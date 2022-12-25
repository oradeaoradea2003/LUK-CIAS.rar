
// LUK-CIASDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "LUK-CIAS.h"
#include "LUK-CIASDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif






///LUK  ///////////////////////// 
HBRUSH m_brBack;

// C++ program to find Current Day, Date
// and Local Time
#include<iostream>
#include<ctime>
using namespace std;

///END LUK
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLUKCIASDlg dialog



CLUKCIASDlg::CLUKCIASDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LUKCIAS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	
}

void CLUKCIASDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_LUKCIAS, m_ziua_luna);
}

BEGIN_MESSAGE_MAP(CLUKCIASDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_STATIC_LUKCIAS, &CLUKCIASDlg::OnStnClickedStaticLukcias)
	ON_BN_CLICKED(IDCANCEL, &CLUKCIASDlg::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CLUKCIASDlg message handlers
void  CLUKCIASDlg:: mainLUKCIAS()
{
	// Declaring argument for time()
	time_t tt;

	// Declaring variable to store return value of
	// localtime()
	struct tm* ti;

	// Applying time()
	time(&tt);

	// Using localtime()
	ti = localtime(&tt);

	//cout << "Current Day, Date and Time is = "
	//	<< asctime(ti);

	m_ziua_luna.SetWindowTextW(CString("ZI   LUNA ORA AN\n  ") + CString(asctime(ti)));

}
CBitmap Bitmap;
BOOL CLUKCIASDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


Bitmap.LoadBitmap(IDB_BITMAP1);
	
	
	CColorDialog dlg(RGB(0,254,254));
	if (dlg.DoModal() == IDOK) {
		m_brBack = CreateSolidBrush(dlg.GetColor());
		//m_brBack = dlg.GetColor();
	}else
	m_brBack = CreateSolidBrush(RGB(0, 0, 0));
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CFont* m_pFont = new CFont();
	m_pFont->CreatePointFont(165, _T("Arial"));
	GetDlgItem(IDC_STATIC_LUKCIAS)->SetFont(m_pFont, TRUE);
	/// <summary>
	/// //
	///
	/// 
	
	mainLUKCIAS();
	SetTimer(1, 1000, 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLUKCIASDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLUKCIASDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		//llllllllllllllllllllllll
		BITMAP bm;
		//Bitmap.LoadBitmap(IDB_BITMAP1);
		Bitmap.GetBitmap(&bm);
		CDC memdc;
		//memdc.CreateCompatibleDC(dc);
		CBitmap* pOldbitmap = dc.SelectObject(&Bitmap);

		if (!dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dc, 0, 0, SRCCOPY))
			MessageBox(L"error bitblt!!!");
		//BrushMap should be intialized once 

		memdc.SelectObject(pOldbitmap);






		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLUKCIASDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLUKCIASDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//lukontime

	mainLUKCIAS();

	CDialogEx::OnTimer(nIDEvent);
}


void CLUKCIASDlg::OnStnClickedStaticLukcias()
{
	// TODO: Add your control notification handler code here






}


void CLUKCIASDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
/*
	CWnd* pWnd = this->GetDlgItem(IDC_STATIC_LUKCIAS);
CDC *dc= pWnd->GetDC();
dc->SetBkColor(RGB(0, 255, 0));
pWnd->Invalidate();
pWnd->UpdateWindow();
Invalidate();
UpdateWindow();
*/
CDialogEx::OnCancel();
}


HBRUSH CLUKCIASDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	pDC->SetBkColor(RGB(0,0,0));
	// TODO:  Return a different brush if the default is not desired
	hbr = m_brBack;
	return hbr;
}


BOOL CLUKCIASDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	BITMAP bm;
	//Bitmap.LoadBitmap(IDB_BITMAP1);
	Bitmap.GetBitmap(&bm);
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	CBitmap* pOldbitmap = memdc.SelectObject(&Bitmap);

	if (!pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memdc, 0, 0, SRCCOPY))
		MessageBox(L"error bitblt!!!");
	//BrushMap should be intialized once 

	memdc.SelectObject(pOldbitmap);
	return CDialogEx::OnEraseBkgnd(pDC);
}
