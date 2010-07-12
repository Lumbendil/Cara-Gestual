//******** PRACTICA GRAFICS PER COMPUTADOR 2
//******** Entorn b�sic VS2005 MONOFINESTRA amb interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Febrer 2010)
// escena.h : interface de escena.cpp
//

#ifndef GLSOURCE_H
#define GLSOURCE_H

#include "SPoint3D.h"
#include "Seleccions/Selection.h"
#include "lectorsModels/Objecte3D.h"
#include "Muscles/MuscleManager.h"
#include "Seleccions/EditorManager.h"

/* ------------------------------------------------------------------------- */
/*                            Funcions de les escenes                        */
/* ------------------------------------------------------------------------- */
void dibuixa(char obj);

// Truck
void truck(bool textu,GLuint VTextu[NUM_MAX_TEXTURES]);
void neumatic(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void llanta(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void sea(void);
void renderSphereSelection (EditorManager* EdManager, TypeMuscle muscle);
void drawSelectionBox	(float x1, float y1, float x2, float y2);
void WireRect( float x1, float y1, float x2, float y2 );
void SetProjection3D();
void SetProjection2D();
void DrawLine( const SPoint3D &P1, const SPoint3D &P2 );
void DrawSubtitles ( void );
#endif