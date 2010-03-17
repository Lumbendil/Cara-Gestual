//******** PRACTICA GRAFICS PER COMPUTADOR 2
//******** Entorn bàsic VS2005 MONOFINESTRA amb interfície MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Febrer 2010)
// stdafx.h : include file for standard system include files,
//            or project specific include files that are used frequently, 
//            but are changed infrequently
//

#if !defined(AFX_STDAFX_H__17E9D4E8_BD1C_11D2_A09D_0060081D77EF__INCLUDED_)
#define AFX_STDAFX_H__17E9D4E8_BD1C_11D2_A09D_0060081D77EF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls



/* ------------------------------------------------------------------------- */
/*                                INCLUDES                                   */
/* ------------------------------------------------------------------------- */

// GC2: Llibreries OpenGL
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <gl\glut.h>

// GC2: Llibreries DevIL/OpenIL per llegir imatges de diferents formats 
//     (BMP,JPG,TIF,GIF,etc.) en la funció loadIMA (visualitzacio.cpp)
//#include <il\il.h>
//#include <il\ilu.h>
#include <il\ilut.h>

// GC2: Includes per lectura fitxers, funcions trigonomètriques i nombres aleatoris.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// GC2: Constants de l'aplicació Practica
#include "constants.h"

#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__17E9D4E8_BD1C_11D2_A09D_0060081D77EF__INCLUDED_)
