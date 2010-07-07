//******** PRACTICA GRAFICS PER COMPUTADOR 2
//******** Entorn bàsic VS2005 MONOFINESTRA amb interfície MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Febrer 2010)
// PracticaView.cpp : implementation of the CPracticaView class
// FUNCIONS:		- Control del bucle principal (OnPaint)
//					- Control teclat (OnKeyDown)
//					- Control mouse interactiu i botons mouse 
//							(OnLButtomDown, OnRButtomDown, OnMouseMove)
//					- Control opcions de menú (On*, OnUpdate*)
//					- Control de color de fons per teclat.
//					- Transformacions Geomètriques Interactives via mouse
//
//

#include "stdafx.h"
#include "MainFrm.h"	// Include per Status Bar
#include "Practica.h"
#include "PracticaDoc.h"
#include "PracticaView.h"
#include "Muscles/MuscleManager.h"
#include "Expresions/ExpressionManager.h"
#include "visualitzacio.h"
#include "SPoint3D.h"
#include "Seleccions/Selection.h"
#include "Seleccions/EditorManager.h"
#include "escena.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <gl\glut.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPracticaView

IMPLEMENT_DYNCREATE(CPracticaView, CView)

BEGIN_MESSAGE_MAP(CPracticaView, CView)
	//{{AFX_MSG_MAP(CPracticaView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	//ON_COMMAND(ID_CUB, OnCub)
	//ON_UPDATE_COMMAND_UI(ID_CUB, OnUpdateCub)
	//ON_COMMAND(ID_PERSPECTIVA, OnPerspectiva)
	//ON_UPDATE_COMMAND_UI(ID_PERSPECTIVA, OnUpdatePerspectiva)
	ON_COMMAND(ID_ZOOM, OnZoom)
	ON_UPDATE_COMMAND_UI(ID_ZOOM, OnUpdateZoom)
	ON_COMMAND(ID_MOBIL, OnMobil)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//ON_COMMAND(ID_ESFERA, OnEsfera)
	//ON_UPDATE_COMMAND_UI(ID_ESFERA, OnUpdateEsfera)
	//ON_COMMAND(ID_TEAPOT, OnTeapot)
	//ON_UPDATE_COMMAND_UI(ID_TEAPOT, OnUpdateTeapot)
	ON_COMMAND(ID_EIXOS, OnEixos)
	ON_UPDATE_COMMAND_UI(ID_EIXOS, OnUpdateEixos)
	ON_COMMAND(ID_FILFERROS, OnFilferros)
	ON_UPDATE_COMMAND_UI(ID_FILFERROS, OnUpdateFilferros)
	ON_COMMAND(ID_PLANA, OnPlana)
	ON_COMMAND(ID_SUAU, OnSuau)
	ON_UPDATE_COMMAND_UI(ID_SUAU, OnUpdateSuau)
	ON_COMMAND(ID_I_FIXE, OnIFixe)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_PAN, OnPan)
	ON_UPDATE_COMMAND_UI(ID_PAN, OnUpdatePan)
	ON_COMMAND(ID_TEST, OnTest)
	ON_UPDATE_COMMAND_UI(ID_TEST, OnUpdateTest)
	//ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	/*ON_COMMAND(ID_TRASLACIO, OnTraslacio)
	ON_UPDATE_COMMAND_UI(ID_TRASLACIO, OnUpdateTraslacio)*/
	/*ON_COMMAND(ID_INITRAS, OnInitras)
	ON_COMMAND(ID_ROTACIO, OnRotacio)
	ON_UPDATE_COMMAND_UI(ID_ROTACIO, OnUpdateRotacio)
	ON_COMMAND(ID_INIROT, OnInirot)
	ON_COMMAND(ID_ESCALATGE, OnEscalatge)
	ON_UPDATE_COMMAND_UI(ID_ESCALATGE, OnUpdateEscalatge)*/
	ON_COMMAND(ID_BACK_LINE, OnBackLine)
	ON_UPDATE_COMMAND_UI(ID_BACK_LINE, OnUpdateBackLine)
	ON_COMMAND(ID_ZBuffer, OnZBuffer)
	ON_UPDATE_COMMAND_UI(ID_ZBuffer, OnUpdateZBuffer)
	/*ON_COMMAND(ID_MOBILX, OnMobilx)
	ON_COMMAND(ID_MOBILY, OnMobily)
	ON_UPDATE_COMMAND_UI(ID_MOBILY, OnUpdateMobily)
	ON_UPDATE_COMMAND_UI(ID_MOBILX, OnUpdateMobilx)
	ON_COMMAND(ID_MOBILZ, OnMobilz)
	ON_UPDATE_COMMAND_UI(ID_MOBILZ, OnUpdateMobilz)*/
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_INIPAN, OnInipan)
	/*ON_COMMAND(ID_INIESCAL, OnIniescal)*/
	ON_UPDATE_COMMAND_UI(ID_PLANA, OnUpdatePlana)
	//ON_COMMAND(ID_TRUCK, OnTruck)
	//ON_UPDATE_COMMAND_UI(ID_TRUCK, OnUpdateTruck)
	ON_COMMAND(ID_NAVEGA, OnNavega)
	ON_UPDATE_COMMAND_UI(ID_NAVEGA, OnUpdateNavega)
	ON_COMMAND(ID_ININAV, OnIninav)
	//ON_COMMAND(ID_OBJ3DS, OnObj3ds)
	//ON_UPDATE_COMMAND_UI(ID_OBJ3DS, OnUpdateObj3ds)
	//ON_COMMAND(ID_FULLSCREEN, OnFullscreen)
	//ON_UPDATE_COMMAND_UI(ID_FULLSCREEN, OnUpdateFullscreen)
	ON_UPDATE_COMMAND_UI(ID_MOBIL, OnUpdateMobil)
	ON_UPDATE_COMMAND_UI(ID_I_FIXE, OnUpdateIFixe)
	//}}AFX_MSG_MAP
	// Standard printing commands
	//ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN_OBJ, &CPracticaView::OnFileOpenObj)
	ON_COMMAND(ID_FILE_OPEN_3DS, &CPracticaView::OnFileOpen3ds)
	//ON_COMMAND(ID_OBJOBJ, &CPracticaView::OnObjobj)
	//ON_UPDATE_COMMAND_UI(ID_OBJOBJ, &CPracticaView::OnUpdateObjobj)
	ON_COMMAND(ID_POLAR_Z, &CPracticaView::OnPolarZ)
	ON_UPDATE_COMMAND_UI(ID_POLAR_Z, &CPracticaView::OnUpdatePolarZ)
	ON_COMMAND(ID_POLAR_Y, &CPracticaView::OnPolarY)
	ON_UPDATE_COMMAND_UI(ID_POLAR_Y, &CPracticaView::OnUpdatePolarY)
	ON_COMMAND(ID_POLAR_X, &CPracticaView::OnPolarX)
	ON_UPDATE_COMMAND_UI(ID_POLAR_X, &CPracticaView::OnUpdatePolarX)

	//Vinculació de funcions de Muscles i Expressions amb el menú gràfic de l'aplicació.
	ON_COMMAND(ID_IMPORT_MUSCLES, &CPracticaView::OnImportMuscles)
	ON_COMMAND(ID_EXPORT_MUSCLES, &CPracticaView::OnExportMuscles)
	ON_COMMAND(ID_IMPORT_EXPRESSIONS, &CPracticaView::OnImportExpressions)
	ON_COMMAND(ID_EXPORT_EXPRESSIONS, &CPracticaView::OnExportExpressions)
	ON_COMMAND(ID_MUSCLE_EDIT, &CPracticaView::OnMuscleEdit)
	ON_UPDATE_COMMAND_UI(ID_MUSCLE_EDIT, &CPracticaView::OnUpdateMuscleEdit)
	ON_COMMAND(ID_EXPRESSION_EDIT, &CPracticaView::OnExpressionEdit)
	ON_UPDATE_COMMAND_UI(ID_EXPRESSION_EDIT, &CPracticaView::OnUpdateExpressionEdit)

	ON_COMMAND(ID_MCELLES_DRETA, &CPracticaView::OnMCellesDreta)
	ON_UPDATE_COMMAND_UI(ID_MCELLES_DRETA, &CPracticaView::OnUpdateMCellesDreta)
	ON_COMMAND(ID_MCELLES_ESQUERRE, &CPracticaView::OnMCellesEsquerra)
	ON_UPDATE_COMMAND_UI(ID_MCELLES_ESQUERRE, &CPracticaView::OnUpdateMCellesEsquerra)
	ON_COMMAND(ID_MBOCA_DRETA, &CPracticaView::OnMBocaDreta)
	ON_UPDATE_COMMAND_UI(ID_MBOCA_DRETA, &CPracticaView::OnUpdateMBocaDreta)
	ON_COMMAND(ID_MBOCA_ESQUERRE, &CPracticaView::OnMBocaEsquerre)
	ON_UPDATE_COMMAND_UI(ID_MBOCA_ESQUERRE, &CPracticaView::OnUpdateMBocaEsquerre)
	ON_COMMAND(ID_MBOCA_INFERIOR, &CPracticaView::OnMBocaInferior)
	ON_UPDATE_COMMAND_UI(ID_MBOCA_INFERIOR, &CPracticaView::OnUpdateMBocaInferior)
	ON_COMMAND(ID_MPARPELLES_DRETA, &CPracticaView::OnMParpellesDreta)
	ON_UPDATE_COMMAND_UI(ID_MPARPELLES_DRETA, &CPracticaView::OnUpdateMParpellesDreta)
	ON_COMMAND(ID_MPARPELLES_ESQUERRA, &CPracticaView::OnMParpellesEsquerra)
	ON_UPDATE_COMMAND_UI(ID_MPARPELLES_ESQUERRA, &CPracticaView::OnUpdateMParpellesEsquerra)
	ON_COMMAND(ID_MGALTES_DRETA, &CPracticaView::OnMGaltesDreta)
	ON_UPDATE_COMMAND_UI(ID_MGALTES_DRETA, &CPracticaView::OnUpdateMGaltesDreta)
	ON_COMMAND(ID_MGALTES_ESQUERRA, &CPracticaView::OnMGaltesEsquerra)
	ON_UPDATE_COMMAND_UI(ID_MGALTES_ESQUERRA, &CPracticaView::OnUpdateMGaltesEsquerra)
	ON_COMMAND(ID_MBOCA_SUPERIOR, &CPracticaView::OnMBocaSuperior)
	ON_UPDATE_COMMAND_UI(ID_MBOCA_SUPERIOR, &CPracticaView::OnUpdateMBocaSuperior)
	ON_COMMAND(ID_MBOCA_LATERALESQUERRE, &CPracticaView::OnMBocaLateralE)
	ON_UPDATE_COMMAND_UI(ID_MBOCA_LATERALESQUERRE, &CPracticaView::OnUpdateMBocaLateralE)
	ON_COMMAND(ID_MBOCA_LATERALDRET, &CPracticaView::OnMBocaLateralD)
	ON_UPDATE_COMMAND_UI(ID_MBOCA_LATERALDRET, &CPracticaView::OnUpdateMBocaLateralD)
	ON_COMMAND(ID_MBOCA_DENTDALT, &CPracticaView::OnMBocaDentDalt)
	ON_UPDATE_COMMAND_UI(ID_MBOCA_DENTDALT, &CPracticaView::OnUpdateMBocaDentDalt)
	ON_COMMAND(ID_MBOCA_DENTBAIX, &CPracticaView::OnMBocaDentBaix)
	ON_UPDATE_COMMAND_UI(ID_MBOCA_DENTBAIX, &CPracticaView::OnUpdateMBocaDentBaix)

	ON_COMMAND(ID_EXPRESSIONS_TRIST, &CPracticaView::OnExpTrist)
	ON_UPDATE_COMMAND_UI(ID_EXPRESSIONS_TRIST, &CPracticaView::OnUpdateExpTrist)
	ON_COMMAND(ID_EXPRESSIONS_ALEGRE, &CPracticaView::OnExpAlegre)
	ON_UPDATE_COMMAND_UI(ID_EXPRESSIONS_ALEGRE, &CPracticaView::OnUpdateExpAlegre)
	ON_COMMAND(ID_EXPRESSIONS_ENFADAT, &CPracticaView::OnExpEnfadat)
	ON_UPDATE_COMMAND_UI(ID_EXPRESSIONS_ENFADAT, &CPracticaView::OnUpdateExpEnfadat)
	ON_COMMAND(ID_EXPRESSIONS_SERIOS, &CPracticaView::OnExpSerios)
	ON_UPDATE_COMMAND_UI(ID_EXPRESSIONS_SERIOS, &CPracticaView::OnUpdateExpSerios)
	ON_COMMAND(ID_EXPRESSIONS_SORPRES, &CPracticaView::OnExpSorpres)
	ON_UPDATE_COMMAND_UI(ID_EXPRESSIONS_SORPRES, &CPracticaView::OnUpdateExpSorpres)

	ON_COMMAND(ID_LLETRES_A, &CPracticaView::OnLletresA)
	ON_UPDATE_COMMAND_UI(ID_LLETRES_A, &CPracticaView::OnUpdateLletresA)
	ON_COMMAND(ID_LLETRES_E, &CPracticaView::OnLletresE)
	ON_UPDATE_COMMAND_UI(ID_LLETRES_E, &CPracticaView::OnUpdateLletresE)
	ON_COMMAND(ID_LLETRES_I, &CPracticaView::OnLletresI)
	ON_UPDATE_COMMAND_UI(ID_LLETRES_I, &CPracticaView::OnUpdateLletresI)
	ON_COMMAND(ID_LLETRES_O, &CPracticaView::OnLletresO)
	ON_UPDATE_COMMAND_UI(ID_LLETRES_O, &CPracticaView::OnUpdateLletresO)
	ON_COMMAND(ID_LLETRES_U, &CPracticaView::OnLletresU)
	ON_UPDATE_COMMAND_UI(ID_LLETRES_U, &CPracticaView::OnUpdateLletresU)
	ON_COMMAND(ID_LLETRES_BILABIAL, &CPracticaView::OnLletresBilabial)
	ON_UPDATE_COMMAND_UI(ID_LLETRES_BILABIAL, &CPracticaView::OnUpdateLletresBilabial)
	ON_COMMAND(ID_LLETRES_NEUTRE, &CPracticaView::OnLletresNeutre)
	ON_UPDATE_COMMAND_UI(ID_LLETRES_NEUTRE, &CPracticaView::OnUpdateLletresNeutre)

	//Vinculació de menú amb les opcions d'animació
	ON_COMMAND(ID_ANIMACIO, &CPracticaView::OnAnimacio)
	ON_UPDATE_COMMAND_UI(ID_ANIMACIO, &CPracticaView::OnUpdateAnimacio)
	ON_COMMAND(ID_FASTV, &CPracticaView::OnVFast)
	ON_UPDATE_COMMAND_UI(ID_FASTV, &CPracticaView::OnUpdateVFast)
	ON_COMMAND(ID_FAST, &CPracticaView::OnFast)
	ON_UPDATE_COMMAND_UI(ID_FAST, &CPracticaView::OnUpdateFast)
	ON_COMMAND(ID_NORMAL, &CPracticaView::OnNormal)
	ON_UPDATE_COMMAND_UI(ID_NORMAL, &CPracticaView::OnUpdateNormal)
	ON_COMMAND(ID_SLOW, &CPracticaView::OnSlow)
	ON_UPDATE_COMMAND_UI(ID_SLOW, &CPracticaView::OnUpdateSlow)
	ON_COMMAND(ID_VSLOW, &CPracticaView::OnVSlow)
	ON_UPDATE_COMMAND_UI(ID_VSLOW, &CPracticaView::OnUpdateVSlow)
	ON_COMMAND(ID_PARLA,&CPracticaView::OnParla)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPracticaView construction/destruction

CPracticaView::CPracticaView()
{
// TODO: add construction code here
	
//------ GC2: Inicialització de les variables globals de CPracticaView

// GC2: Variables de control per Menú Veure->Pantalla Completa 
	fullscreen=false;

// GC2: Variables de control per Menú Vista: canvi PV interactiu, Zoom i dibuixar eixos 
	mobil=true;				zzoom=true;		pan=false;		navega=false;	eixos=true;

// GC2: Variables opció Vista->Pan
	fact_pan=1;
	tr_cpv[0]=0;	tr_cpv[1]=0;	tr_cpv[2]=0;

// GC2: Variables de control de l'opció Vista->Navega?
	n[0]=0.0;		n[1]=0.0;		n[2]=0.0;
	opv.x=10.0;		opv.y=0.0;		opv.z=0.0;
	angleZ=0.0;

// GC2: Variables de control per les opcions de menú Projecció, Objecte
	projeccio=PERSPECT;			objecte=CAP;

// GC2: Variables de control del menú Transforma
	transf=false;	trasl=false;	rota=false;		escal=false;
	fact_Tras=1;	fact_Rota=90;
	VTras.x=0.0;	VTras.y=0.0;	VTras.z=0;
	VRota.x=0;		VRota.y=0;		VRota.z=0;
	VScal.x=1;		VScal.y=1;		VScal.z=1;
	transX=false;	transY=false;	transZ=false;

// GC2: Variables de control per les opcions de menú Ocultacions
	oculta=true;			test_vis=false;			back_line=false;

// GC2: Variables de control del menú Iluminació		
	ilumina=SUAU;		ifixe=true;	textura=false;	t_textura=CAP;

// GC2: Variables de control dels botons de mouse
	m_PosEAvall=(0,0);		m_PosDAvall=(0,0);
	m_ButoEAvall=false;		m_ButoDAvall=false;

// GC2: Variables que controlen paràmetres visualització: Mides finestra Windows i PV
	w=0;			h=0;					// Mides finestra
	R=15;		angleh=0;		anglev=0;	// PV en esfèriques
	Vis_Polar=POLARZ;

// GC2: Color de fons
	fonsR=true;		fonsG=true;		fonsB=true;
	c_fons.r=0.0;	c_fons.g=0.0;	c_fons.b=0.0;


// GC2: Objecte OBJ:
	ObOBJ = NULL;

// GC2: Variables del Timer
	t=0;			anima=false;

// GC2: Variables dels Muscles
	editMuscle = false;
	selectedMuscle = NONE_MUSCLE;

// GC2: Variables de les Expressions
	editExpression = false;
	selectedExpression = NONE_EXPRESSION;

// GC2: Altres variables
	nom="";			// Nom del fitxer

// GC2: Tecla Control per a la sel·lecció
	TeclaControl = false;
	TeclaTab = false;
	zBuffer = false;

// GC2: Inicialització de les llibreries DevIL per a la càrrega de textures i fitxers .3DS
	ilInit();					// Inicialitzar llibreria IL
	iluInit();					// Inicialitzar llibreria ILU
	ilutRenderer(ILUT_OPENGL);	// Inicialitzar llibreria ILUT per a OpenGL

	// Variables d'animació
	animacio = false;
	temporitzador = 0.5;
	acumulativeTime = 0.f;
	subtitles = false;
	tempsParla = 0.02f; //Temps de temporitzador Normal

	select = NULL;
	deform = NULL;

	MManager = new MuscleManager();
	EManager = new ExpressionManager(MManager);
	animate = new Animation(EManager, MManager);
	parla = new CParla(animate);
	MSubtitles = new CSubtitles();
	editor = NULL;
}

CPracticaView::~CPracticaView()
{
	// Eliminar estructures dinàmiques
	if (ObOBJ!=NULL)
		delete ObOBJ;
	if (MManager != NULL)
		delete MManager;
	if (EManager != NULL)
		delete EManager;
	if (editor != NULL)
		delete editor;
	if (deform != NULL)
		delete deform;
	if (animate != NULL)
		delete animate;
	if (parla != NULL)
		delete parla;
	if (MSubtitles != NULL)
		delete MSubtitles;
}

BOOL CPracticaView::PreCreateWindow(CREATESTRUCT& cs)
{
// TODO: Modify the Window class or styles here by modifying
//  the CREATESTRUCT cs

// ATENCIÓ:MODIFICACIÓ OPENGL
// Afegim els estils de finestra que necessita OpenGl abans 
//	  de crear la finestra
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CS_OWNDC);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPracticaView drawing

void CPracticaView::OnDraw(CDC* pDC)
{
	CPracticaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPracticaView printing

BOOL CPracticaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPracticaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPracticaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPracticaView diagnostics

#ifdef _DEBUG
void CPracticaView::AssertValid() const
{
	CView::AssertValid();
}

void CPracticaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPracticaDoc* CPracticaView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPracticaDoc)));
	return (CPracticaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPracticaView message handlers

int CPracticaView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{	
	if(CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
// TODO: Add your specialized creation code here

// ATENCIÓ:MODIFICACIÓ OPENGL
	int nPixelFormat;					// Index del format de pixel
	m_hDC = ::GetDC(m_hWnd);			// Agafa un contexte de dispositiu per la Finestra

	static  PIXELFORMATDESCRIPTOR pfd= {
		sizeof(PIXELFORMATDESCRIPTOR),
			1,							// Version number
			PFD_DRAW_TO_WINDOW |		// Dibuixa a la finestra(no en un mapa)
			PFD_SUPPORT_OPENGL |        // Suport de crida a OpenGL a la finestra
			PFD_DOUBLEBUFFER |			// Doble buffer
			PFD_TYPE_RGBA,				// Requested An RGBA Format
			24,							// Color 24 bits
			0,0,0,0,0,0,				// Bits de color
			0,							// No Alpha Buffer
			0,							// Shift Bit Ignored
			0,							// No Accumulation Buffer
			0,0,0,0,					// Accumulation Bits Ignored
			32,							// 32 Bits Z-Buffer (Depth Buffer)
			0,							// No Stencil Buffer
			0,							// No Auxiliary Buffer
			PFD_MAIN_PLANE,				// Dibuix del pla principal
			0,							// Reserved
			0,0,0 };					// Layer masks Ignored
		
// Format del pixel que millor s'ajusti al descrit en pfd
    nPixelFormat= ChoosePixelFormat(m_hDC, &pfd);
	if (!nPixelFormat)
		{::MessageBox(0,"Error en el PixelFormat","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);		// This sends a message telling the program to quit
			return false;
		}

// Activació format pixel per al contexte dispositiu
//			SetPixelFormat(m_hDC,nPixelFormat,&pfd);
	if (!SetPixelFormat(m_hDC,nPixelFormat,&pfd))
		{	::MessageBox(0,"Error en el SetPixelFormat","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);		// This sends a message telling the program to quit
			return false;	
		}

// Creació contexte generació OpenGL
	m_hRC=wglCreateContext(m_hDC);
	if (!m_hRC)
		{	::MessageBox(0,"Error en el GL Rendering Context","Error",MB_OK|MB_ICONERROR);
			PostQuitMessage(0);		// This sends a message telling the program to quit
			return false;
		}
	 
	return true;
}

void CPracticaView::OnDestroy() 
{


// ATENCIÓ:MODIFICACIÓ OPENGL
	 wglDeleteContext(m_hRC);
	 
	 CView::OnDestroy();
}

void CPracticaView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	GLfloat vpv[3]={0.0,0.0,1.0};

// TODO: Add your message handler code here
	
// ATENCIÓ:MODIFICACIÓ OPENGL

// Activació el contexte OpenGL
    wglMakeCurrent(m_hDC,m_hRC);

// Cridem a les funcions de l'escena i la projecció segons s'hagi 
// seleccionat una projecció o un altra
	switch(projeccio)
	{
	case ORTO:
// Aquí farem les quatre crides a ProjeccioOrto i Ortografica per obtenir 
// les quatre vistes ortogràfiques

// Activació del retall de pantalla
	    glEnable(GL_SCISSOR_TEST);

// Retall
		glScissor(0,0,w,h);
	    glViewport(0,0,w,h);

// Fons condicionat al color de fons
		if ((c_fons.r < 0.5) || (c_fons.g < 0.5) || (c_fons.b<0.5))
			FonsB(); 
		else 
			FonsN();

// PLANTA
//		Projeccio_Orto();
//		Ortografica(0,c_fons,objecte,transf,VScal,VTras,VRota,oculta,
//			test_vis,back_line,ilumina,textura,ifixe,eixos);
// ALÇAT 
//		Projeccio_Orto(0,0,(w-1)/2,(h-1)/2);
//		Ortografica(1,c_fons,objecte,transf,VScal,VTras,VRota,oculta,
//			test_vis,back_line,ilumina,textura,ifixe,eixos);
// PERFIL
//		Projeccio_Orto(0,(h+1)/2,(w-1)/2,h/2);
//		Ortografica(2,c_fons,objecte,transf,VScal,VTras,VRota,oculta,
//			test_vis,back_line,ilumina,textura,ifixe,eixos);
// ISOMÈTRICA
//		Projeccio_Orto((w+1)/2,0,w/2,(h-1)/2);
//		Ortografica(3,c_fons,objecte,transf,VScal,VTras,VRota,oculta,
//			test_vis,back_line,ilumina,textura,ifixe,eixos); 

// Intercanvia l'escena al front de la pantalla (buffer OpenGL --> buffer pantalla)
		SwapBuffers(m_hDC);
		break;

	case PERSPECT:
// Aquí es cridarem a ProjeccioPerspectiva i Perspectiva
		Projeccio_Perspectiva(0,0,w,h,R);
		if (navega) 
			{	PerspectivaN(opv,false,n,vpv,pan,tr_cpv,c_fons,objecte,true,transf,VScal,VTras,
					VRota,oculta,test_vis,back_line,ilumina,textura,ifixe,eixos);
			}
		else {	n[0]=0;		n[1]=0;		n[2]=0;
			Perspectiva(anglev,angleh,R,Vis_Polar,pan,tr_cpv,c_fons,objecte,transf,
				VScal,VTras,VRota,oculta,test_vis,back_line,ilumina,textura,ifixe,eixos, editor, ObOBJ, MManager, editMuscle, 
				MSubtitles, subtitles, parla);
			}

// Intercanvia l'escena al front de la pantalla
		SwapBuffers(m_hDC);

		break;

	default:
// Crida a la funció Fons Blanc
		FonsB();
// Intercanvia l'escena al front de la pantalla (buffer OpenGL --> buffer pantalla)
		SwapBuffers(m_hDC);
		break;
	}

// Permet la coexistencia d'altres contextes de generació
	wglMakeCurrent(m_hDC,NULL);

//  Actualitzar la barra d'estat de l'aplicació amb els valors R,A,B,PVx,PVy,PVz
	Barra_Estat();

// Do not call CView::OnPaint() for painting messages
}

// Barra_Estat: Actualitza la barra d'estat (Status Bar) de l'aplicació amb els
//      valors R,A,B,PVx,PVy,PVz en Visualització Interactiva.
void CPracticaView::Barra_Estat() 
{
	CString sss,buffer;
	int  tam,i,decimal,sign;
	char car;
	float Raux = 0.f, angv = 0.f, angh = 0.f;
	float PVx = 0.f, PVy = 0.f, PVz = 0.f;
	GLfloat color;

//  Agafar entorn Status Bar
	CMainFrame *pChild = (CMainFrame*)AfxGetMainWnd();
	CStatusBar *StatusBar = pChild->GetStatusBar();

// Status Bar fitxer fractal
	if (nom!="") StatusBar->SetPaneText(0, nom); 

// Càlcul dels valors per l'opció Vista->Navega
	if (projeccio!=CAP && projeccio!=ORTO) { 
		if (navega) 
			{	Raux=sqrt(opv.x*opv.x+opv.y*opv.y+opv.z*opv.z);
				angv=(asin(opv.z/Raux)*180)/pi; 
				angh=(atan(opv.y/opv.x))*180/pi;
			}
			else {	Raux=R; angv=anglev; angh=angleh; }
			}

// Status Bar R
	if (projeccio==CAP) buffer="       ";
		else if (navega) buffer=" NAV   ";
			else if (projeccio==ORTO) buffer="ORTO   ";
				else {	buffer = _ecvt(Raux, 6, &decimal, &sign );
						//err = _ecvt_s(buffer,_CVTBUFSIZE,Raux, 6, &decimal, &sign );
						//	Posar el punt decimal
						if (decimal==0) decimal=1;
						tam=buffer.GetLength();
						for (i=tam-2;i>=decimal;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+1,car);}
						buffer.SetAt(decimal,'.');
					}
	sss = "R=" + buffer;
// Refrescar posició R Status Bar
	StatusBar->SetPaneText(1, sss); 

// Status Bar anglev
	if (projeccio==CAP) buffer="       ";
		else if (navega) buffer=" NAV   ";
			else if (projeccio==ORTO) buffer="ORTO   ";
				else {	buffer = _ecvt(angv, 5, &decimal, &sign );
						//  Posar el punt decimal
						if (decimal==0) decimal=1;
						tam=buffer.GetLength();
						for (i=tam-2;i>=decimal;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+1,car);}
						buffer.SetAt(decimal,'.');
					}
    sss = "A=" + buffer;
// Refrescar posició angleh Status Bar
	StatusBar->SetPaneText(2, sss); 

// Status Bar anglev
	if (projeccio==CAP) buffer="       ";
		else if (navega) buffer=" NAV   ";
			else if (projeccio==ORTO) buffer="ORTO   ";
				else {buffer = _ecvt(angh, 5, &decimal, &sign );
					  //  Posar el punt decimal
						if (decimal==0) decimal=1;
							tam=buffer.GetLength();
						for (i=tam-2;i>=decimal;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+1,car);}
						buffer.SetAt(decimal,'.');
					}
    sss = "B=" + buffer;
// Refrescar posició anglev Status Bar
	StatusBar->SetPaneText(3, sss); 

// Transformació PV de Coord. esfèriques (R,anglev,angleh) --> Coord. cartesianes (PVx,PVy,PVz)
	if (navega) {PVx=opv.x; PVy=opv.y; PVz=opv.z;}
	else {	PVx=Raux*cos(angh*pi/180)*cos(angv*pi/180);
			PVy=Raux*sin(angh*pi/180)*cos(angv*pi/180);
			PVz=Raux*sin(angv*pi/180);
			}

// Status Bar PVx
	if (projeccio==CAP) buffer="       ";
	else if (projeccio==ORTO) buffer="ORTO   ";
		else if (pan) buffer="PAN    ";
			else {	buffer = _ecvt(PVx, 7, &decimal, &sign );
					//  Posar el punt decimal
					if (decimal<0) buffer="0.00000";
						else{	if (decimal==0) decimal=1;
								tam=buffer.GetLength();
								for (i=tam-2;i>=decimal;i=i-1)
									{	car=buffer.GetAt(i);
										buffer.SetAt(i+1,car);	}
								buffer.SetAt(decimal,'.');
							}
					if (sign!=0) buffer='-' + buffer;
				}
    sss = "PVx=" + buffer;
// Refrescar posició PVx Status Bar
	StatusBar->SetPaneText(4, sss);

// Status Bar PVy
	if (projeccio==CAP) buffer="       ";
	else if (projeccio==ORTO) buffer="ORTO   ";
		else if (pan) buffer="PAN    ";
				else {	buffer = _ecvt(PVy, 7, &decimal, &sign );
					//  Posar el punt decimal
					if (decimal<0) buffer="0.00000";
						else{	if (decimal==0) decimal=1;
								tam=buffer.GetLength();
								for (i=tam-2;i>=decimal;i=i-1)
									{	car=buffer.GetAt(i);
										buffer.SetAt(i+1,car);	}
								buffer.SetAt(decimal,'.');
							}
					if (sign!=0) buffer='-' + buffer;
				}
    sss = "PVy=" + buffer;
// Refrescar posició PVy Status Bar
	StatusBar->SetPaneText(5, sss);

// Status Bar PVz
	if (projeccio==CAP) buffer="       ";
	else if (projeccio==ORTO) buffer="ORTO   ";
		else if (pan) buffer="PAN    ";
				else {	buffer = _ecvt(PVz, 7, &decimal, &sign );
					//  Posar el punt decimal
					if (decimal<0) buffer="0.00000";
						else{	if (decimal==0) decimal=1;
								tam=buffer.GetLength();
								for (i=tam-2;i>=decimal;i=i-1)
									{	car=buffer.GetAt(i);
										buffer.SetAt(i+1,car);	}
								buffer.SetAt(decimal,'.');
							}
					if (sign!=0) buffer='-' + buffer;
				}
    sss = "PVz=" + buffer;
// Refrescar posició PVz Status Bar
	StatusBar->SetPaneText(6, sss);

// Status Bar per indicar tipus de Transformació (TRAS, ROT, ESC)
	sss=" ";
	if (transf) {	
		if (rota) sss="ROT";
			else if (trasl) sss="TRA";
					else if (escal) sss="ESC";
		}
	else {
// Components d'intensitat de fons que varien per teclat
		   if ((fonsR) && (fonsG) && (fonsB)) sss="RGB";
			else if ((fonsR) && (fonsG)) sss="RG ";
					else if ((fonsR) && (fonsB)) sss="R   B";
						else if ((fonsG) && (fonsB)) sss="   GB";
							else if (fonsR) sss="R  ";
								else if (fonsG) sss="  G ";
									else if (fonsB) sss="     B";
		}
// Refrescar posició Transformacions en Status Bar
	StatusBar->SetPaneText(7, sss);

// Status Bar dels paràmetres de Transformació, Color i posicions de Robot i Cama
	sss=" ";
	if (transf)
		 { if (rota)
				{	buffer = _ecvt(VRota.x, 4, &decimal, &sign );
					// Posar el punt decimal
					if ((decimal<=0) || (VRota.x==0)) buffer="0.00";
					else{	tam=buffer.GetLength();
							for (i=tam-2;i>=decimal;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+1,car);	}
							buffer.SetAt(decimal,'.');
						}
					sss = "  " + buffer + "   ";

					buffer = _ecvt(VRota.y, 4, &decimal, &sign );
					// Posar el punt decimal
					if ((decimal<=0) || (VRota.y==0)) buffer="0.00";
					else{	tam=buffer.GetLength();
							for (i=tam-2;i>=decimal;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+1,car);	}
							buffer.SetAt(decimal,'.');
						}
					sss = sss + buffer + "   ";

					buffer = _ecvt(VRota.z, 4, &decimal, &sign );
					// Posar el punt decimal
					if ((decimal<=0) || (VRota.z==0)) buffer="0.00";
					else{	tam=buffer.GetLength();
							for (i=tam-2;i>=decimal;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+1,car);	}
							buffer.SetAt(decimal,'.');
						}
					sss = sss + buffer;
				}
			else if (trasl)
				{	buffer = _ecvt(VTras.x, 5, &decimal, &sign );
					// Posar el punt decimal
					if ((decimal<=0) || (VTras.x==0)) buffer=" 0.000";
					else{	tam=buffer.GetLength();
							for (i=tam-2;i>=decimal;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+1,car);	}
							if (decimal<tam) buffer.SetAt(decimal,'.');
							if (sign!=0) buffer='-' + buffer;
								else buffer=' ' + buffer;
						}
					sss = buffer + ' ';

					buffer = _ecvt(VTras.y, 5, &decimal, &sign );
					// Posar el punt decimal
					if ((decimal<=0) || (VTras.y==0)) buffer=" 0.000";
					else{	tam=buffer.GetLength();
							for (i=tam-2;i>=decimal;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+1,car);	}
							if (decimal<tam) buffer.SetAt(decimal,'.');
							if (sign!=0) buffer='-' + buffer;
								else buffer=' ' + buffer;
						}
					sss = sss + buffer + ' ';

					buffer = _ecvt(VTras.z, 5, &decimal, &sign );
					// Posar el punt decimal
					if ((decimal<=0) || (VTras.z==0)) buffer=" 0.000";
					else{	tam=buffer.GetLength();
							for (i=tam-2;i>decimal;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+1,car);	}
							if (decimal<tam) buffer.SetAt(decimal,'.');
							if (sign!=0) buffer='-' + buffer;
								else buffer=' ' + buffer;
						}
					sss = sss + buffer;
				}
				else if (escal)
					{	buffer = _ecvt(VScal.x, 5, &decimal, &sign );
						// Posar el punt decimal
						if ((decimal<0) || (VScal.x==1)) buffer="1.000";
						else{	tam=buffer.GetLength();
								for (i=tam-2;i>=decimal;i=i-1)
								{	car=buffer.GetAt(i);
									buffer.SetAt(i+1,car);	}
								if (decimal<tam) buffer.SetAt(decimal,'.');
							}
						sss = " " + buffer + "  ";
	
						buffer = _ecvt(VScal.y, 5, &decimal, &sign );
						// Posar el punt decimal
						if ((decimal<0) || (VScal.y==1)) buffer="1.000";
						else{	tam=buffer.GetLength();
								for (i=tam-2;i>=decimal;i=i-1)
								{	car=buffer.GetAt(i);
									buffer.SetAt(i+1,car);	}
								if (decimal<tam) buffer.SetAt(decimal,'.');
							}
						sss = sss + buffer + "  ";
	
						buffer = _ecvt(VScal.z, 5, &decimal, &sign );
						// Posar el punt decimal
						if ((decimal<0) || (VScal.z==1)) buffer="1.000";
						else{	tam=buffer.GetLength();
								for (i=tam-2;i>=decimal;i=i-1)
								{	car=buffer.GetAt(i);
									buffer.SetAt(i+1,car);	}
								if (decimal<tam) buffer.SetAt(decimal,'.');
							}
						sss = sss + buffer;
					}
		}
			else {

					color=c_fons.r*1000;
					buffer = _ecvt(color, 5, &decimal, &sign );
					// Posar el punt decimal
					if ((decimal<0) || (c_fons.r==1)) buffer="1.000";
					else{	tam=buffer.GetLength();
							for (i=decimal-1;i>=0;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+(tam-decimal),car);	}
							buffer.SetAt(1,'.');
							buffer.SetAt(0,'0');
						}
					sss = " " + buffer + "  ";
	
					color=c_fons.g*1000;
					buffer = _ecvt(color, 5, &decimal, &sign );
					// Posar el punt decimal
					if ((decimal<0) || (c_fons.g==1)) buffer="1.000";
					else{	tam=buffer.GetLength();
							for (i=decimal-1;i>=0;i=i-1)
							{	car=buffer.GetAt(i);
								buffer.SetAt(i+(tam-decimal),car);	}
							buffer.SetAt(1,'.');
							buffer.SetAt(0,'0');
						}
					sss = sss + buffer + "  ";

					color=c_fons.b*1000;
					buffer = _ecvt(color, 5, &decimal, &sign );
					// Posar el punt decimal
					if ((decimal<0) || (c_fons.b==1)) buffer="1.000";
					else{	tam=buffer.GetLength();
							for (i=decimal-1;i>=0;i=i-1)
								{	car=buffer.GetAt(i);
									buffer.SetAt(i+(tam-decimal),car);	}
									buffer.SetAt(1,'.');
									buffer.SetAt(0,'0');
						}
							sss = sss + buffer;
						
				}

// Refrescar posició PVz Status Bar
	StatusBar->SetPaneText(8, sss);

}

void CPracticaView::OnSize(UINT nType, int cx, int cy) 
{

// ATENCIÓ:MODIFICACIÓ OPENGL
// Establim les mides de la finestra actual
	w=cx;
	h=cy;

	CView::OnSize(nType, cx, cy);	
}

BOOL CPracticaView::OnEraseBkgnd(CDC* pDC) 
{
// TODO: Add your message handler code here and/or call default
		return FALSE;
}



/* ------------------------------------------------------------------------- */
/*                           CONTROL DEL RATOLI                              */
/* ------------------------------------------------------------------------- */


void CPracticaView::OnLButtonDown(UINT nFlags, CPoint point) 
{
// TODO: Add your message handler code here and/or call default
	
// Detectem en quina posició s'ha pitjat el botó esquerra del
//  mouse i ho guardem a la variable m_PosEAvall
	m_ButoEAvall = true;
	m_PosEAvall = point;
	
	/////////////////////////////////////////////////////////
	/////// wx, wy, wz són les coordenades món			/////	
	/////////////////////////////////////////////////////////
	
	if (editExpression && ObOBJ != NULL)
	{
		if (deform == NULL)
			deform = new Deformation(EManager,ObOBJ,editor);

		deform->SetExpression(selectedExpression);
		deform->SetMuscle(selectedMuscle);
		deform->SetObjecte(ObOBJ);
		// Pas de coordenades esferiques a mon
		float x,y,z;
		if (this->Vis_Polar==POLARZ) {
			x=R*cos(anglev)*cos(angleh);
			y=R*sin(anglev)*cos(angleh);
			z=R*sin(angleh);
		}
		else if (this->Vis_Polar==POLARY) {
			x=R*sin(anglev)*cos(angleh);
			y=R*sin(angleh);
			z=R*cos(anglev)*cos(angleh);
		}
		else {
			x=R*sin(angleh);
			y=R*cos(anglev)*cos(angleh);
			z=R*sin(anglev)*cos(angleh);
		}
		deform->ButtonDown(point.x, point.y, SPoint3D(x, y, z));

	}
	else if (editMuscle && ObOBJ != NULL)
	{
		if (select == NULL)
			select = new Selection(ObOBJ,editor);

		select->SetObj(ObOBJ);
		select->SetZBufferTriangles(SPoint3D(opv.x,opv.y,opv.z));
		if(TeclaControl)
		{
			select->ButtonDown(point.x, point.y, 1);
			select->Render();
		}
		else if (TeclaTab)
		{
			select->ButtonDown(point.x, point.y, 2);
			select->Render();
		}
	}

	Invalidate();

	//////////////////////////////////////////////////////////


	CView::OnLButtonDown(nFlags, point);
}


void CPracticaView::OnLButtonUp(UINT nFlags, CPoint point) 
{
// TODO: Add your message handler code here and/or call default
	m_ButoEAvall = false;

	if (editExpression && deform != NULL)
	{
		deform->ButtonUp();
	}
	else if ((select != NULL && TeclaControl) ||(select != NULL && TeclaTab))
	{
		//select->SetZBufferTriangles(SPoint3D(opv.x,opv.y,opv.z));
		select->ButtonUp();
		select->NoRender();
	}

	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}

void CPracticaView::OnRButtonDown(UINT nFlags, CPoint point) 
{
// TODO: Add your message handler code here and/or call default
	m_ButoDAvall = true;
	m_PosDAvall = point;

	//Sel·lecció del punt domimant del muscle del model
	if (editMuscle && ObOBJ != NULL)
	{
		if (select == NULL)
			select = new Selection(ObOBJ,editor);

		select->SetObj(ObOBJ);
		select->SetZBufferTriangles(SPoint3D(opv.x,opv.y,opv.z));
		if (TeclaControl)
			select->ButtonRDown(point.x,point.y);
	}
	
	CView::OnRButtonDown(nFlags, point);
}

void CPracticaView::OnRButtonUp(UINT nFlags, CPoint point) 
{
// TODO: Add your message handler code here and/or call default
	m_ButoDAvall = false;
	
	CView::OnRButtonUp(nFlags, point);
}


// OnMouseWheel: Funció que es crida quan es toca el rodet del mouse
BOOL CPracticaView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	float modul=0;
	GLfloat vdir[3]={0,0,0};

// Funció de zoom quan està activada la funció pan o les T. Geomètriques
	if ((zzoom) || (transX) || (transY) || (transZ)) 
		{	R=R+zDelta;
			if (R<1) R=1;
			Invalidate();
	}
	else if (navega)
		{	vdir[0]=n[0]-opv.x;
			vdir[1]=n[1]-opv.y;
			vdir[2]=n[2]-opv.z;
			modul=sqrt(vdir[0]*vdir[0]+vdir[1]*vdir[1]+vdir[2]*vdir[2]);
			vdir[0]=vdir[0]/modul;
			vdir[1]=vdir[1]/modul;
			vdir[2]=vdir[2]/modul;
			opv.x+=(zDelta/4)*vdir[0];
			opv.y+=(zDelta/4)*vdir[1];
			n[0]+=(zDelta/4)*vdir[0];
			n[1]+=(zDelta/4)*vdir[1];
			Invalidate();
		}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


// OnMouseMove: Funció que es crida quan es mou el mouse. La utilitzem per la 
//				  Visualització Interactiva amb les tecles del mouse apretades per 
//				  modificar els paràmetres de P.V. (R,angleh,anglev) segons els 
//				  moviments del mouse.
//      PARAMETRES: - nFlags: Flags que controlen si el botó es apretat o no.
//					- point: Estructura (x,y) que dóna la posició del mouse 
//							 (coord. pantalla) quan el botó s'ha apretat.
void CPracticaView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (deform != NULL && editExpression && m_ButoEAvall)
	{
		deform->ButtonMove(point.x, point.y);
	}
	else if ((select != NULL && TeclaControl) ||(select != NULL && TeclaTab) || (select != NULL && zBuffer))
	{
		select->ButtonMove(point.x, point.y);
		select->Render();
		Invalidate();
	}
	else
		{
		float modul=0;
		GLfloat vdir[3]={0,0,0};

	// TODO: Add your message handler code here and/or call default
		if (m_ButoEAvall && mobil && projeccio!=CAP)
		{
			
	// Determinació dels angles (en graus) segons l'increment
	//  horitzontal i vertical de la posició del mouse
			CSize gir = m_PosEAvall - point;
			m_PosEAvall = point;
			angleh = angleh-gir.cx/2;
			anglev= anglev+gir.cy/2 ;
			
	// Control per evitar el creixement desmesurat dels angles
			if(anglev>=360)	anglev=anglev-360;
			if(anglev<0)	anglev=anglev+360;
			if(angleh>=360)	angleh=angleh-360;
			if(angleh<0)	angleh=angleh+360;
			InvalidateRect(NULL, false);	
		}
		else if (m_ButoEAvall && navega && (projeccio!=CAP && projeccio!=ORTO)) // Opció Navegació
				{
	// Canviar orientació en opció de Navegació
				CSize girn = m_PosEAvall - point;
				angleZ=girn.cx/2.0;
	// Control per evitar el creixement desmesurat dels angles
				if(angleZ>=360) angleZ=angleZ-360;
				if(angleZ<0)	angleZ=angleZ+360;
	//			if(angleZ>=360)	angleZ=angleZ-360;
	//			if(angleZ<0)	angleZ=angleZ+360;

				n[0]=n[0]-opv.x;
				n[1]=n[1]-opv.y;
				n[0]=n[0]*cos(angleZ*pi/180)-n[1]*sin(angleZ*pi/180);
				n[1]=n[0]*sin(angleZ*pi/180)+n[1]*cos(angleZ*pi/180);
				n[0]=n[0]+opv.x;
				n[1]=n[1]+opv.y;

				m_PosEAvall = point;
				InvalidateRect(NULL,false);
				}

	// Transformació Geomètrica interactiva pels eixos X,Y boto esquerra del mouse
				else {	bool transE = transX || transY;
						if (m_ButoEAvall && transE && transf)
						{
	// Calcular increment
							CSize girT = m_PosEAvall - point;
							if (transX)
								{	long int incrT=girT.cx;
									if (trasl)
										{ VTras.x+=incrT*fact_Tras;
										  if (VTras.x<-100000) VTras.x=100000;
										  if (VTras.x>100000) VTras.x=100000;
										}
										else if (rota)
												{	VRota.x+=incrT*fact_Rota;
													while (VRota.x>=360) VRota.x-=360;
													while (VRota.x<0) VRota.x+=360;
												}
												else if (escal)
													{ if (incrT<0) incrT=-1/incrT;
													  VScal.x=VScal.x*incrT;
													  if(VScal.x<0.25) VScal.x=0.25;
													  if(VScal.x>8192) VScal.x=8192;
													}
								}
							if (transY)
								{	long int incrT=girT.cy;
									if (trasl)
										{	VTras.y+=incrT*fact_Tras;
											if (VTras.y<-100000) VTras.y=100000;
											if (VTras.y>100000) VTras.y=100000;
										}
										else if (rota)
											{	VRota.y+=incrT*fact_Rota;
												while (VRota.y>=360) VRota.y-=360;
												while (VRota.y<0) VRota.y+=360;
											}
											else if (escal)
											{	if (incrT<=0) {	if (incrT>=-2) incrT=-2;
																incrT=1/Log2(-incrT);}
													else incrT=Log2(incrT);
												VScal.y=VScal.y*incrT;
												if(VScal.y<0.25) VScal.y=0.25;
												if(VScal.y>8192) VScal.y=8192;
												}
								}
						m_PosEAvall = point;
						InvalidateRect(NULL,false);
						}
					}

	// Determinació del desplaçament del pan segons l'increment
	//   vertical de la posició del mouse (tecla dreta apretada)
			if (m_ButoDAvall && pan && (projeccio!=CAP && projeccio!=ORTO))
			{	CSize zoomincr=m_PosDAvall - point;
				long int incrx=zoomincr.cx;
				long int incry=zoomincr.cy;

				// Desplaçament pan vertical
				tr_cpv[1]-=incry*fact_pan;
				if(tr_cpv[1]>100000) tr_cpv[1]=100000;
				else if(tr_cpv[1]<-100000) tr_cpv[1]=-100000;

				// Desplaçament pan horitzontal
				tr_cpv[0]+=incrx*fact_pan;
				if(tr_cpv[0]>100000) tr_cpv[0]=100000;
				else if(tr_cpv[0]<-100000) tr_cpv[0]=-100000;

				m_PosDAvall=point;
				InvalidateRect(NULL,false);
			}
	// Determinació del paràmetre R segons l'increment
	//   vertical de la posició del mouse (tecla dreta apretada)
			else if (m_ButoDAvall && zzoom && (projeccio!=CAP && projeccio!=ORTO))
				{
					CSize zoomincr=m_PosDAvall - point;
					long int incr=zoomincr.cy/1.0;

	//				zoom=zoom+incr;
					R=R+incr;
					if (R<1) R=1;
					m_PosDAvall=point;
					InvalidateRect(NULL,false);
				}
				else if (m_ButoDAvall && navega && (projeccio!=CAP && projeccio!=ORTO))
					{
	// Avançar en opció de Navegació
					if (m_PosDAvall!=point) 
						{
						CSize zoomincr=m_PosDAvall - point;

						float incr=zoomincr.cy/2;
	//					long int incr=zoomincr.cy/2.0;  // Causa assertion en "afx.inl" lin 169
						vdir[0]=n[0]-opv.x;
						vdir[1]=n[1]-opv.y;
						vdir[2]=n[2]-opv.z;
						modul=sqrt(vdir[0]*vdir[0]+vdir[1]*vdir[1]+vdir[2]*vdir[2]);
						vdir[0]=vdir[0]/modul;
						vdir[1]=vdir[1]/modul;
						vdir[2]=vdir[2]/modul;
						opv.x+=incr*vdir[0];
						opv.y+=incr*vdir[1];
						n[0]+=incr*vdir[0];
						n[1]+=incr*vdir[1];
						m_PosDAvall=point;
						InvalidateRect(NULL,false);
						}
					}

	// Transformació Geomètrica interactiva per l'eix Z amb boto dret del mouse
					else if (m_ButoDAvall && transZ && transf)
							{
	// Calcular increment
								CSize girT = m_PosDAvall - point;
								long int incrT=girT.cy;
								if (trasl)
									{ VTras.z+=incrT*fact_Tras;
									  if (VTras.z<-100000) VTras.z=100000;
									  if (VTras.z>100000) VTras.z=100000;
									}
									else if (rota)
											{	incrT=girT.cx;
												VRota.z+=incrT*fact_Rota;
												while (VRota.z>=360) VRota.z-=360;
												while (VRota.z<0) VRota.z+=360;
											}
										else if (escal)
											{	if (incrT<=0) {	if (incrT>=-2) incrT=-2;
																incrT=1/Log2(-incrT);}
													else incrT=Log2(incrT);
												VScal.z=VScal.z*incrT;
												if(VScal.z<0.25) VScal.z=0.25;
												if(VScal.z>8192) VScal.z=8192;
											}
		
								m_PosDAvall = point;
								InvalidateRect(NULL,false);
							}

		CView::OnMouseMove(nFlags, point);
//	 Do not call CView::OnPaint() for painting messages
	 }
}

/* ------------------------------------------------------------------------- */
/*                           CONTROL DEL TECLAT                              */
/* ------------------------------------------------------------------------- */

// OnKeyDown: Funció de tractament de teclat (funció que es crida quan es prem una tecla)
//   PARÀMETRES:
//    - nChar: Codi del caracter seleccionat
//    - nRepCnt: Nombre de vegades que s'ha apretat la tecla (acceleració)
//    - nFlags: Flags d'interrupció activats.
void CPracticaView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

const float incr=0.025f;
float modul=0;
GLfloat vdir[3]={0,0,0};

	if ((!pan) && (!transf) && (!navega)) {
// Canvi de la intensitat de fons per teclat

		if (nChar==VK_CONTROL && !TeclaControl)
		{
			TeclaControl = true;
			TeclaTab = false;
		}
		else
			TeclaControl = false;
		if (nChar==VK_TAB && !TeclaTab)
		{
			TeclaTab = true;
			TeclaControl = false;
		}
		else
			TeclaTab = false;

		if(nChar==VK_DOWN) {
			if (fonsR) {
				c_fons.r-=nRepCnt*incr;
				if(c_fons.r<0.0) c_fons.r=0.0;
				}
			if (fonsG) {
				c_fons.g-=nRepCnt*incr;
				if(c_fons.g<0.0) c_fons.g=0.0;
				}
			if (fonsB) {
				c_fons.b-=nRepCnt*incr;
				if(c_fons.b<0.0) c_fons.b=0.0;
				}
			}
			else if(nChar==VK_UP) {
					if (fonsR) {
						c_fons.r+=nRepCnt*incr;
						if(c_fons.r>1.0) c_fons.r=1.0;
						}
					if (fonsG) {
						c_fons.g+=nRepCnt*incr;
						if(c_fons.g>1.0) c_fons.g=1.0;
						}
					if (fonsB) {
						c_fons.b+=nRepCnt*incr;
						if(c_fons.b>1.0) c_fons.b=1.0;
						}
					}
				else if(nChar==VK_SPACE) { 
						if ((fonsR) && (fonsG) && (fonsB)) {
							fonsG=false;
							fonsB=false;
							}
						else if ((fonsR) && (fonsG)) {
							fonsG=false;
							fonsB=true;
							}
							else if ((fonsR) && (fonsB)) {
								fonsR=false;
								fonsG=true;
								}
								else if ((fonsG) && (fonsB)) fonsR=true;
									else if (fonsR) {
											fonsR=false;
											fonsG=true;
											}
										else if (fonsG) {
												fonsG=false;
												fonsB=true;
												}
											else if (fonsB) {
												fonsR=true;
												fonsG=true;
												fonsB=false;
												}
					}
		}
		else {	
			if (transf)
				{ if (rota)
// Modificar vector de rotació per teclat.
					{switch(nChar)
						{
						// Tecla cursor amunt ('8')
						case 104:
							VRota.x+=nRepCnt*fact_Rota;
							if(VRota.x>=360) VRota.x-=360;
							break;

						// Tecla cursor avall ('2')
						case 98:
							VRota.x-=nRepCnt*fact_Rota;
							if(VRota.x<1) VRota.x+=360;
							break;

						// Tecla cursor esquerra ('4')
						case 100:
							VRota.y-=nRepCnt*fact_Rota;
							if(VRota.y<1) VRota.y+=360;
							break;
				
						// Tecla cursor dret ('6')
						case 102:
							VRota.y+=nRepCnt*fact_Rota;
							if(VRota.y>=360) VRota.y-=360;
							break;

						// Tecla HOME ('7')
						case 103:
							VRota.z+=nRepCnt*fact_Rota;
							if(VRota.z>=360) VRota.z-=360;
							break;
				
						// Tecla END ('1')
						case 97:
							VRota.z-=nRepCnt*fact_Rota;
							if(VRota.z<1) VRota.z+=360;
							break;

						// Tecla PgUp ('9')
						case 105:
							fact_Rota/=2;
							if (fact_Rota<1) fact_Rota=1;
							break;
				
						// Tecla PgDown ('3')
						case 99:
							fact_Rota*=2;
							if(fact_Rota>90) fact_Rota=90;
							break;

// Modificar vector d'Escalatge per teclat (actiu amb Rotació)
						// Tecla '+' (augmentar escalat)
						case 107:
							VScal.x=VScal.x*2;
							if(VScal.x>8192) VScal.x=8192;
							VScal.y=VScal.y*2;
							if(VScal.y>8192) VScal.y=8192;
							VScal.z=VScal.z*2;
							if(VScal.z>8192) VScal.z=8192;
							break;

						// Tecla '-' (disminuir escalat)
						case 109:
							VScal.x=VScal.x/2;
							if(VScal.x<0.25) VScal.x=0.25;
							VScal.y=VScal.y/2;
							if(VScal.y<0.25) VScal.y=0.25;
							VScal.z=VScal.z/2;
							if(VScal.z<0.25) VScal.z=0.25;
							break;
							
						// Tecla Espaiador
						case VK_SPACE:
							rota=!rota;
							trasl=!trasl;
							break;
//						default:		
//								break;
						}
					}
					else if (trasl)
						{switch(nChar)
							{
// Modificar vector de Traslació per teclat.
							// Tecla cursor amunt ('8')
							case 104:
								VTras.x-=nRepCnt*fact_Tras;
								if(VTras.x<-100000) VTras.x=100000;
								break;

							// Tecla cursor avall ('2')
							case 98:
								VTras.x+=nRepCnt*fact_Tras;
								if(VTras.x>10000) VTras.x=100000;
								break;

							// Tecla cursor esquerra ('4')
							case 100:
								VTras.y-=nRepCnt*fact_Tras;
								if(VTras.y<-100000) VTras.y=-100000;
								break;
				
							// Tecla cursor dret ('6')
							case 102:
								VTras.y+=nRepCnt*fact_Tras;
								if(VTras.y>100000) VTras.y=100000;
								break;
	
							// Tecla HOME ('7')
							case 103:
								VTras.z+=nRepCnt*fact_Tras;
								if(VTras.z>100000) VTras.z=100000;
								break;
					
							// Tecla END ('1')
							case 97:
								VTras.z-=nRepCnt*fact_Tras;
								if(VTras.z<-100000) VTras.z=-100000;
								break;
	
							// Tecla PgUp ('9')
							case 105:
								fact_Tras/=2;
								if (fact_Tras<1) fact_Tras=1;
								break;
					
							// Tecla PgDown ('3')
							case 99:
								fact_Tras*=2;
								if(fact_Tras>100000) fact_Tras=100000;
								break;

// Modificar vector d'Escalatge per teclat (actiu amb Traslació)
							// Tecla '+' (augmentar escalat)
							case 107:
								VScal.x=VScal.x*2;
								if(VScal.x>8192) VScal.x=8192;
								VScal.y=VScal.y*2;
								if(VScal.y>8192) VScal.y=8192;
								VScal.z=VScal.z*2;
								if(VScal.z>8192) VScal.z=8192;
								break;

							// Tecla '-' (disminuir escalat)
							case 109:
								VScal.x=VScal.x/2;
								if(VScal.x<0.25) VScal.x=0.25;
								VScal.y=VScal.y/2;
								if(VScal.y<0.25) VScal.y=0.25;
								VScal.z=VScal.z/2;
								if(VScal.z<0.25) VScal.z=0.25;	
								break;

							// Tecla Espaiador
							case VK_SPACE:
								rota=!rota;
								trasl=!trasl;
								break;	
//							default:		
//								break;
							}
						}
					else if (escal)
							{/*3*/switch(nChar)
								{/*4*/
// Modificar vector d'Escalatge per teclat (actiu amb Escalat únicament)
								// Tecla '+' (augmentar tot l'escalat)
								case 107:
									VScal.x=VScal.x*2;
									if(VScal.x>8192) VScal.x=8192;
									VScal.y=VScal.y*2;
									if(VScal.y>8192) VScal.y=8192;
									VScal.z=VScal.z*2;
									if(VScal.z>8192) VScal.z=8192;
									break;

								// Tecla '-' (disminuir tot l'escalat)
								case 109:
									VScal.x=VScal.x/2;
									if(VScal.x<0.25) VScal.x=0.25;
									VScal.y=VScal.y/2;
									if(VScal.y<0.25) VScal.y=0.25;
									VScal.z=VScal.z/2;
									if(VScal.z<0.25) VScal.z=0.25;	
									break;
								// Tecla cursor amunt ('8')
								case 104:
									VScal.x=VScal.x*2;
									if(VScal.x>8192) VScal.x=8192;
									break;

								// Tecla cursor avall ('2')
								case 98:
									VScal.x=VScal.x/2;
									if(VScal.x<0.25) VScal.x=0.25;
									break;

								// Tecla cursor esquerra ('4')
								case 100:
									VScal.y=VScal.y/2;
									if(VScal.y<0.25) VScal.y=0.25;
									break;
						
								// Tecla cursor dret ('6')
								case 102:
									VScal.y=VScal.y*2;
									if(VScal.y>8192) VScal.y=8192;
									break;

								// Tecla HOME ('7')
								case 103:
									VScal.z=VScal.z*2;
									if(VScal.z>8192) VScal.z=8192;
									break;
				
								// Tecla END ('1')
								case 97:
									VScal.z=VScal.z/2;
									if(VScal.z<0.25) VScal.z=0.25;	
									break;	
	
//								default:		
//									break;
							/*4*/}
						/*3*/}
						}
//				}
				if (pan) {
					switch(nChar)
						{
							// Tecla cursor amunt
							case VK_UP:
								tr_cpv[1]-=nRepCnt*fact_pan;
								if(tr_cpv[1]<-100000) tr_cpv[1]=100000;
								break;

							// Tecla cursor avall
							case VK_DOWN:
								tr_cpv[1]+=nRepCnt*fact_pan;
								if(tr_cpv[1]>100000) tr_cpv[1]=100000;
								break;

							// Tecla cursor esquerra
							case VK_LEFT:
								tr_cpv[0]+=nRepCnt*fact_pan;
								if(tr_cpv[0]>100000) tr_cpv[0]=100000;
								break;
					
							// Tecla cursor dret
							case VK_RIGHT:
								tr_cpv[0]-=nRepCnt*fact_pan;
								if(tr_cpv[0]<-100000) tr_cpv[0]=100000;
								break;

							// Tecla PgUp
							case VK_PRIOR:
								fact_pan/=2;
								if(fact_pan<0.125) fact_pan=0.125;
								break;
					
							// Tecla PgDown
							case VK_NEXT:
								fact_pan*=2;
								if(fact_pan>2048) fact_pan=2048;
								break;

							default:		
								break;
						}
					}
					else if (navega)
// Controls de moviment de navegació
							{ vdir[0]=n[0]-opv.x;
							  vdir[1]=n[1]-opv.y;
							  vdir[2]=n[2]-opv.z;
							  modul=sqrt(vdir[0]*vdir[0]+vdir[1]*vdir[1]+vdir[2]*vdir[2]);
							  vdir[0]=vdir[0]/modul;
							  vdir[1]=vdir[1]/modul;
							  vdir[2]=vdir[2]/modul;
							  switch(nChar)
								{
								// Tecla cursor amunt
								case VK_UP:
									opv.x+=nRepCnt*fact_pan*vdir[0];
									opv.y+=nRepCnt*fact_pan*vdir[1];
									n[0]+=nRepCnt*fact_pan*vdir[0];
									n[1]+=nRepCnt*fact_pan*vdir[1];
									break;

								// Tecla cursor avall
								case VK_DOWN:
									opv.x-=nRepCnt*fact_pan*vdir[0];
									opv.y-=nRepCnt*fact_pan*vdir[1];
									n[0]-=nRepCnt*fact_pan*vdir[0];
									n[1]-=nRepCnt*fact_pan*vdir[1];
									break;

								// Tecla cursor esquerra
								case VK_LEFT:
									angleZ=+nRepCnt*fact_pan;
									n[0]=n[0]-opv.x;
									n[1]=n[1]-opv.y;
									n[0]=n[0]*cos(angleZ*pi/180)-n[1]*sin(angleZ*pi/180);
									n[1]=n[0]*sin(angleZ*pi/180)+n[1]*cos(angleZ*pi/180);
									n[0]=n[0]+opv.x;
									n[1]=n[1]+opv.y;
									break;
						
								// Tecla cursor dret
								case VK_RIGHT:
									angleZ=360-nRepCnt*fact_pan;
									n[0]=n[0]-opv.x;
									n[1]=n[1]-opv.y;
									n[0]=n[0]*cos(angleZ*pi/180)-n[1]*sin(angleZ*pi/180);
									n[1]=n[0]*sin(angleZ*pi/180)+n[1]*cos(angleZ*pi/180);
									n[0]=n[0]+opv.x;
									n[1]=n[1]+opv.y;
									break;

								// Tecla Inicio
								case VK_HOME:
									opv.z+=nRepCnt*fact_pan;
									n[2]+=nRepCnt*fact_pan;
									break;
				
								// Tecla Fin
								case VK_END:
									opv.z-=nRepCnt*fact_pan;
									n[2]-=nRepCnt*fact_pan;
									break;

								// Tecla PgUp
								case VK_PRIOR:
									fact_pan/=2;
									if(fact_pan<1) fact_pan=1;
									break;
				
								// Tecla PgDown
								case VK_NEXT:
									fact_pan*=2;
									if(fact_pan>2048) fact_pan=2048;
									break;

								default:		
									break;
								}
							}

				}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();	
}

/* ------------------------------------------------------------------------- */
/*   RECURSOS DE MENU (persianes) DE L'APLICACIO:                            */
/*					1. ARXIUS												 */
/*					2. VEURE: ToolBar, StatusBar, Pantalla Completa			 */
/*					3. VISTA: Punt de Vista, Zoom, Pan Navega i Eixos	     */
/*					4. PROJECCIÓ                                             */
/*					5. OBJECTE					                             */
/*					6. TRANSFORMA											 */
/*					7. OCULTACIONS											 */
/*					8. IL.LUMINACIÓ											 */
/*					9. TIMER (ANIMACIÓ)									     */
/*					10. MUSCLES												 */
/*					11. EXPRESSIONS											 */
/*					12. ANIMACIÓ											 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/*					1. ARXIUS 												 */
/* ------------------------------------------------------------------------- */

// Obrir fitxer
//void CPracticaView::OnFileOpen() 
//{
//
////  Obrir diàleg de lectura de fitxer (fitxers (*.MNT)
//	CFileDialog openMunt (TRUE, NULL, NULL,
//		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,
//		_T("MNT Files(*.mnt)|*.mnt|Error Files (*.err)|*err|All Files (*.*)|*.*||"));;
//
//	if (openMunt.DoModal() != IDOK)
//		return;                 // stay with old data file
//    else
//	   {nom=openMunt.GetPathName();}
//
//// Variable de tipus CString 'nom' conté el nom del fitxer seleccionat
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();		
//}

// Obrir fitxer en format gràfic 3DS
void CPracticaView::OnFileOpen3ds()
{
// TODO: Add your command handler code here
	if(ObOBJ!=NULL) delete ObOBJ;

	objecte=OBJOBJ;

// Obrir diàleg de lectura de fitxer
		CFileDialog openOBJ (TRUE, NULL, NULL,
			OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,
			_T("3DS Files(*.3ds)|*.3ds|Error Files (*.err)|*err|All Files (*.*)|*.*||"));;

			if (openOBJ.DoModal() != IDOK)	return;  // stay with old data file
			else nom=openOBJ.GetPathName();
	
// Conversió de la variable CString nom a la variable char *nomfitx, compatible amb la funció carregar3DS
	char * nomfitx = (char *)(LPCTSTR)nom;

	/* i carreguem */	
	wglMakeCurrent(m_hDC,m_hRC);	// Activem contexte OpenGL
	ObOBJ = new Objecte3D(nomfitx,TIPUS_3DS);
	editor = new EditorManager(MManager,EManager,ObOBJ);
	wglMakeCurrent(m_hDC,NULL);	// Desactivem contexte OpenGL

	MManager->SetModel(ObOBJ);
//Resetejar la memòria de Selection
	if (select != NULL)
		select->SetFlagsTriangles();

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}


// OnFileOpenObj: Obrir fitxer en format gràfic OBJ
void CPracticaView::OnFileOpenObj()
{
// TODO: Add your command handler code here
	if(ObOBJ!=NULL) delete ObOBJ;

	objecte=OBJOBJ;

// Obrir diàleg de lectura de fitxer
		CFileDialog openOBJ (TRUE, NULL, NULL,
			OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,
			_T("OBJ Files(*.obj)|*.obj|All Files (*.*)|*.*||"));;

			if (openOBJ.DoModal() != IDOK)	return;  // stay with old data file
			else nom=openOBJ.GetPathName();
	
// Conversió de la variable CString nom a la variable char *nomfitx, compatible amb la funció carregar3DS
	char * nomfitx = (char *)(LPCTSTR)nom;

	/* i carreguem */	
	wglMakeCurrent(m_hDC,m_hRC);	// Activem contexte OpenGL
	ObOBJ = new Objecte3D(nomfitx,TIPUS_OBJ);
	editor = new EditorManager(MManager,EManager,ObOBJ);
	wglMakeCurrent(m_hDC,NULL);	// Desactivem contexte OpenGL

	MManager->SetModel(ObOBJ);
//Resetejar la memòria de Selection
	if (select != NULL)
		select->SetFlagsTriangles();

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();	
}


// Escriure fitxer
//void CPracticaView::OnFileSaveAs() 
//{
//
////  Obrir diàleg d'escriptura de fitxer (fitxers *.MNT)
//	CFileDialog openMunt (FALSE, NULL, NULL,
//		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,
//		_T("MNT Files(*.mnt)|*.mnt|Error Files (*.err)|*err|All Files (*.*)|*.*||"));;
//
//	if (openMunt.DoModal() != IDOK)
//		return;                 // stay with old data file
//    else
//	   {nom=openMunt.GetPathName();}
//
//// Variable de tipus CString 'nom' conté el nom del fitxer seleccionat
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}

/* ------------------------------------------------------------------------- */
/*					2. VEURE: ToolBar), StatusBar, Pantalla Completa         */
/* ------------------------------------------------------------------------- */

// PANTALLA COMPLETA: opció booleana
//void CPracticaView::OnFullscreen() 
//{
//// TODO: Add your command handler code here
//	fullscreen=!fullscreen;
//
//}

void CPracticaView::OnUpdateFullscreen(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if (fullscreen)
		pCmdUI->SetCheck(1);
	else
        pCmdUI->SetCheck(0);
}

/* ------------------------------------------------------------------------- */
/*					3. VISTA: Punt de Vista, Zoom, Pan i Eixos				 */
/* ------------------------------------------------------------------------- */

// Punt de Vista Interactiu (opció booleana)
void CPracticaView::OnMobil() 
{
// TODO: Add your command handler code here
	if (projeccio==PERSPECT) mobil=!mobil;
// Desactivació de Transformacions Geomètriques via mouse 
//	si Visualització Interactiva activada	
	if (mobil)	{	transX=false;		
					transY=false; 		
					transZ=false;
				}
// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateMobil(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if (mobil)
		pCmdUI->SetCheck(1);
	else
        pCmdUI->SetCheck(0);
}

// Zoom Interactiu (opció booleana)
void CPracticaView::OnZoom() 
{
// TODO: Add your command handler code here
	if (projeccio==PERSPECT) zzoom=!zzoom;
// Desactivació de Transformacions Geomètriques via mouse 
//	si Zoom activat
	if (zzoom)	{	transX=false;
					transY=false;
					transZ=false;
				}
// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateZoom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (zzoom)
		pCmdUI->SetCheck(1);
	else
        pCmdUI->SetCheck(0);
}


// VISTA: Polars Eix Z cap amunt per a Visialització Interactiva
void CPracticaView::OnPolarZ()
{
// TODO: Add your command handler code here
	if ((projeccio!=CAP) && (!navega)) Vis_Polar=POLARZ;

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();

}

void CPracticaView::OnUpdatePolarZ(CCmdUI *pCmdUI)
{
// TODO: Add your command update UI handler code here
	if (Vis_Polar==POLARZ)
		pCmdUI->SetCheck(1);
	else
        pCmdUI->SetCheck(0);

}

// VISTA: Polars Eix Y cap amunt per a Visialització Interactiva
void CPracticaView::OnPolarY()
{
// TODO: Add your command handler code here
	if ((projeccio!=CAP) && (!navega)) Vis_Polar=POLARY;

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();

}

void CPracticaView::OnUpdatePolarY(CCmdUI *pCmdUI)
{
// TODO: Add your command update UI handler code here
	if (Vis_Polar==POLARY)
		pCmdUI->SetCheck(1);
	else
        pCmdUI->SetCheck(0);

}


// VISTA: Polars Eix X cap amunt per a Visialització Interactiva
void CPracticaView::OnPolarX()
{
// TODO: Add your command handler code here
	if ((projeccio!=CAP) && (!navega)) Vis_Polar=POLARX;

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();

}

void CPracticaView::OnUpdatePolarX(CCmdUI *pCmdUI)
{
// TODO: Add your command update UI handler code here
	if (Vis_Polar==POLARX)
		pCmdUI->SetCheck(1);
	else
        pCmdUI->SetCheck(0);

}


// PAN: Desplaçament del Centre de l'esfera de visualització (opció booleana)
void CPracticaView::OnPan() 
{
// TODO: Add your command handler code here
	if (projeccio==PERSPECT) pan=!pan;
// Desactivació de Transformacions Geomètriques via mouse i navega si pan activat
	if (pan)	{	mobil=true;		zzoom=true;
					transX=false;	transY=false;	transZ=false;
					navega=false;
				}
	
// Crida a OnPaint() per redibuixar l'escena
	Invalidate();		
}

void CPracticaView::OnUpdatePan(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if (pan)
		pCmdUI->SetCheck(1);
	else
        pCmdUI->SetCheck(0);
}


// VISTA: Origen (inicialitzar) Pan
void CPracticaView::OnInipan() 
{
// TODO: Add your command handler code here
	if (pan) {	fact_pan=1;
				tr_cpv[0]=0;	tr_cpv[1]=0;	tr_cpv[2]=0;
				}
// Crida a OnPaint() per redibuixar l'escena
	Invalidate();	
}


// VISTA: Opció Navega (opció booleana)
void CPracticaView::OnNavega() 
{
// TODO: Add your command handler code here
	if (projeccio==PERSPECT) navega=!navega;
// Desactivació de zoom, mobil, Transformacions Geomètriques via mouse i pan 
//		si navega activat
	if (navega){	mobil=false;	zzoom=false;
					pan=false;
					transX=false;	transY=false;	transZ=false;
				}
	else {mobil=true;
		  zzoom=true;}

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();	
}

void CPracticaView::OnUpdateNavega(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if(navega)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}


// VISTA: Origen Navegació
void CPracticaView::OnIninav() 
{
// TODO: Add your command handler code here
	if (navega) {	n[0]=0.0;		n[1]=0.0;		n[2]=0.0;
					opv.x=10.0;		opv.y=0.0;		opv.z=0.0;
					angleZ=0.0;
				}
// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}


// VISTA: Dibuixar els eixos (opció booleana)
void CPracticaView::OnEixos() 
{
// TODO: Add your command handler code here
	eixos=!eixos;
// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateEixos(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if(eixos)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

/* ------------------------------------------------------------------------- */
/*					4. PROJECCIÓ                                             */
/* ------------------------------------------------------------------------- */

// PROJECCIÓ: Perspectiva
//void CPracticaView::OnPerspectiva() 
//{
//	//Fixat en OnPaint() que dibuixi en Perspectiva
//// TODO: Add your command handler code here
//	projeccio=PERSPECT;
//	mobil=true;			zzoom=true;
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();	
//}
//
//void CPracticaView::OnUpdatePerspectiva(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if (projeccio==PERSPECT)
//		pCmdUI->SetCheck(1);
//	else
//        pCmdUI->SetCheck(0);	
//}
/* ------------------------------------------------------------------------- */
/*					5. OBJECTE					                             */
/* ------------------------------------------------------------------------- */

// OBJECTE Cub
//void CPracticaView::OnCub() 
//{
//// TODO: Add your command handler code here
//	objecte=CUB;
//
//// 	----GC2: Modificar R per centrar Vista amb mida de l'objecte
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();	
//}

//void CPracticaView::OnUpdateCub(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if(objecte==CUB)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}


// OBJECTE Esfera
//void CPracticaView::OnEsfera() 
//{
//// TODO: Add your command handler code here
//	objecte=ESFERA;
//
//// 	----GC2: Modificar R per centrar Vista amb mida de l'objecte
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();	
//}

//void CPracticaView::OnUpdateEsfera(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if(objecte==ESFERA)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}


// OBJECTE Tetera
//void CPracticaView::OnTeapot() 
//{
//// TODO: Add your command handler code here
//	objecte=TETERA;
//
//// 	----GC2: Modificar R per centrar Vista amb mida de l'objecte
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}

//void CPracticaView::OnUpdateTeapot(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if(objecte==TETERA)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}


// OBJECTE Truck
//void CPracticaView::OnTruck() 
//{
//// TODO: Add your command handler code here
//	objecte=TRUCK;
//
//// Activació el contexte OpenGL
//    wglMakeCurrent(m_hDC,m_hRC);
//// Inicialitza vector imatges textura pel Truck.
//	Init_Textures();
//// Desactivació contexte OpenGL
//	wglMakeCurrent(m_hDC,NULL);
//
//// 	----GC2: Modificar R per centrar Vista amb mida de l'objecte
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}

//void CPracticaView::OnUpdateTruck(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if(objecte==TRUCK)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}


// OBJECTE 3DS
//void CPracticaView::OnObj3ds() 
//{
//// TODO: Add your command handler code here
//	if(Ob3DS!=NULL) delete Ob3DS;
//
//	objecte=OBJ3DS;
//
//// Obrir diàleg de lectura de fitxer
//		CFileDialog open3DS (TRUE, NULL, NULL,
//			OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,
//			_T("3DS Files(*.3ds)|*.3ds|Error Files (*.err)|*err|All Files (*.*)|*.*||"));;
//
//			if (open3DS.DoModal() != IDOK)	return;  // stay with old data file
//			else nom=open3DS.GetPathName();
//	
//// Conversió de la variable CString nom a la variable char *nomfitx, compatible amb la funció carregar3DS
//	char * nomfitx = (char *)(LPCTSTR)nom;
//
//	/* i carreguem */	
//	wglMakeCurrent(m_hDC,m_hRC);	// Activem contexte OpenGL
//	Ob3DS = new Obj_3DS;
//	Ob3DS->EliminarMemoria();
//	Ob3DS->Inicialitzar();
//	Ob3DS->Carregar3DS(nomfitx);
//
//// objecte nou;index DisplayList nº2; amb textures
//	Ob3DS->Dibuixa3DS(false,OBJECTE3DS);
//	wglMakeCurrent(m_hDC,NULL);	// Desactivem contexte OpenGL
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}


//void CPracticaView::OnUpdateObj3ds(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if (objecte==OBJ3DS)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}
//
//// OBJECTE OBJ
//void CPracticaView::OnObjobj()
//{
//// TODO: Add your command handler code here
//	if(ObOBJ!=NULL) delete ObOBJ;
//
//	objecte=OBJOBJ;
//
//// Obrir diàleg de lectura de fitxer
//		CFileDialog openOBJ (TRUE, NULL, NULL,
//			OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,
//			_T("OBJ Files(*.obj)|*.obj|Error Files (*.err)|*err|All Files (*.*)|*.*||"));;
//
//			if (openOBJ.DoModal() != IDOK)	return;  // stay with old data file
//			else nom=openOBJ.GetPathName();
//	
//// Conversió de la variable CString nom a la variable char *nomfitx, compatible amb la funció carregar3DS
//	char * nomfitx = (char *)(LPCTSTR)nom;
//
//	/* i carreguem */	
//	wglMakeCurrent(m_hDC,m_hRC);	// Activem contexte OpenGL
//	ObOBJ = new Objecte3D(nomfitx,TIPUS_OBJ);
//	ObOBJ->Dibuixar(OBJECTEOBJ);
//	wglMakeCurrent(m_hDC,NULL);	// Desactivem contexte OpenGL
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}
//
//void CPracticaView::OnUpdateObjobj(CCmdUI *pCmdUI)
//{
//// TODO: Add your command update UI handler code here
//	if (objecte==OBJOBJ)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}


/* ------------------------------------------------------------------------- */
/*					6. TRANSFORMA											 */
/* ------------------------------------------------------------------------- */

//// TRANSFORMA: TRASLACIÓ
//void CPracticaView::OnTraslacio() 
//{
//// TODO: Add your command handler code here	
//	trasl=!trasl;
//	rota=false;
//	if (trasl) escal=true;
//	transf=trasl || rota || escal;
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}
//
//void CPracticaView::OnUpdateTraslacio(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if(trasl)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}
//
//// Reinicialitza a l'origen la Traslació
//void CPracticaView::OnInitras() 
//{
//// TODO: Add your command handler code here	
//	if (trasl) 
//		{	fact_Tras=1;
//			VTras.x=0.0;	VTras.y=0.0;	VTras.z=0;	
//		}		
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}
//
//// TRANSFORMA: ROTACIÓ
//void CPracticaView::OnRotacio() 
//{
//// TODO: Add your command handler code here
//	rota=!rota;
//	trasl=false;
//	if (rota) escal=true;
//	transf=trasl || rota || escal;
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}
//
//void CPracticaView::OnUpdateRotacio(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if(rota)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}
//
//// Reinicialitza a l'origen la Rotació
//void CPracticaView::OnInirot() 
//{
//// TODO: Add your command handler code here
//	if (rota) 
//		{	fact_Rota=90;
//			VRota.x=0;		VRota.y=0;		VRota.z=0;
//		}
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}
//
//
//// TRANSFORMA: ESCALATGE
//void CPracticaView::OnEscalatge() 
//{
//// TODO: Add your command handler code here
//	if ((!rota) && (!trasl)) escal=!escal;
//	transf=trasl || rota || escal;
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}
//
//void CPracticaView::OnUpdateEscalatge(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if(escal)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}
//
//// Reinicialitza a l'origen l'Escalatge
//void CPracticaView::OnIniescal() 
//{
//// TODO: Add your command handler code here
//	if (escal) {VScal.x=1;	VScal.y=1;	VScal.z=1;}
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}
//
//// TRANSFORMA: Transformacions Geomètriques per l'eix X movent el mouse (booleana)
//void CPracticaView::OnMobilx() 
//{
//// TODO: Add your command handler code here
//	if (transf) 
//		{	transX=!transX;
//			if (transX) {	mobil=false;			zzoom=false;
//							pan=false;				navega=false;
//						}
//				else if ((!transY) && (!transZ)){	mobil=true;
//													zzoom=true;
//												}	
//		}
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}
//
//void CPracticaView::OnUpdateMobilx(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if (transX)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}
//
//// TRANSFORMA: Transformacions Geomètriques per l'eix Y movent el mouse (booleana)
//void CPracticaView::OnMobily() 
//{
//// TODO: Add your command handler code here
//	if (transf) 
//		{	transY=!transY;
//			if (transY) {	mobil=false;			zzoom=false;
//							pan=false;				navega=false;
//						}
//				else if ((!transX) && (!transZ)){	mobil=true;
//													zzoom=true;
//												}
//		}
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}
//
//void CPracticaView::OnUpdateMobily(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if (transY)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}
//
//// TRANSFORMA: Transformacions Geomètriques per l'eix X movent el mouse (booleana)
//void CPracticaView::OnMobilz() 
//{
//// TODO: Add your command handler code here
//	if (transf) 
//		{	transZ=!transZ;
//			if (transZ) {	mobil=false;			zzoom=false;
//							pan=false;				navega=false;
//						}
//				else if ((!transX) && (!transY)) {	mobil=true;
//													zzoom=true;
//												}	
//		}
//
//// Crida a OnPaint() per redibuixar l'escena
//	Invalidate();
//}
//
//void CPracticaView::OnUpdateMobilz(CCmdUI* pCmdUI) 
//{
//// TODO: Add your command update UI handler code here
//	if (transZ)
//		 pCmdUI->SetCheck(1);
//	else
//		 pCmdUI->SetCheck(0);
//}


/* ------------------------------------------------------------------------- */
/*					7. OCULTACIONS											 */
/* ------------------------------------------------------------------------- */

// OCULTACIONS: Test de Visibilitat (BACK FACE CULLING) (opció booleana)
void CPracticaView::OnTest() 
{
// TODO: Add your command handler code here
	test_vis=!test_vis;

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateTest(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if (test_vis)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

// OCULTACIONS: Algorisme d'ocultacions Z-buffer (opció booleana)
void CPracticaView::OnZBuffer() 
{
// TODO: Add your command handler code here
	oculta=!oculta;

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateZBuffer(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if (oculta)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

// OCULTACIONS: Dibuix cares darrera com a línies (opció booleana)
void CPracticaView::OnBackLine() 
{
// TODO: Add your command handler code here
	back_line=!back_line;

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateBackLine(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if (back_line)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}


/* ------------------------------------------------------------------------- */
/*					8. IL.LUMINACIÓ											 */
/* ------------------------------------------------------------------------- */

// IL.LUMINACIÓ Font de llum fixe? (opció booleana).
void CPracticaView::OnIFixe() 
{
// TODO: Add your command handler code here
	ifixe=!ifixe;

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateIFixe(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if(ifixe)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}


// IL.LUMINACIÓ Filferros
void CPracticaView::OnFilferros() 
{
// TODO: Add your command handler code here
	ilumina=FILFERROS;
	test_vis=false;		oculta=false;

// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateFilferros(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if(ilumina==FILFERROS)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

// IL.LUMINACIÓ plana
void CPracticaView::OnPlana() 
{
// TODO: Add your command handler code here
	ilumina=PLANA;
	test_vis=false;		oculta=true;

	// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdatePlana(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if(ilumina==PLANA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

// IL.LUMINACIÓ Suau
void CPracticaView::OnSuau() 
{
// TODO: Add your command handler code here
	ilumina=SUAU;
	test_vis=false;		oculta=true;

	// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateSuau(CCmdUI* pCmdUI) 
{
// TODO: Add your command update UI handler code here
	if(ilumina==SUAU)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}


/* ------------------------------------------------------------------------- */
/*					9. TIMER (ANIMACIÓ)										 */
/* ------------------------------------------------------------------------- */

// Rutina d'interrupció pel crono
void CPracticaView::OnTimer(UINT nIDEvent) 
{
// TODO: Add your message handler code here and/or call default
	if (!subtitles)
	{
		if (this->animacio && !editExpression)	
		{
			if (acumulativeTime < temporitzador)
			{
				anima = true;
				animate->NextStepAnimation();
				animate->Render();
				acumulativeTime += 0.004;
			}
			else
			{
				animate->FinalizeAnimation();
				KillTimer(WM_TIMER);
				acumulativeTime = 0.f;
				anima = false;
				subtitles = false;
			}
			// Crida a OnPaint() per redibuixar l'escena
			Invalidate();
		}
	}
	else
	{
		if (parla->IsTalking())
		{
			if (acumulativeTime < tempsParla)
			{
				anima = true;
				animate->NextStepAnimation();
				animate->Render();
				acumulativeTime += 0.004;
			}
			else
			{
				animate->FinalizeAnimation();
				acumulativeTime = 0.f;
				parla->NextTalk();
			}
		}
		else
		{
				KillTimer(WM_TIMER);
				acumulativeTime = 0.f;
				animate->FinalizeAnimation();
				anima = false;
		}
		Invalidate();
	}

	CView::OnTimer(nIDEvent);
}


// ---------------- GC2: Funcions locals a PracticaView.cpp

// Log2: Càlcul del log base 2 de num
int CPracticaView::Log2(int num)
{
	int tlog;

	if (num>=8192) tlog=13;
	else if (num>=4096) tlog=12;
	else if (num>=2048) tlog=11;
	else if (num>=1024) tlog=10;
	else if (num>=512) tlog=9;
	else if (num>=256) tlog=8;
	else if (num>=128) tlog=7;
	else if (num>=64) tlog=6;
	else if (num>=32) tlog=5;
	else if (num>=16) tlog=4;
	else if (num>=8) tlog=3;
	else if (num>=4) tlog=2;
	else if (num>=2) tlog=1;
	else tlog=0;

	return tlog;
}
/* ------------------------------------------------------------------------- */
/*					10. MUSCLES												 */
/* ------------------------------------------------------------------------- */
void CPracticaView::OnImportMuscles()
{
	// Obrir diàleg de lectura de fitxer
	CFileDialog openXML (TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,
		_T("XML Files(*.xml)|*.xml|All Files (*.*)|*.*||"));;

	if (openXML.DoModal() != IDOK)	return;  // stay with old data file
	else nom=openXML.GetPathName();

	// Conversió de la variable CString nom a la variable char *nomfitx, compatible amb la funció carregar3DS
	char * nomfitx = (char *)(LPCTSTR)nom;

	if (ObOBJ != NULL)
	{
		XMLReader* lector = new XMLReader(nomfitx, EManager, MManager);
		lector->Read();
		delete lector;
	}

	// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnExportMuscles()
{
		//  Obrir diàleg d'escriptura de fitxer (fitxers *.MNT)
	CFileDialog openExportXML (FALSE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,
		_T("XML Files(*.xml)|*.xml|All Files (*.*)|*.*||"));;

	if (openExportXML.DoModal() != IDOK)
		return;                 // stay with old data file
    else
	   {nom=openExportXML.GetPathName();}

	nom = nom + CString(".xml");
	// Conversió de la variable CString nom a la variable char *nomfitx, compatible amb la funció carregar3DS
	char * nomfitx = (char *)(LPCTSTR)nom;

	// La variable nomfitx conté tot el path del fitxer.
	if(ObOBJ != NULL)
	{
		XMLWriter* escriptura = new XMLWriter(nomfitx, EManager, MManager,1);
		escriptura->Guardar();
		delete escriptura;
	}


	// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnMuscleEdit()
{
	editMuscle = !editMuscle;
	if (!editMuscle)
	{
		ChangeMuscleState(NONE_MUSCLE);
		SetRenderMuscle(selectedMuscle);
		//TODO Cridar funció de EditorManager per tal de guardar les dades a Muscles
		editor->SaveMuscle();
		TeclaControl = false;
		TeclaTab = false;
	}

	// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateMuscleEdit(CCmdUI *pCmdUI)
{
	if(editMuscle)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::SwitchMuscle(TypeMuscle m)
{
	if (selectedMuscle != m)
	{
		if (ObOBJ != NULL)
			editor->SetMuscle(m);

		if (editExpression)
		{
			ChangeMuscleState(m);
			//TODO Aquí hi va quan es defineixen els vectors directors
			SetRenderMuscle(selectedMuscle);
			if (deform != NULL)
			{
				deform->SetExpression(selectedExpression);
				deform->SetMuscle(selectedMuscle);
			}
		}
		else if (editMuscle)
		{
			ChangeMuscleState(m);
			SetRenderMuscle(selectedMuscle);
			//TODO Aquí hi va el codi quan es defineixen els muscles
			/*if (ObOBJ != NULL)
				editor->SetMuscle(DCELLA);*/
		
		}
		else
		{
			ChangeMuscleState(m);
			//TODO Aquí hi va el codi quan es visualitza el muscle sense editar
			SetRenderMuscle(selectedMuscle);
		}
	}
	else
	{
		selectedMuscle = NONE_MUSCLE;
		SetRenderMuscle(selectedMuscle);
	}

	// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnMCellesDreta()
{
	SwitchMuscle(DCELLA);
}

void CPracticaView::OnUpdateMCellesDreta(CCmdUI *pCmdUI)
{
	if(selectedMuscle == DCELLA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMCellesEsquerra()
{
	SwitchMuscle(ECELLA);
}

void CPracticaView::OnUpdateMCellesEsquerra(CCmdUI *pCmdUI)
{
	if(selectedMuscle == ECELLA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMBocaDreta()
{
	SwitchMuscle(DBOCA);
}

void CPracticaView::OnUpdateMBocaDreta(CCmdUI *pCmdUI)
{
	if(selectedMuscle == DBOCA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMBocaEsquerre()
{
	SwitchMuscle(EBOCA);
}

void CPracticaView::OnUpdateMBocaEsquerre(CCmdUI *pCmdUI)
{
	if(selectedMuscle == EBOCA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMBocaInferior()
{
	SwitchMuscle(INFBOCA);
}

void CPracticaView::OnUpdateMBocaInferior(CCmdUI *pCmdUI)
{
	if(selectedMuscle == INFBOCA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMParpellesDreta()
{
	SwitchMuscle(DPARPELLA);
}

void CPracticaView::OnUpdateMParpellesDreta(CCmdUI *pCmdUI)
{
	if(selectedMuscle == DPARPELLA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMParpellesEsquerra()
{
	SwitchMuscle(EPARPELLA);
}

void CPracticaView::OnUpdateMParpellesEsquerra(CCmdUI *pCmdUI)
{
	if(selectedMuscle == EPARPELLA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMGaltesDreta()
{
	SwitchMuscle(DGALTA);
}

void CPracticaView::OnUpdateMGaltesDreta(CCmdUI *pCmdUI)
{
	if(selectedMuscle == DGALTA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMGaltesEsquerra()
{
	SwitchMuscle(EGALTA);
}

void CPracticaView::OnUpdateMGaltesEsquerra(CCmdUI *pCmdUI)
{
	if(selectedMuscle == EGALTA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMBocaSuperior()
{
	SwitchMuscle(SUPBOCA);
}

void CPracticaView::OnUpdateMBocaSuperior(CCmdUI *pCmdUI)
{
	if(selectedMuscle == SUPBOCA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMBocaLateralE()
{
	SwitchMuscle(LATEBOCA);
}

void CPracticaView::OnUpdateMBocaLateralE(CCmdUI *pCmdUI)
{
	if(selectedMuscle == LATEBOCA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMBocaLateralD()
{
	SwitchMuscle(LATDBOCA);
}

void CPracticaView::OnUpdateMBocaLateralD(CCmdUI *pCmdUI)
{
	if(selectedMuscle == LATDBOCA)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMBocaDentDalt()
{
	SwitchMuscle(DENTDALT);
}

void CPracticaView::OnUpdateMBocaDentDalt(CCmdUI *pCmdUI)
{
	if(selectedMuscle == DENTDALT)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnMBocaDentBaix()
{
	SwitchMuscle(DENTBAIX);
}

void CPracticaView::OnUpdateMBocaDentBaix(CCmdUI *pCmdUI)
{
	if(selectedMuscle == DENTBAIX)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::ChangeMuscleState ( TypeMuscle muscle )
{
	//this->SwitchMuscle(selectedMuscle);
	selectedMuscle = muscle;
}
/* ------------------------------------------------------------------------- */
/*					11. EXPRESSIONS											 */
/* ------------------------------------------------------------------------- */
void CPracticaView::OnImportExpressions()
{
	// Obrir diàleg de lectura de fitxer
	CFileDialog openXML (TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,
		_T("XML Files(*.xml)|*.xml|All Files (*.*)|*.*||"));;

	if (openXML.DoModal() != IDOK)	return;  // stay with old data file
	else nom=openXML.GetPathName();

	// Conversió de la variable CString nom a la variable char *nomfitx, compatible amb la funció carregar3DS
	char * nomfitx = (char *)(LPCTSTR)nom;

	//Cridar al parsejador de fitxers XML per carregar les expressions.
	// La variable nomfitx conté tot el path del fitxer.
	if (ObOBJ != NULL)
	{
		XMLReader* lector = new XMLReader(nomfitx, EManager, MManager);
		lector->Read();
		delete lector;
	}

	// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnExportExpressions()
{
	//  Obrir diàleg d'escriptura de fitxer (fitxers *.MNT)
	CFileDialog openExportXML (FALSE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY ,
		_T("XML Files(*.xml)|*.xml|All Files (*.*)|*.*||"));;

	if (openExportXML.DoModal() != IDOK)
		return;                 // stay with old data file
    else
	   {nom=openExportXML.GetPathName();}

	nom = nom + CString(".xml");
	// Conversió de la variable CString nom a la variable char *nomfitx, compatible amb la funció carregar3DS
	char * nomfitx = (char *)(LPCTSTR)nom;

	// La variable nomfitx conté tot el path del fitxer.
	if (ObOBJ != NULL)
	{
		XMLWriter* escriptura = new XMLWriter(nomfitx, EManager, MManager,0);
		escriptura->Guardar();
		delete escriptura;
	}


	// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnExpressionEdit()
{
	if (editMuscle)
		editor->SaveMuscle();

	editExpression = !editExpression;


	// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnUpdateExpressionEdit(CCmdUI *pCmdUI)
{
	if(editExpression)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::SwitchExpression(TypeExpression e)
{
	if (ObOBJ != NULL && !animacio)
		this->ObOBJ->resetMoviments();

	if (!anima)
	{
		if (selectedExpression != e)
		{
			if (editExpression)
				ChangeExpressionState(e);
			else
			{
				ChangeExpressionState(e);
				if (!this->animacio)
					EManager->RenderExpression(selectedExpression);
				else
					SetAndStartAnimation(selectedExpression);
			}
		}
		else
		{
			if (!this->animacio)
				selectedExpression = NONE_EXPRESSION;
		}
	}

	// Crida a OnPaint() per redibuixar l'escena
	Invalidate();
}

void CPracticaView::OnExpTrist()
{
	SwitchExpression(TRIST);
}
void CPracticaView::OnUpdateExpTrist(CCmdUI *pCmdUI)
{
	if(selectedExpression == TRIST)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnExpAlegre()
{
	SwitchExpression(ALEGRE);
}

void CPracticaView::OnUpdateExpAlegre(CCmdUI *pCmdUI)
{
	if(selectedExpression == ALEGRE)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnExpEnfadat()
{
	SwitchExpression(ENFADAT);
}

void CPracticaView::OnUpdateExpEnfadat(CCmdUI *pCmdUI)
{
	if(selectedExpression == ENFADAT)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnExpSerios()
{
	SwitchExpression(SERIOS);
}

void CPracticaView::OnUpdateExpSerios(CCmdUI *pCmdUI)
{
	if(selectedExpression == SERIOS)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnExpSorpres()
{
	SwitchExpression(SORPRES);
}

void CPracticaView::OnUpdateExpSorpres(CCmdUI *pCmdUI)
{
	if(selectedExpression == SORPRES)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnLletresA()
{
	SwitchExpression(A);
}

void CPracticaView::OnUpdateLletresA(CCmdUI *pCmdUI)
{
	if(selectedExpression == A)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnLletresE()
{
	SwitchExpression(E);
}

void CPracticaView::OnUpdateLletresE(CCmdUI *pCmdUI)
{
	if(selectedExpression == E)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnLletresI()
{
	SwitchExpression(I);
}

void CPracticaView::OnUpdateLletresI(CCmdUI *pCmdUI)
{
	if(selectedExpression == I)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnLletresO()
{
	SwitchExpression(O);
}

void CPracticaView::OnUpdateLletresO(CCmdUI *pCmdUI)
{
	if(selectedExpression == O)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnLletresU()
{
	SwitchExpression(U);
}

void CPracticaView::OnUpdateLletresU(CCmdUI *pCmdUI)
{
	if(selectedExpression == U)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnLletresBilabial()
{
	SwitchExpression(BILABIAL);
}

void CPracticaView::OnUpdateLletresBilabial(CCmdUI *pCmdUI)
{
	if(selectedExpression == BILABIAL)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}

void CPracticaView::OnLletresNeutre()
{
	SwitchExpression(NEUTRE);
}

void CPracticaView::OnUpdateLletresNeutre(CCmdUI *pCmdUI)
{
	if(selectedExpression == NEUTRE)
		 pCmdUI->SetCheck(1);
	else
		 pCmdUI->SetCheck(0);
}


void CPracticaView::ChangeExpressionState ( TypeExpression expression )
{
	//this->SwitchExpression(selectedExpression);
	selectedExpression = expression;
}

void CPracticaView::SetAndStartAnimation( TypeExpression expression )
{
	animate->SetTime(4, temporitzador);
	animate->StartAnimation(expression);
	SetTimer(WM_TIMER,4,NULL);	
}

/* ------------------------------------------------------------------------- */
/*					12. ANIMACIÓ											 */
/* ------------------------------------------------------------------------- */
void CPracticaView::OnAnimacio()
{
	animacio = !animacio;
}

void CPracticaView::OnUpdateAnimacio(CCmdUI *pCmdUI)
{
	if (animacio)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CPracticaView::OnVFast()
{
	temporitzador = 0.05f;
	tempsParla = 0.005f;
	parla->SetVelocity(1.f, 0.005f);
}

void CPracticaView::OnUpdateVFast(CCmdUI *pCmdUI)
{
	if (temporitzador == 0.05f)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CPracticaView::OnFast()
{
	temporitzador = 0.1f;
	tempsParla = 0.01f;
	parla->SetVelocity(1.f, 0.007f);
}

void CPracticaView::OnUpdateFast(CCmdUI *pCmdUI)
{
	if (temporitzador == 0.1f)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CPracticaView::OnNormal()
{
	temporitzador = 0.5f;
	tempsParla = 0.02f;
	parla->SetVelocity(1.f, 0.01f);
}

void CPracticaView::OnUpdateNormal(CCmdUI *pCmdUI)
{
	if (temporitzador == 0.5f)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CPracticaView::OnSlow()
{
	temporitzador = 1.f;
	tempsParla = 0.1f;
	parla->SetVelocity(1.f, 0.03f);
}

void CPracticaView::OnUpdateSlow(CCmdUI *pCmdUI)
{
	if (temporitzador == 1.f)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CPracticaView::OnVSlow()
{
	temporitzador = 3.f;
	tempsParla = 0.3f;
	parla->SetVelocity(1.f, 0.09f);
}

void CPracticaView::OnUpdateVSlow(CCmdUI *pCmdUI)
{
	if (temporitzador == 3.f)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CPracticaView::OnParla()
{
	subtitles = true;
	SetTimer(WM_TIMER,4,NULL);
	parla->StartTalk();

	// Crida el OnPaint() per a redibuixar l'escena
	Invalidate();
}

