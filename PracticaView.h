//******** PRACTICA GRAFICS PER COMPUTADOR 2
//******** Entorn b�sic VS2005 MONOFINESTRA amb interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Febrer 2010)
// PracticaView.h : interface of the CPracticaView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRACTICAVIEW_H__17E9D4EE_BD1C_11D2_A09D_0060081D77EF__INCLUDED_)
#define AFX_PRACTICAVIEW_H__17E9D4EE_BD1C_11D2_A09D_0060081D77EF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#pragma warning(disable : 4996 4267) // Eliminar missatges de warnings C4996 i C4267 de la compilaci� (Visual 2005)
#endif // _MSC_VER >= 1000

#include "stdafx.h"

// OBJECTE 3DS: Include per la definici� de l'objecte Obj_3DS
#include "lectorsModels/Obj3DS.h"	

// OBJECTE OBJ: Include per la definici� de l'objecte Obj_OBJ
#include "lectorsModels/objLoader.h"
#include "lectorsModels/Objecte3D.h"

// MUSCLES I EXPRESSIONS
#include "Muscles/MuscleManager.h"
#include "Expresions/ExpressionManager.h"

#include "PracticaDoc.h"
#include "Seleccions/Selection.h"
#include "SPoint3D.h"
#include "Seleccions/EditorManager.h"
#include "Muscles/MuscleManager.h"
#include "tractarXML/XMLReader.h"
#include "tractarXML/XMLWriter.h"
#include "Seleccions/Deformation.h"
#include "Animacio/Animation.h"




class CPracticaView : public CView
{
protected: // create from serialization only
	CPracticaView();
	DECLARE_DYNCREATE(CPracticaView);

	void ChangeMuscleState ( TypeMuscle muscle );
	void ChangeExpressionState ( TypeExpression expression );
	void SetAndStartAnimation	( TypeExpression expression );

private:
	bool TeclaControl;
	bool TeclaTab;
	bool zBuffer;

	float acumulativeTime;

	Selection* select;
	EditorManager* editor;
	MuscleManager* MManager;
	ExpressionManager* EManager;
	Deformation* deform;
	Animation*	animate;

// Attributes
public:
	CPracticaDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPracticaView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

//-------------- GC2: Variables globals de CPractivaView
public:
    HGLRC m_hRC;       // Contexte de generaci� OpenGL
    HDC m_hDC;         // Contexte de dispositiu OpenGL

// GC2: Variables de control per Men� Veure->Pantalla Completa 
	bool fullscreen;	// Opci� booleana per Pantalla Completal [0:NO,1:SI]

// GC2: Variables de control per Men� Vista: canvi PV interactiu, Zoom i dibuixar eixos 
	bool mobil;	// Opci� canvi de Punt de Vista interactiu (mobil) [0:NO,1:SI]
	bool zzoom;	// Opci� Zoom interactiu (zoom) [0:NO,1:SI]
	bool pan;    // Opcio Pan. Despla�ament del centre de l'esfera de Vista [0:NO,1:SI]
	bool navega; // Opci� Navega [F:NO,T:SI].
	bool eixos;	// Opci� per dibuixar els eixos X,Y,Z (Eixos?) [0:NO,1:SI]

// GC2: Variables de l'opci� Vista->Pan
	float fact_pan;		    // Factor de despla�ament de la c�mara (opci� pan).
	GLfloat tr_cpv[3];      // vector de Traslaci� del Centre del Punt de Vista (opci� pan)

// GC2: Variables de control de l'opci� Vista->Navega?
	GLfloat n[3];   // Punt cap on mira.
	CPunt3D opv;    // Definici� Or�gen Punt de Vista (en coordenades m�n)
	float angleZ;   // angle de rotaci� de la traject�ria.

// GC2: Variables de control per les opcions de men� Projecci�, Objecte
	char projeccio;	// Men� Projecci�: Tipus de projeccio 
    char objecte;	// Men� Objecte: Tipus d'Objecte

// GC2: Variables de control del men� Transforma
	bool transf;	// Booleana per activar Transformacions (true) o no (false).
	bool trasl;		// Booleana d'activaci� de la Traslaci� (true) o no (false).
	bool rota;		// Booleana d'activaci� de la Rotaci� (true) o no (false).
	bool escal;		// Booleana d'activaci� de l'Escalatge (true) o no (false).
	float fact_Tras, fact_Rota;	// Increments de Traslaci� i Rotaci�.
	CPunt3D VTras;				// Vector de Traslaci�
	CPunt3D VRota;				// Vector de Rotaci�
	CPunt3D VScal;				// Vector d'Escalatge
	bool transX; // Opci� Mobil Eix X?: TG interactives per l'eix X via mouse [F:NO,T:SI].
	bool transY; // Opci� Mobil Eix Y?: TG interactives per l'eix Y via mouse [F:NO,T:SI].
	bool transZ; // Opci� Mobil Eix Z?: TG interactives per l'eix Z via mouse [F:NO,T:SI].

// GC2: Variables de control per les opcions de men� Ocultacions
	bool test_vis;  // Men� ocultacions: Activa [true] o desactiva [false] Test Visibilitat.
	bool oculta;    // Men� ocultacions: Activa [true] o desactiva [false] Ocultacions (Z-buffer).
	bool back_line; // Men� ocultacions: Activa [true] o desactiva [false] dibuix cares back com a l�nies.

// GC2: Variables de control del men� Iluminaci�	
	bool ifixe;          // Iluminaci� fixe independent del PV (ifixe=1) 
						// o depenent (mobil) respecte el PV (casc miner) (ifixe=0)
	char ilumina;		// Tipus d'il.luminaci� [FILFERROS 'f',PLANA 'c',SUAU 'c']
    bool textura;       // Control de textures desactivades [0:NO] o activades [1:SI]
	char t_textura;		// Tipus de textures (predefinides o per fitxer)

// GC2: Variables butons de mouse 
	CPoint m_PosEAvall,m_PosDAvall; //Coordenades del cursor quan el 
	                                //boto esquerre(E) o dret(D) del 
									//mouse ha estat clicat
	bool m_ButoEAvall,m_ButoDAvall; //TRUE si el boto esquerre(E) o dret(D)
									//del mouse esta clicat

// GC2: Variables que controlen par�metres visualitzaci�: Mides finestra Windows i PV
	int w,h;				// Mides de la finestra Windows (w-amplada,h-al�ada)
	float R,angleh,anglev;	// Par�metres camera en coord. esf�riques (R,angleh,anglev)
	char Vis_Polar;			// Variable que controla orientaci� dels eixos en Visualitzaci� Interactiva (POLARZ,POLARY,POLARX)

// GC2: Color de fons
	bool fonsR,fonsG,fonsB;	// Booleanes per controlar variaci� de color per teclat.
	CColor c_fons;			// Intensitat de color de fons.

// GC2: Objecte 3DS:
	Obj_3DS* Ob3DS;			// Variable d'objecte 3D Studio (*.3DS)

// GC2: Objecte OBJ:
	//TODO: Canviar nom i demes
	Objecte3D* ObOBJ;		// Variable d'objecte format OBJ (*.OBJ)

// GC2: Variables del Timer
	float t;		// Par�metre t pel Timer.
	bool anima;		// Booleana que controla si l'animaci� �s activa (TRUE) o no (FALSE)
					//    dins la funci� de control del rellotge OnTimer.

// GC2: Altres variables
	CString nom;	// Nom de fitxer.

// GC2: Variables de control de Muscles
	bool editMuscle;	// Booleana que indica si s'est� editant els muscles.
	TypeMuscle selectedMuscle;

// GC2: Variables de control d'Expressions
	bool editExpression;	// Booleana que indica si s'est� editant les expressions.
	TypeExpression selectedExpression;

// Variables d'animaci�
	bool animacio;
	float temporitzador;
	bool subtitles;

	//XMLReader* lector;
	//XMLWriter* escritor;

	virtual ~CPracticaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

void CPracticaView::Barra_Estat();
int CPracticaView::Log2(int num);   // Log2: C�lcul del log base 2 de num

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPracticaView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnCub();
	//afx_msg void OnUpdateCub(CCmdUI* pCmdUI);
	//afx_msg void OnPerspectiva();
	//afx_msg void OnUpdatePerspectiva(CCmdUI* pCmdUI);
	afx_msg void OnZoom();
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnMobil();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnEsfera();
	//afx_msg void OnUpdateEsfera(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIcosahedron(CCmdUI* pCmdUI);
	//afx_msg void OnTeapot();
	//afx_msg void OnUpdateTeapot(CCmdUI* pCmdUI);
	afx_msg void OnSemafor();
	afx_msg void OnUpdateSemafor(CCmdUI* pCmdUI);
	afx_msg void OnEixos();
	afx_msg void OnUpdateEixos(CCmdUI* pCmdUI);
	afx_msg void OnFilferros();
	afx_msg void OnUpdateFilferros(CCmdUI* pCmdUI);
	afx_msg void OnPlana();
	afx_msg void OnSuau();
	afx_msg void OnUpdateSuau(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePinsa(CCmdUI* pCmdUI);
	afx_msg void OnIFixe();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPan();
	afx_msg void OnUpdatePan(CCmdUI* pCmdUI);
	afx_msg void OnTest();
	afx_msg void OnUpdateTest(CCmdUI* pCmdUI);
	//afx_msg void OnFileSaveAs();
	//afx_msg void OnFileOpen();
	/*afx_msg void OnTraslacio();
	afx_msg void OnUpdateTraslacio(CCmdUI* pCmdUI);
	afx_msg void OnInitras();
	afx_msg void OnRotacio();
	afx_msg void OnUpdateRotacio(CCmdUI* pCmdUI);
	afx_msg void OnInirot();
	afx_msg void OnEscalatge();
	afx_msg void OnUpdateEscalatge(CCmdUI* pCmdUI);*/
	afx_msg void OnBackLine();
	afx_msg void OnUpdateBackLine(CCmdUI* pCmdUI);
	afx_msg void OnZBuffer();
	afx_msg void OnUpdateZBuffer(CCmdUI* pCmdUI);
	/*afx_msg void OnMobilx();
	afx_msg void OnMobily();
	afx_msg void OnUpdateMobily(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMobilx(CCmdUI* pCmdUI);
	afx_msg void OnMobilz();
	afx_msg void OnUpdateMobilz(CCmdUI* pCmdUI);*/
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnInipan();
	/*afx_msg void OnIniescal();*/
	afx_msg void OnUpdatePlana(CCmdUI* pCmdUI);
	//afx_msg void OnTruck();
	//afx_msg void OnUpdateTruck(CCmdUI* pCmdUI);
	afx_msg void OnNavega();
	afx_msg void OnUpdateNavega(CCmdUI* pCmdUI);
	afx_msg void OnIninav();
	//afx_msg void OnObj3ds();
	//afx_msg void OnUpdateObj3ds(CCmdUI* pCmdUI);
	//afx_msg void OnFullscreen();
	afx_msg void OnUpdateFullscreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMobil(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIFixe(CCmdUI* pCmdUI);

	// Creaci� de funcions sobre Muscles i Expressions
	afx_msg void OnImportMuscles();
	afx_msg void OnExportMuscles();
	afx_msg void OnImportExpressions();
	afx_msg void OnExportExpressions();
	afx_msg void OnMuscleEdit();
	afx_msg void OnUpdateMuscleEdit(CCmdUI *pCmdUI);
	afx_msg void OnExpressionEdit();
	afx_msg void OnUpdateExpressionEdit(CCmdUI *pCmdUI);


	afx_msg void SwitchMuscle(TypeMuscle m);
	afx_msg void SwitchExpression(TypeExpression e);

	afx_msg void OnMCellesDreta();
	afx_msg void OnUpdateMCellesDreta(CCmdUI *pCmdUI);
	afx_msg void OnMCellesEsquerra();
	afx_msg void OnUpdateMCellesEsquerra(CCmdUI *pCmdUI);
	afx_msg void OnMBocaDreta();
	afx_msg void OnUpdateMBocaDreta(CCmdUI *pCmdUI);
	afx_msg void OnMBocaEsquerre();
	afx_msg void OnUpdateMBocaEsquerre(CCmdUI *pCmdUI);
	afx_msg void OnMBocaInferior();
	afx_msg void OnUpdateMBocaInferior(CCmdUI *pCmdUI);
	afx_msg void OnMParpellesDreta();
	afx_msg void OnUpdateMParpellesDreta(CCmdUI *pCmdUI);
	afx_msg void OnMParpellesEsquerra();
	afx_msg void OnUpdateMParpellesEsquerra(CCmdUI *pCmdUI);
	afx_msg void OnMGaltesEsquerra();
	afx_msg void OnUpdateMGaltesEsquerra(CCmdUI *pCmdUI);
	afx_msg void OnMGaltesDreta();
	afx_msg void OnUpdateMGaltesDreta(CCmdUI *pCmdUI);

	afx_msg void OnExpTrist();
	afx_msg void OnUpdateExpTrist(CCmdUI *pCmdUI);
	afx_msg void OnExpAlegre();
	afx_msg void OnUpdateExpAlegre(CCmdUI *pCmdUI);
	afx_msg void OnExpEnfadat();
	afx_msg void OnUpdateExpEnfadat(CCmdUI *pCmdUI);
	afx_msg void OnExpSerios();
	afx_msg void OnUpdateExpSerios(CCmdUI *pCmdUI);
	afx_msg void OnExpSorpres();
	afx_msg void OnUpdateExpSorpres(CCmdUI *pCmdUI);

	// Lletres per a la parla
	afx_msg void OnLletresA();
	afx_msg void OnUpdateLletresA(CCmdUI *pCmdUI);
	afx_msg void OnLletresE();
	afx_msg void OnUpdateLletresE(CCmdUI *pCmdUI);
	afx_msg void OnLletresI();
	afx_msg void OnUpdateLletresI(CCmdUI *pCmdUI);
	afx_msg void OnLletresO();
	afx_msg void OnUpdateLletresO(CCmdUI *pCmdUI);
	afx_msg void OnLletresU();
	afx_msg void OnUpdateLletresU(CCmdUI *pCmdUI);
	afx_msg void OnLletresBilabial();
	afx_msg void OnUpdateLletresBilabial(CCmdUI *pCmdUI);
	afx_msg void OnLletresNeutre();
	afx_msg void OnUpdateLletresNeutre(CCmdUI *pCmdUI);

	//Funcions d'animaci�
	afx_msg void OnAnimacio();
	afx_msg void OnUpdateAnimacio(CCmdUI *pCmdUI);
	afx_msg void OnVFast();
	afx_msg void OnUpdateVFast(CCmdUI *pCmdUI);
	afx_msg void OnFast();
	afx_msg void OnUpdateFast(CCmdUI *pCmdUI);
	afx_msg void OnNormal();
	afx_msg void OnUpdateNormal(CCmdUI *pCmdUI);
	afx_msg void OnSlow();
	afx_msg void OnUpdateSlow(CCmdUI *pCmdUI);
	afx_msg void OnVSlow();
	afx_msg void OnUpdateVSlow(CCmdUI *pCmdUI);
	afx_msg void OnParla(); // Activa la parla del personatge
	afx_msg void OnUpdateParla(CCmdUI *pCmdUI);


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpenObj();
public:
	afx_msg void OnFileOpen3ds();
public:
	//afx_msg void OnObjobj();
public:
	//afx_msg void OnUpdateObjobj(CCmdUI *pCmdUI);
public:
	afx_msg void OnPolarZ();
public:
	afx_msg void OnUpdatePolarZ(CCmdUI *pCmdUI);
public:
	afx_msg void OnPolarY();
public:
	afx_msg void OnUpdatePolarY(CCmdUI *pCmdUI);
public:
	afx_msg void OnPolarX();
public:
	afx_msg void OnUpdatePolarX(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in PracticaView.cpp
inline CPracticaDoc* CPracticaView::GetDocument()
   { return (CPracticaDoc*)m_pDocument; }


#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRACTICAVIEW_H__17E9D4EE_BD1C_11D2_A09D_0060081D77EF__INCLUDED_)
