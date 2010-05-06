//******** PRACTICA GRAFICS PER COMPUTADOR 2
///******** Entorn b�sic VS2005 MONOFINESTRA amb interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Febrer 2010)
// constants.h : Definici� de constants compartides a 
//				 CPracticaView.cpp, visualitzacio.cpp i escena.cpp

#include <math.h>


#ifndef CONST_H
#define CONST_H

//--------------- GC2: Tipus de Projecci�
#define CAP ' '
#define ORTO 'O'
#define PERSPECT 'P'

//--------------- GC2: Tipus de Polars (per la Visualitzaci� Interactiva)
#define POLARZ 'Z'
#define POLARY 'Y'
#define POLARX 'X'

//-------------- GC2: Tipus d'Objectes 
#define CUB 'c'
#define ESFERA 'e'
#define MALLA 'M' 
#define TETERA 't'
#define TRUCK 'T'
#define OBJ3DS '3'		// Objecte format 3DS
#define OBJOBJ '4'		// Objecte format OBJ

//-------------- GC2: Tipus d'Iluminacio
#define FILFERROS 'f'
#define PLANA 'p'
#define SUAU 's'

//-------------- GC2: Objectes precompilats OpenGL amb glNewList
#define EIXOS 1			// Eixos
#define FRACTAL 2		// Fractal
#define OBJECTE3DS 3	// Objecte 3DS
#define OBJECTE3DST 4	// Objecte 3DS amb textures
#define OBJECTEOBJ 5	// Objecte OBJ

// Definici� dels valors del pla near i far del Volum de 
// Visualitzaci� en Perspectiva
const int p_near=1;
const int p_far=5000;

// -------------- TEXTURES: Nombre m�xim de textures
#define NUM_MAX_TEXTURES 10

// -------------- TEXTURES: Tipus de textures
#define CAP ' '
#define FUSTA 'F'
#define MARBRE 'M'
#define METALL 'E'
#define FITXER 'f'

//--------------- GC2: Valor constant de pi
const double pi=3.14159;

// ------TRUCK: Resoluci� de les rodes (Nombre de divisions del cilindre i discos)
#define RESOLUCIO_RODA 16

// --------------- GC2: Estructura coordenada 3D
struct CPunt3D
{   GLfloat x;
    GLfloat y;
	GLfloat z;
};

// --------------- GC2: Estructura de color R,G,B
struct CColor
{   GLfloat r;
    GLfloat g;
	GLfloat b;
};


#endif