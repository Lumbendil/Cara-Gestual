// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__17E9D4EA_BD1C_11D2_A09D_0060081D77EF__INCLUDED_)
#define AFX_MAINFRM_H__17E9D4EA_BD1C_11D2_A09D_0060081D77EF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

CStatusBar *GetStatusBar() {return &m_wndStatusBar;} 

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnFrcnInicia();
//	afx_msg void OnUpdateFrcnInicia(CCmdUI* pCmdUI);
// Status Bar
	afx_msg void OnUpdateR(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlfa(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBeta(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePVx(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePVy(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePVz(CCmdUI *pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__17E9D4EA_BD1C_11D2_A09D_0060081D77EF__INCLUDED_)
