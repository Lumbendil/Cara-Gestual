//******** PRACTICA GRAFICS PER COMPUTADOR 2
//******** Entorn bàsic VS2005 MONOFINESTRA amb interfície MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Febrer 2010)
// escena.h : interface de escena.cpp
//

#ifndef GLSOURCE_H
#define GLSOURCE_H

#include "SPoint3D.h"
#include "Seleccions/Selection.h"
#include "lectorsModels/Objecte3D.h"
#include "Muscles/MuscleManager.h"

/* ------------------------------------------------------------------------- */
/*                            Funcions de les escenes                        */
/* ------------------------------------------------------------------------- */
void dibuixa(char obj);

// Truck
void truck(bool textu,GLuint VTextu[NUM_MAX_TEXTURES]);
void neumatic(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void llanta(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void sea(void);
void renderSphereSelection (Selection* select, Objecte3D* ObOBJ);
void drawSelectionBox	(float x1, float y1, float x2, float y2);
void WireRect( float x1, float y1, float x2, float y2 );
void SetProjection3D();
void SetProjection2D();
void DrawLine( const SPoint3D &P1, const SPoint3D &P2 );
void RenderSelectedMuscle( TypeMuscle muscle, MuscleManager* MManager);
#endif