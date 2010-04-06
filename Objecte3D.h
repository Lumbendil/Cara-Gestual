#ifndef OBJECTE3D_H
#define OBJECTE3D_H

#define TIPUS_OBJ 1
#define TIPUS_3DS 2

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "SPoint3D.h"
#include "objLoader.h"

struct O3DMaterial
{
	char	szName[1024];		 // Name of the material
	char	szTexture[_MAX_PATH];// Filename of the texture
	int	iTextureID;			 // OpenGL name of the texture
	float fDiffuse[3];		 // Diffuse component
	float fAmbient[3];		 // Ambient component
	float fSpecular[3];		 // Specular component
	float fEmmissive[3];		 // Emmissive component
	float fShininess;			 // Specular exponent
};

struct Point2D {
	float x,y;
};

struct Punt {
	Point3D cordenades,normal;
	Point2D cordTex;
};

// Les cares es considera que son triangles.
// Es guarda la ID relacionada a cada punt.
struct Cara {
	Punt *punts[3];
	int materialTextura;
};

class Objecte3D {
	public:
		/*
		Constructor.
		El tipus seria 1 per a OBJ i 2 per a 3DS. 
		Aix� seria extensible a mes tipus.
		*/
		Objecte3D(char* file,int tipus);
		/*
		El destructor, que alliberaria tota la memoria
		*/
		~Objecte3D();
		/*
		Retorna l'identificador del punt de l'objecte mes proxim al
		punt p.
		*/
		int PuntMesProxim(Punt p);
		/*
		Dibuixa la funció
		*/
		void Dibuixar(int list); 
		/*
		Retorna la cara amb index n 
		*/
		Cara getCara(int n); 
		/*
		Retorna el punt amb index n
		*/
		Punt getPunt(int n);
		/*
		Canvia el punt n per el nouPunt
		*/
		void editarPunt(int n, Punt nouPunt);
	private:
		Cara *cares;
		Punt *punts;
		O3DMaterial *materials;
		int nombreCares, nombrePunts,nombreMaterials;
		void Objecte3DDeOBJ(char* filename);
		void Objecte3DDe3DS(char* filename);
		Punt* buscarPunt(Punt p);
};

#endif