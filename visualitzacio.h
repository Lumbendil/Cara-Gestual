//******** PRACTICA GRAFICS PER COMPUTADOR 2
//******** Entorn bàsic VS2005 MONOFINESTRA amb interfície MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Febrer 2010)
// visualitzacio.h : Interface de visualitzacio.cpp
//

#ifndef GLVIS_H
#define GLVIS_H

#include "stdafx.h"
#include "Seleccions/Selection.h"
#include "Muscles/MuscleManager.h"
#include "Seleccions/EditorManager.h"

/* ------------------------------------------------------------------------- */
/*                                Funcions                                   */
/* ------------------------------------------------------------------------- */

void RenderBox (float x1, float y1, float x2, float y2);
void SetRenderMuscle ( TypeMuscle numMuscle );

// G2: Il.luminació
void Iluminacio(char ilumin,bool textur,char obj,bool bc_lin,int step);

// G2: Projecció Ortografica;
void Projeccio_Orto();
void Ortografica(int prj,CColor col_fons,char objecte,bool TR, 
				 CPunt3D VScl,CPunt3D VTr,CPunt3D VRot,bool oculta,bool testv,
				 bool bck_ln,char iluminacio,bool textur,bool ifix,bool eix);

// G2: Projecció Perspectiva
void Projeccio_Perspectiva(int,int,GLsizei,GLsizei,float);
void Perspectiva(float anglex,float angley,float R,char VPol,bool pant,GLfloat tr[3],
				 CColor col_fons,char objecte,bool TR,
				 CPunt3D VScl,CPunt3D VTr, CPunt3D VRot,bool oculta,bool testv,
				 bool bck_ln,char iluminacio,bool textur,bool ifix,bool eix,
				 EditorManager* EdManager, Objecte3D* ObOBJ, MuscleManager* MManager, bool flags);

void PerspectivaN(CPunt3D pv,bool pvb,GLfloat n[3],GLfloat v[3],
				 bool pant,GLfloat tr[3],CColor col_fons,char objecte,bool color,
				 bool TR,CPunt3D VScl,CPunt3D VTr,CPunt3D VRot,
				 bool oculta,bool testv,bool bck_ln,char iluminacio,
				 bool textur,bool ifix,bool eix);

// G2: Dibuix dels eixos de coordenades
void deixos(void);

// G2: Esborrats de pantalla a fons variable (Fons), negre (Fons) o a blanc (FonsW)
void Fons(CColor int_fons);
void FonsB(void);
void FonsN(void);

// G2: Carregar fitxer BMP com a textura
bool loadBMP(CString filename, int texID);

// G2: Carregar fitxer imatge de formats admesos per la llibreria DevIL/OpenIL 
//		com a textura
bool loadIMA(CString filename, int texID);

// Textures Objecte Truck
void Init_Textures();

GLdouble* GetProjectionMatrix (void);
GLint* GetViewportMatrix (void);
GLdouble* GetModelviewMatrix (void);

#endif