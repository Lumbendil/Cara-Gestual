// PracticaDoc.h : interface of the CPracticaDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRACTICADOC_H__17E9D4EC_BD1C_11D2_A09D_0060081D77EF__INCLUDED_)
#define AFX_PRACTICADOC_H__17E9D4EC_BD1C_11D2_A09D_0060081D77EF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CPracticaDoc : public CDocument
{
protected: // create from serialization only
	CPracticaDoc();
	DECLARE_DYNCREATE(CPracticaDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPracticaDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPracticaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPracticaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRACTICADOC_H__17E9D4EC_BD1C_11D2_A09D_0060081D77EF__INCLUDED_)
