//******** PRACTICA GRAFICS PER COMPUTADOR 2
//******** Entorn b�sic VS2005 MONOFINESTRA amb interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Febrer 2010)
// visualitzacio.h : Interface de visualitzacio.cpp
//

#ifndef GLVIS_H
#define GLVIS_H

/* ------------------------------------------------------------------------- */
/*                                Funcions                                   */
/* ------------------------------------------------------------------------- */

// G2: Il.luminaci�
void Iluminacio(char ilumin,bool textur,char obj,bool bc_lin,int step);

// G2: Projecci� Ortografica;
void Projeccio_Orto();
void Ortografica(int prj,CColor col_fons,char objecte,bool TR, 
				 CPunt3D VScl,CPunt3D VTr,CPunt3D VRot,bool oculta,bool testv,
				 bool bck_ln,char iluminacio,bool textur,bool ifix,bool eix);

// G2: Projecci� Perspectiva
void Projeccio_Perspectiva(int,int,GLsizei,GLsizei,float);
void Perspectiva(float anglex,float angley,float R,char VPol,bool pant,GLfloat tr[3],
				 CColor col_fons,char objecte,bool TR,
				 CPunt3D VScl,CPunt3D VTr, CPunt3D VRot,bool oculta,bool testv,
				 bool bck_ln,char iluminacio,bool textur,bool ifix,bool eix);

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
#endif