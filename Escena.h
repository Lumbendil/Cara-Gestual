//******** PRACTICA GRAFICS PER COMPUTADOR 2
//******** Entorn b�sic VS2005 MONOFINESTRA amb interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Febrer 2010)
// escena.h : interface de escena.cpp
//

#ifndef GLSOURCE_H
#define GLSOURCE_H

/* ------------------------------------------------------------------------- */
/*                            Funcions de les escenes                        */
/* ------------------------------------------------------------------------- */
void dibuixa(char obj);

// Truck
void truck(bool textu,GLuint VTextu[NUM_MAX_TEXTURES]);
void neumatic(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void llanta(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void sea(void);
#endif