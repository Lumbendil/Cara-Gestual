#include "stdafx.h"
#include "Objecte3D.h"
//#include <stdio.h>
#include "objLoader.h"
#include "constants.h"

Objecte3D::Objecte3D(char* filename, int tipus) {
	switch (tipus) {
		case 1: this->Objecte3DDeOBJ(filename);
			break;
		case 2: this->Objecte3DDe3DS(filename);
			break;
		default: printf("Tipus invalid\n");
	}
}
void Objecte3D::Objecte3DDeOBJ(char* filename) {
	int numpunts,numcares,i,j;
	Punt p;

	COBJModel *o = new COBJModel();
	o->LoadModel(filename,NULL);
	ModelOBJ ob = o->GetModel();

	numpunts = o->GetNumVertices();
	this->punts = (Punt*) malloc(sizeof(Punt) * numpunts);
	this->nombrePunts = numpunts;

	for (i = 0; i < numpunts; i++) {
		this->punts[i].cordenades = Point3D(ob.pVertices[i].fX,ob.pVertices[i].fY,ob.pVertices[i].fZ);
		this->punts[i].normal = Point3D(ob.pNormals[i].fX,ob.pNormals[i].fY,ob.pNormals[i].fZ);

		this->punts[i].cordTex.x = ob.pTexCoords[i].fX;
		this->punts[i].cordTex.y = ob.pTexCoords[i].fY;
	}

	numcares = o->GetNumFaces();
	this->cares = ( Cara * ) malloc(sizeof(Cara) * numcares);
	this->nombreCares = numcares;

	for (i = 0; i < numcares; i++) {
		if (ob.pFaces[i].iNumVertices == 3) {
			for (j = 0; j < 3; j++) {
				p.cordenades = Point3D(ob.pFaces[i].pVertices[j].fX,ob.pFaces[i].pVertices[j].fY,ob.pFaces[i].pVertices[j].fZ);
				this->cares[i].punts[j] = this->buscarPunt(p);
				this->cares[i].materialTextura = ob.pFaces[i].iMaterialIndex;
				// TODO: Cordenades de textura de cada vertex ¿?
			}
		} else {
			// Error
		}
	}
	this->nombreMaterials = o->GetNumMaterials();
	this->materials = ( O3DMaterial * ) malloc(sizeof(O3DMaterial) * this->nombreMaterials);
	// Copiar guarro
	memcpy(this->materials,ob.pMaterials,sizeof(O3DMaterial) * this->nombreMaterials);
}

Punt* Objecte3D::buscarPunt(Punt p) {
	int i;
	for (i = 0;(this->punts[i].cordenades.x != p.cordenades.x || this->punts[i].cordenades.y != p.cordenades.y || this->punts[i].cordenades.z != p.cordenades.z) && i < this->nombrePunts; i++);
	return &(this->punts[i]);
}
void Objecte3D::Objecte3DDe3DS(char* filename)
{
}
Objecte3D::~Objecte3D()
{
}
int Objecte3D::PuntMesProxim(Punt p)
{
	return 0;
}
	/*
	Dibuixa la funció
	*/
void Objecte3D::Dibuixar(int list)
{
	int iPreviousMaterial = -1,i,j;

	glNewList(m_iDisplayList, GL_COMPILE);
	// Save texture bit to recover from the various texture state changes
	glPushAttrib(GL_TEXTURE_BIT);

	for (i=0; i < this->nombreCares; i++)
	{
		if (iPreviousMaterial != (int) this->cares[i].materialTextura)
		{
			iPreviousMaterial = this->cares[i].materialTextura;
			UseMaterial(this->materials[iPreviousMaterial]);
		}
		glBegin(GL_TRIANGLES);
		// Calculate and set face normal if no vertex normals are specified
		if (!pFaces[i].pNormals)
		{
			GetFaceNormal(fNormal, &pFaces[i]);
			glNormal3fv(fNormal);
		}
		// Process all vertices
		for (j=0; j < 3; j++)
		{
			// Set vertex normal (if vertex normals are specified)
			if (this->cares[i].punts[j]->normal)
				glNormal3f(this->cares[i].punts[j]->normal);

			// Set texture coordinates (if any specified)
			if (this->cares[i].punts[j]->cordTex)
				glTexCoord2f(this->cares[i].punts[j]->cordTex);

			// Set vertex
			glVertex3f(this->cares[i].punts[j]->cordenades);
		}

		glEnd();	
	}

	glPopAttrib();
	glEndList();
}
/*
Retorna la cara amb index n 
*/
Cara Objecte3D::getCara(int n)
{
	Cara caraC;
	return caraC;
}
/*
Retorna el punt amb index n
*/
Punt Objecte3D::getPunt(int n)
{
	Punt point;
	return point;
}
/*
Canvia el punt n per el nouPunt
*/
void Objecte3D::editarPunt(int n, Punt nouPunt)
{
}
