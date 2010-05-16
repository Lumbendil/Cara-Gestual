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

#include "../SPoint3D.h"
#include "objLoader.h"
#include "../Seleccions/intersection.h"

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
	SPoint3D cordenades,normal,moviment;
	Point2D cordTex;
};

// Les cares es considera que son triangles.
// Es guarda la ID relacionada a cada punt.
struct Cara {
	Punt *punts[3];
	SPoint3D normals[3];
	int materialTextura;
	Point2D cordTex[3];
};

class Objecte3D {
	public:
		Objecte3D(char* file,int tipus);
		~Objecte3D();
		int PuntMesProxim(SPoint3D);
		SPoint3D RetornaPunt ( int );
		int GetNumVertexs ( void );
		// No guarda el moviment a dins del vertex!!!
		void mourePunt(int, SPoint3D);
		int buscarPunt(SPoint3D);
		void GetTriangle ( int index, SPoint3D* triangle );
		int GetNumTriangles ( void );
		void GetFaceCoords ( int nFace, SPoint3D* coords );
		SPoint3D GetNormalsFace ( int nFace );
		void Render( void );
		void resetMoviments();
		SPoint3D returnMoviment(int punt);
	private:
		Cara *cares;
		Punt *punts;
		SPoint3D *moviment;
		O3DMaterial *materials;
		bool teNormals;
		int  nombrePunts,nombreMaterials;
		int nombreCares;
		void Objecte3DDeOBJ(char* filename);
		void Objecte3DDe3DS(char* filename);
		void UseMaterial(O3DMaterial pMaterial);
		SPoint3D Objecte3D::GetFaceNormal(const Cara*);
};

#endif
