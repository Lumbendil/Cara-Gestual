#include "stdafx.h"
#include "Selection.h"
#include "SPoint3D.h"
#include "matrix.h"
#include "Objecte3D.h"
#include "EditorManager.h"

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

	GetLine( m_vLineP[0], m_vLineP[1], mouseX, mouseY );	//Obtenim la línia que pertany a on s'ha clickat
	int index = ObOBJ->LineSelect(m_vLineP[0],m_vLineP[1]);	//Agafem l'índex del punt més proper a la col·lisió en aquell punt
	SPoint3D puntTrobat = ObOBJ->RetornaPunt(index);		//Obtenim les coordenades del punt
	editorM->AddVertex(puntTrobat, ObOBJ);					//Afegim el vèrtex a la llista de vèrtexs sel·leccionats
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

	SPoint3D P[8];
	SPoint3D Normals[6];
	GetFrustum(Normals,P);
	editorM->AddVertexs( nStartX, nStartY, nEndX, nEndY );
}

//Obté una línia d'allà on s'ha apretat en coordenades món
void Selection::GetLine( SPoint3D &L1, SPoint3D &L2, float mouseX, float mouseY )
{
	double mvmatrix[16];
	double projmatrix[16];
	int Viewport[4];
	double dX, dY, dZ, dClickY; // glUnProject uses doubles, but I'm using floats for these 3D vectors

	glGetIntegerv(GL_VIEWPORT, Viewport);	
	glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);
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

}

