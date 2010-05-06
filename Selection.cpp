#include "stdafx.h"
#include "Selection.h"
#include "SPoint3D.h"
#include "matrix.h"
#include "Objecte3D.h"
#include "EditorManager.h"
#include "intersection.h"
#include "visualitzacio.h"
#include <gl/gl.h>
#include <gl/glu.h>

void inline swapInt( float &x, float &y )
{
	 float temp = x; 
	 x = y;
	 y = temp;
}

Selection::Selection(Objecte3D* obj, EditorManager* editor)
{
	ObOBJ = obj;
	editorM = editor;
	m_pTriFlags = NULL;
	if (obj != NULL)
		this->SetFlagsTriangles();
}
Selection::~Selection()
{
	free(ObOBJ);
}

//Al premer el botó esquerre
void Selection::ButtonDown( float mouseX, float mouseY )
{
	nStartX = mouseX;
	nStartY = mouseY;
	nEndX = mouseX;
	nEndY = mouseY;
    buttonState = true;	

	if (ObOBJ != NULL)
	{
		GetLine( m_vLineP[0], m_vLineP[1], mouseX, mouseY );	//Obtenim la línia que pertany a on s'ha clickat
		SetSelectionMode( SELECT_ADD );

		LineSelect(m_vLineP[0],m_vLineP[1]);	//Agafem l'índex del punt més proper a la col·lisió en aquell punt
	}
}

//Al moure el ratolí amb el botó apretat
void Selection::ButtonMove( float mouseX, float mouseY )
{
	if ( buttonState )
	{
		if ( mouseX < 32000 ) 
			nEndX = mouseX; 
		else 
			nEndX = 0;
		if ( mouseY < 32000 ) 
			nEndY = mouseY; 
		else 
			nEndY = 0;
		// (reason for if : when the mouse is beyond the window in a negative direction we end up with a high number )		
	}
}

//Al deixar el botó esquerre
void Selection::ButtonUp( void )
{
	buttonState = false;
	if ( abs( nEndX - nStartX ) < 4 && abs( nEndY - nStartY ) < 4 ) return;
	if ( nEndX < nStartX ) 
		swapInt( nEndX, nStartX );
	if ( nEndY < nStartY ) 
		swapInt( nEndY, nStartY );
	
	if (ObOBJ != NULL)
	{
		SPoint3D P[8];
		SPoint3D Normals[6];
		GetFrustum(Normals,P);
		FrustumSelect(Normals, P);
		//Cridar als mètodes de EditorManager per tal d'afegir els vèrtexs allà
	}
}

//Obté una línia d'allà on s'ha apretat en coordenades món
void Selection::GetLine( SPoint3D &L1, SPoint3D &L2, float mouseX, float mouseY )
{
	double* mvmatrix;
	double* projmatrix;
	int* Viewport;
	//int Viewport[4];
	double dX, dY, dZ, dClickY; // glUnProject uses doubles, but I'm using floats for these 3D vectors

	Viewport = GetViewportMatrix();
	mvmatrix = GetModelviewMatrix();
	projmatrix = GetProjectionMatrix();
	dClickY = double (Viewport[3] - mouseY); 
	// OpenGL renders with (0,0) on bottom, mouse reports with (0,0) on top

	gluUnProject ((double) mouseX, dClickY, 0.0, mvmatrix, projmatrix, Viewport, &dX, &dY, &dZ);
	L1 = SPoint3D( (float) dX, (float) dY, (float) dZ );
	gluUnProject ((double) mouseX, dClickY, 1.0, mvmatrix, projmatrix, Viewport, &dX, &dY, &dZ);
	L2 = SPoint3D( (float) dX, (float) dY, (float) dZ );
}

void Selection::GetFrustum( SPoint3D Normals[4], SPoint3D P[8])
{
	GetLine( P[0], P[1], nStartX, nStartY );
	GetLine( P[2], P[3], nStartX, nEndY );
	GetLine( P[4], P[5], nEndX, nEndY );
	GetLine( P[6], P[7], nEndX, nStartY );
	Normals[0] = (P[0]-P[1]).CrossProduct( P[2]-P[3] );
	Normals[1] = (P[2]-P[3]).CrossProduct( P[4]-P[5] );
	Normals[2] = (P[4]-P[5]).CrossProduct( P[6]-P[7] );
	Normals[3] = (P[6]-P[7]).CrossProduct( P[0]-P[1] );
	for (int i = 0; i < 4; i++) 
		Normals[i].normalizeVector();
}


void Selection::Render()
{
	if (buttonState)
		RenderBox(nStartX, nStartY, nEndX, nEndY);
}

void Selection::NoRender()
{
	RenderBox(0.0,0.0,0.0,0.0);
}

void Selection::SetObj( Objecte3D* obj )
{
	if (ObOBJ == NULL)
	{
		ObOBJ = obj;
		this->SetFlagsTriangles();
	}		
}

bool Selection::IsTriangleSelected ( int nTri )
{
	if (m_pTriFlags != NULL)
	{
		if (m_pTriFlags[nTri] == TF_SELECTED)
			return true;
		else
			return false;
	}
	else
		return false;
}

void Selection::SetFlagsTriangles ( void )
{
	m_pTriFlags = new int[ObOBJ->GetNumTriangles()];
}

void Selection::SetSelectionMode ( int nMode )
{
	m_nSelMode = nMode; 
}

void Selection::SelectTriangle	( int nTri )
{
	if ( nTri < 0 || nTri >= ObOBJ->GetNumTriangles() ) return;
	if ( m_nSelMode == SELECT_ADD ) 
		m_pTriFlags[ nTri ] = TF_SELECTED;
	if ( m_nSelMode == SELECT_SUB )
		m_pTriFlags[ nTri ] &= NTF_SELECTED;
}

int Selection::FrustumSelect ( SPoint3D Normals[4], SPoint3D Points[8] )
{
	int nbHits = 0;
	SPoint3D Tri[3];

	for (int nTri = 0; nTri < ObOBJ->GetNumTriangles(); ++nTri )
		{	
		int nV = nTri*3;
		ObOBJ->GetFaceCoords(nTri, Tri);

		if ( TriInFrustum( Tri, Normals, Points ) )
			{
			SelectTriangle( nTri );			
			++nbHits;			
			}
		}
	
	return nbHits;
}

//Mira el punt més proper en què col·lisiona el raig
int Selection::LineSelect (const SPoint3D &LP1, const SPoint3D &LP2 )
{
	SPoint3D HitP, pFace[3];
	int nbHits = 0;
	int nSelTri = -1;
	float fDistance = 1000000000.0f;
	
	for (int nTri = 0; nTri < ObOBJ->GetNumTriangles(); ++nTri )
	{
		int nV = nTri*3;	
	
		ObOBJ->GetFaceCoords(nTri, pFace);

		bool bHit = CheckLineTri( LP2, LP1, pFace[0], pFace[1], pFace[2], HitP );
		if ( bHit ) {
			if ( HitP.calcularDistancia( LP1 ) < fDistance ) {
				fDistance = HitP.calcularDistancia( LP1 );
				nSelTri = nTri;
				}
			++nbHits;
			}
	}
		
	SelectTriangle( nSelTri );
	
	return nbHits;
}