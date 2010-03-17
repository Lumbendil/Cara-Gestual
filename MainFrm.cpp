// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Practica.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
// Status Bar
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_R, OnUpdateR)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ALFA, OnUpdateAlfa)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_BETA, OnUpdateBeta)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_PVX, OnUpdatePVx)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_PVY, OnUpdatePVy)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_PVZ, OnUpdatePVz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_R,
	ID_INDICATOR_ALFA,
	ID_INDICATOR_BETA,
//	ID_SEPARATOR,
	ID_INDICATOR_PVX,
	ID_INDICATOR_PVY,
	ID_INDICATOR_PVZ,
//	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
	ID_INDICATOR_TR,		// Indicador de tipus Transformació (T,R)
	ID_INDICATOR_PTR,		// Indicador dels paràmetres de Transformació (S,R,T)
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
	ID_INDICATOR_PAS
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("No se pudo crear la barra de herramientas\n");
		return -1;      // no se pudo crear
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFrameWnd::PreCreateWindow(cs);
}

void CMainFrame::OnUpdateR(CCmdUI *pCmdUI)
{
//	pCmdUI->Enable();
//	CString strR;
//	strR.Format("%6.4f  ",R);
//	pCmdUI->SetText(strR);
}

void CMainFrame::OnUpdateAlfa(CCmdUI *pCmdUI)
{
//	pCmdUI->Enable();
//	CString strAlfa;
//	strAlfa.Format("A= %f  ",anglev);
//	pCmdUI->SetText(strAlfa);
}

void CMainFrame::OnUpdateBeta(CCmdUI *pCmdUI)
{
//	pCmdUI->Enable();
//	CString strBeta;
//	CPracticaView * myView=(CPracticaView *) GetActiveView()
//	strBeta.Format("B= %f  ",angleh);
//	pCmdUI->SetText(strBeta);
}

void CMainFrame::OnUpdatePVx(CCmdUI *pCmdUI)
{
//	pCmdUI->Enable();
//	CString strR;
//	strR.Format("PVx=%6.4f  ",PVx);
//	pCmdUI->SetText(strR);
}

void CMainFrame::OnUpdatePVy(CCmdUI *pCmdUI)
{
//	pCmdUI->Enable();
//	CString strAlfa;
//	strAlfa.Format("PVy= %f  ",PVy);
//	pCmdUI->SetText(strAlfa);
}

void CMainFrame::OnUpdatePVz(CCmdUI *pCmdUI)
{
//	pCmdUI->Enable();
//	CString strBeta;
//	CPracticaView * myView=(CPracticaView *) GetActiveView()
//	strBeta.Format("PVz= %f  ",PVz);
//	pCmdUI->SetText(strBeta);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

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

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

