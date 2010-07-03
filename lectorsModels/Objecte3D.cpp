#include "../stdafx.h"
#include "Objecte3D.h"
#include "objLoader.h"
#include "Obj3DS.h"
#include "../Seleccions/intersection.h"

Objecte3D::Objecte3D(char* filename, int tipus) {
	this->materials = NULL;
	this->cares = NULL;
	this->punts = NULL;
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

	this->punts = new Punt[numpunts];
	this->nombrePunts = numpunts;
	
	this->resetMoviments();
	for (i = 0; i < numpunts; i++) {
		this->punts[i].cordenades = SPoint3D(ob.pVertices[i].fX,ob.pVertices[i].fY,ob.pVertices[i].fZ);
		if (ob.pTexCoords != NULL)
		{
			this->punts[i].cordTex.x = ob.pTexCoords[i].fX;
			this->punts[i].cordTex.y = ob.pTexCoords[i].fY;
		}
	}

	numcares = o->GetNumFaces();

	this->cares = new Cara[numcares];
	this->nombreCares = numcares;

	for (i = 0; i < numcares; ++i) {
		for (j = 0; j < 3; ++j) {
			this->cares[i].punts[j] = &(this->punts[this->buscarPunt(SPoint3D(ob.pFaces[i].pVertices[j].fX,ob.pFaces[i].pVertices[j].fY,ob.pFaces[i].pVertices[j].fZ))]);
			if (ob.pNormals != NULL)
			{
				this->cares[i].normals[j] = SPoint3D(ob.pFaces[i].pNormals[j].fX,ob.pFaces[i].pNormals[j].fY,ob.pFaces[i].pNormals[j].fZ);
			}
			// TODO: Controlar que tenen textures
			if (ob.pTexCoords != NULL)
			{
				this->cares[i].materialTextura = ob.pFaces[i].iMaterialIndex;
				this->cares[i].cordTex[j].x = ob.pFaces[i].pTexCoords[j].fX;
				this->cares[i].cordTex[j].y = ob.pFaces[i].pTexCoords[j].fY;
			}
		}
	}
	if (ob.pMaterials != NULL)
	{
		this->nombreMaterials = o->GetNumMaterials();
		this->materials = new O3DMaterial[this->nombreMaterials];
	}
	else
	{
		this->nombreMaterials = 0;
		this->materials = NULL;
	}

	memcpy(this->materials,ob.pMaterials,sizeof(O3DMaterial) * this->nombreMaterials);

	delete o;
}

void Objecte3D::Objecte3DDe3DS(char* filename)
{
	Obj_3DS *o = new Obj_3DS();
	t3DObject *objecte;
	int i,j,objectes;
	int offsetPunts, offsetCares,npunts,ncares;


	o->Carregar3DS(filename);
	this->nombreCares = 0;
	this->nombrePunts = 0;

	for (objectes = 0; objectes < o->g_3DModel.numOfObjects; objectes++) {
		objecte = &(o->g_3DModel.pObject[objectes]);
		offsetPunts = this->nombrePunts;
		offsetCares = this->nombreCares;

		npunts = objecte->numOfVerts;
		this->nombrePunts += objecte->numOfVerts;
		this->punts = (Punt*) realloc(this->punts,this->nombrePunts*sizeof(Punt));
		for (i = 0; i < npunts; i++) {
			this->punts[i + offsetPunts].cordenades = SPoint3D(objecte->pVerts[i].x,objecte->pVerts[i].y,objecte->pVerts[i].z);
		}

		ncares = objecte->numOfFaces;
		this->nombreCares += objecte->numOfFaces;
		this->cares = (Cara*) realloc(this->cares,this->nombreCares*sizeof(Cara));
		for (i = 0; i < ncares; i++) {
			for (j = 0; j < 3; j++) {
				this->cares[i + offsetCares].punts[j] = &(this->punts[objecte->pFaces[i].vertIndex[j] + offsetPunts]);
				this->cares[i + offsetCares].cordTex[j].x = objecte->pTexVerts[objecte->pFaces[i].vertIndex[j]].x;
				this->cares[i + offsetCares].cordTex[j].y = objecte->pTexVerts[objecte->pFaces[i].vertIndex[j]].y;
				this->cares[i + offsetCares].materialTextura = objecte->materialID;
			}
		}
	}

	this->nombreMaterials = o->g_3DModel.numOfMaterials;
	this->materials = new O3DMaterial[this->nombreMaterials];
	for (i = 0; i < this->nombreMaterials; i++) {
		strcpy(this->materials[i].szTexture,o->g_3DModel.pMaterials[i].strFile);
		strcpy(this->materials[i].szName,o->g_3DModel.pMaterials[i].strName);
		this->materials[i].iTextureID = o->g_Texture[o->g_3DModel.pMaterials[i].texureId];
	}

	this->resetMoviments();

	o->EliminarMemoria();
	delete o;
}

int Objecte3D::buscarPunt(SPoint3D punt) {
	int i;
	for (i = 0;this->punts[i].cordenades != punt; i++);
	return i;
}

Objecte3D::~Objecte3D()
{
	delete [] punts;
	delete [] materials;
	delete [] cares;
}

int Objecte3D::PuntMesProxim(SPoint3D p)
{
	int millorPunt = 0;
	double distMin = this->punts[0].cordenades.calcularDistancia(p),distancia;
	for (int i = 1; i < this->nombrePunts; i++) {
		distancia = this->punts[i].cordenades.calcularDistancia(p);
		if (distancia < distMin) {
			millorPunt = i;
			distMin = distancia;
		}
	}
	return millorPunt;
}

SPoint3D Objecte3D::GetPoint(int punt)
{
	return this->punts[punt].cordenades;
}

SPoint3D Objecte3D::GetMovement(int punt)
{
	return this->punts[punt].moviment;
}

int Objecte3D::GetNumVertexs ( void )
{
	return nombrePunts;
}

// TODO: Recalcular les normals
void Objecte3D::mourePunt(int punt, SPoint3D vectorMoviment)
{
	this->punts[punt].moviment = vectorMoviment;
}

// Funcions Privades
void Objecte3D::UseMaterial(const O3DMaterial pMaterial)
{
	glColor3f(1.0,1.0,1.0);
	if (pMaterial.iTextureID > -1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, pMaterial.iTextureID);
	}
	else
		glDisable(GL_TEXTURE_2D);
}

SPoint3D Objecte3D::GetFaceNormal(const Cara *cara)
{
	SPoint3D p1,p2,normal;
	p1 = cara->punts[0]->cordenades - cara->punts[1]->cordenades;
	p2 = cara->punts[1]->cordenades - cara->punts[2]->cordenades;
	normal = SPoint3D(p1.y*p2.z - p1.z*p2.y,p1.z*p2.x - p1.x*p2.z,p1.x*p2.y - p1.y*p2.x);
	normal.normalizeVector();
	return normal;
}

void Objecte3D::GetTriangle ( int index, SPoint3D* triangle )
{
	triangle[0] = this->cares[index].punts[0]->cordenades;
	triangle[1] = this->cares[index].punts[1]->cordenades;
	triangle[2] = this->cares[index].punts[2]->cordenades;
}

int Objecte3D::GetNumTriangles ( void )
{
	return nombreCares;
}

void Objecte3D::GetFaceCoords ( int nFace, SPoint3D* coords )
{
	coords[0] = this->cares[nFace].punts[0]->cordenades;
	coords[1] = this->cares[nFace].punts[1]->cordenades;
	coords[2] = this->cares[nFace].punts[2]->cordenades;
}

SPoint3D Objecte3D::GetNormalsFace ( int nFace )
{
	return this->GetFaceNormal(&this->cares[nFace]);
}

void Objecte3D::Render ( void )
{
	int iPreviousMaterial = -1,i,j;
	glPushAttrib(GL_TEXTURE_BIT);
	this->CalcularNormalsVertex();

	if (this->nombreMaterials == 0)
	{
		// Posa una textura nul·la
		O3DMaterial material;
		material.iTextureID = -1;
		UseMaterial(material);
	}

	for (i=0; i < this->nombreCares; i++)
	{
		if (this->nombreMaterials != 0 && iPreviousMaterial != (int) this->cares[i].materialTextura)
		{
			iPreviousMaterial = this->cares[i].materialTextura;
			UseMaterial(this->materials[iPreviousMaterial]);
		}
		glBegin(GL_TRIANGLES);

		// Calculate and set face normal if no vertex normals are specified
		//if (!this->teNormals) {
			//SPoint3D fNormal = GetFaceNormal(&this->cares[i]);
			//glNormal3fv(fNormal);
		//}
		// Process all vertices
		for (j=0; j < 3; j++)
		{
			//if (this->teNormals) {
			//	glNormal3fv(this->cares[i].normals[j]);
			glNormal3fv(this->cares[i].normals[j]);
			//}

			// Set texture coordinates (if any specified)
			//if (this->cares[i].punts[j]->cordTex)
			glTexCoord2f(this->cares[i].cordTex[j].x,this->cares[i].cordTex[j].y);

			// Set vertex
			glVertex3fv(this->cares[i].punts[j]->cordenades + this->cares[i].punts[j]->moviment);
		}
		glEnd();
	}
	glPopAttrib();
}

void Objecte3D::resetMoviments()
{
	for (int i = 0; i < this->nombrePunts; i++) {
		this->punts[i].moviment = SPoint3D(0,0,0);
	}
}

void Objecte3D::CalcularNormalsVertex()
{
	int i,j;
	SPoint3D p;
	for (i = 0; i < this->nombrePunts; i++) {
		this->punts[i].normal = SPoint3D(0.0, 0.0, 0.0);
	}
	for (i = 0; i < this->nombreCares; i++) {
		p = this->GetNormalsFace(i);
		for (j = 0; j < 3; j++) {
			this->cares[i].punts[j]->normal += p;
		}
	}
	for (i = 0; i < this->nombrePunts; i++) {
		this->punts[i].normal.normalizeVector();
	}
}