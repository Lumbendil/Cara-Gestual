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

#include "CollisionManager.h"
#include "SPoint3D.h"
#include "objLoader.h"
#include "intersection.h"

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
	SPoint3D cordenades,normal;
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
		int PuntMesProxim(SPoint3D);
		SPoint3D RetornaPunt ( int );
		int GetNumVertexs ( void );
		/*
		Dibuixa la funció
		*/
		void Dibuixar(int list); 
		/*
		Canvia el punt n per el nouPunt
		*/
		void mourePunt(int, SPoint3D);
		int buscarPunt(SPoint3D);

		//Mètodes per al Rigging
		int LineSelect (const SPoint3D &LP1, const SPoint3D &LP2);
		void GetTriangle ( int index, SPoint3D* triangle );
		int GetNumTriangles ( void );
		void SetFlagsTriangles ( void );
		void SelectTriangle	( int nTri );
		void SetSelectionMode ( int nMode );
		int FrustumSelect ( SPoint3D Normals[4], SPoint3D Points[8] );
		bool IsTriangleSelected ( int nTri );

		enum SelectionModes{ SELECT_ADD, SELECT_SUB };
		enum TriFlags{ TF_SELECTED = 1, NTF_SELECTED = 2, TF_BACKFACING = (1<<1) };
		
	private:
		Cara *cares;
		Punt *punts;
		O3DMaterial *materials;
		bool teNormals;
		int  nombrePunts,nombreMaterials;
		int nombreCares;
		void Objecte3DDeOBJ(char* filename);
		void Objecte3DDe3DS(char* filename);
		void UseMaterial(O3DMaterial pMaterial);
		SPoint3D Objecte3D::GetFaceNormal(const Cara*);

		int m_nSelMode;
		int *m_pTriFlags;
};

#endif
