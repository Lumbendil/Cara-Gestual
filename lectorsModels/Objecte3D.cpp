#include "../stdafx.h"
#include "Objecte3D.h"
#include "objLoader.h"
#include "../Seleccions/intersection.h"

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
		this->punts[i].cordenades = SPoint3D(ob.pVertices[i].fX,ob.pVertices[i].fY,ob.pVertices[i].fZ);
		if (ob.pNormals) {
			this->punts[i].normal = SPoint3D(ob.pNormals[i].fX,ob.pNormals[i].fY,ob.pNormals[i].fZ);
			this->teNormals = true;
		} else {
			this->teNormals = false;
		}

		this->punts[i].cordTex.x = ob.pTexCoords[i].fX;
		this->punts[i].cordTex.y = ob.pTexCoords[i].fY;
	}

	numcares = o->GetNumFaces();
	this->cares = ( Cara * ) malloc(sizeof(Cara) * numcares);
	this->nombreCares = numcares;

	for (i = 0; i < numcares; ++i) {
		for (j = 0; j < 3; ++j) {
			this->cares[i].punts[j] = &(this->punts[this->buscarPunt(SPoint3D(ob.pFaces[i].pVertices[j].fX,ob.pFaces[i].pVertices[j].fY,ob.pFaces[i].pVertices[j].fZ))]);
			this->cares[i].normals[j] = SPoint3D(ob.pFaces[i].pNormals[j].fX,ob.pFaces[i].pNormals[j].fY,ob.pFaces[i].pNormals[j].fZ);
			// TODO: Controlar que tenen textures
			this->cares[i].materialTextura = ob.pFaces[i].iMaterialIndex;
			this->cares[i].cordTex[j].x = ob.pFaces[i].pTexCoords[j].fX;
			this->cares[i].cordTex[j].y = ob.pFaces[i].pTexCoords[j].fY;
		}
	}
	this->nombreMaterials = o->GetNumMaterials();
	this->materials = ( O3DMaterial * ) malloc(sizeof(O3DMaterial) * this->nombreMaterials);
	// Copiar guarro
	memcpy(this->materials,ob.pMaterials,sizeof(O3DMaterial) * this->nombreMaterials);

}

// TODO: Fer funció
void Objecte3D::Objecte3DDe3DS(char* filename)
{
}
int Objecte3D::buscarPunt(SPoint3D p) {
	int i;
	for (i = 0;this->punts[i].cordenades != p; i++);
	return i;
}
Objecte3D::~Objecte3D()
{
	free(this->punts);
	free(this->cares);
	free(this->materials);
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
SPoint3D Objecte3D::RetornaPunt(int punt)
{
	return this->punts[punt].cordenades;
}
int Objecte3D::GetNumVertexs ( void )
{
	return nombrePunts;
}

void Objecte3D::Dibuixar(int list)
{
	int iPreviousMaterial = -1,i,j;

	glNewList(list, GL_COMPILE);
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
		if (!this->teNormals)
		{
			SPoint3D fNormal = GetFaceNormal(&this->cares[i]);
			glNormal3fv(fNormal);
		}
		// Process all vertices
		for (j=0; j < 3; j++)
		{
			// Set vertex normal (if vertex normals are specified)
			//Sif (this->cares[i].punts[j]->normal)
				//glNormal3fv(this->cares[i].punts[j]->normal);
			glNormal3fv(this->cares[i].normals[j]);
			// Set texture coordinates (if any specified)
			//if (this->cares[i].punts[j]->cordTex)
				glTexCoord2f(this->cares[i].cordTex[j].x,this->cares[i].cordTex[j].y);
			// Set vertex
			glVertex3fv(this->cares[i].punts[j]->cordenades);
		}
		glEnd();	
	}
	glPopAttrib();
	glEndList();
}
// TODO: Recalcular les normals
void Objecte3D::mourePunt(int n, SPoint3D vectorMoviment)
{
	this->punts[n].cordenades += vectorMoviment;
}


// Funcions Privades
void Objecte3D::UseMaterial(const O3DMaterial pMaterial)
{
	////////////////////////////////////////////////////////////////////////
	// Make a given material the current one
	////////////////////////////////////////////////////////////////////////

	glColor3f(1.0,1.0,1.0);
	// Look for the presence of a texture and activate texturing if succeed
	//if (pMaterial!=NULL)
	//{
		if (pMaterial.iTextureID)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, pMaterial.iTextureID);
		}
		else
			glDisable(GL_TEXTURE_2D);
		
	//}
	//else
	//	glDisable(GL_TEXTURE_2D);
}

SPoint3D Objecte3D::GetFaceNormal(const Cara *cara)
{
	////////////////////////////////////////////////////////////////////////
	// Calculate normal for a given face
	////////////////////////////////////////////////////////////////////////

	// Only faces with at least 3 vertices can have a normal
	// Two vectors
	SPoint3D p1,p2,normal;

	// Calculate two vectors from the three points
	p1 = cara->punts[0]->cordenades - cara->punts[1]->cordenades;
	p2 = cara->punts[1]->cordenades - cara->punts[2]->cordenades;
	
	// Take the cross product of the two vectors to get the normal vector
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

	for (i=0; i < this->nombreCares; i++)
	{
		if (iPreviousMaterial != (int) this->cares[i].materialTextura)
		{
			iPreviousMaterial = this->cares[i].materialTextura;
			UseMaterial(this->materials[iPreviousMaterial]);
		}
		glBegin(GL_TRIANGLES);
		// Calculate and set face normal if no vertex normals are specified
		if (!this->teNormals)
		{
			SPoint3D fNormal = GetFaceNormal(&this->cares[i]);
			glNormal3fv(fNormal);
		}
		// Process all vertices
		for (j=0; j < 3; j++)
		{
			// Set vertex normal (if vertex normals are specified)
			//Sif (this->cares[i].punts[j]->normal)
				//glNormal3fv(this->cares[i].punts[j]->normal);
			glNormal3fv(this->cares[i].normals[j]);
			// Set texture coordinates (if any specified)
			//if (this->cares[i].punts[j]->cordTex)
				glTexCoord2f(this->cares[i].cordTex[j].x,this->cares[i].cordTex[j].y);
			// Set vertex
			glVertex3fv(this->cares[i].punts[j]->cordenades);
		}
		glEnd();	
	}
	glPopAttrib();
}