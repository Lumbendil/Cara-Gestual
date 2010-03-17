// PracticaDoc.cpp : implementation of the CPracticaDoc class
//

#include "stdafx.h"
#include "Practica.h"

#include "PracticaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPracticaDoc

IMPLEMENT_DYNCREATE(CPracticaDoc, CDocument)

BEGIN_MESSAGE_MAP(CPracticaDoc, CDocument)
	//{{AFX_MSG_MAP(CPracticaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPracticaDoc construction/destruction

CPracticaDoc::CPracticaDoc()
{
	// TODO: add one-time construction code here

}

CPracticaDoc::~CPracticaDoc()
{
}

BOOL CPracticaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPracticaDoc serialization

void CPracticaDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CPracticaDoc diagnostics

#ifdef _DEBUG
void CPracticaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPracticaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPracticaDoc commands
