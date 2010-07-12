//******** PRACTICA GRAFICS PER COMPUTADOR 2
//******** Entorn b�sic VS2005 MONOFINESTRA amb interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, Debora Gil, Enric Mart� (Febrer 2010)
// escena.cpp : Aqui es on ha d'anar el codi de les funcions que 
//              dibuixin les escenes.

#include "stdafx.h"
#include "escena.h"
#include "PracticaView.h"
#include "visualitzacio.h"
#include "Seleccions/Selection.h"
#include "lectorsModels/Objecte3D.h"
#include "Muscles/MuscleManager.h"
#include "SPoint3D.h"

void renderSphereSelection (EditorManager* EdManager, TypeMuscle muscle)
{
	int tamany,dominant;
	SPoint3D *llista;
	if (EdManager != NULL && muscle != NONE_MUSCLE) {
		llista = EdManager->GetPointList(&tamany,&dominant);
		for (int i = 0; i < tamany; i++) {
			if (i == dominant) {
				glColor3f(1.0,0.0,0.0);
			} else {
				glColor3f(1.0,1.0,1.0);
			}
			glPushMatrix();
				glTranslatef(llista[i].x,llista[i].y,llista[i].z);
				glutSolidSphere(0.1,5,5);
			glPopMatrix();
		}
		delete [] llista;
	}
}

void DrawSubtitles ()
{
	char* frase = "HOLA MON!";
	bool blending = false;

	SetProjection2D();
	if(glIsEnabled(GL_BLEND)) blending = true;
    glEnable(GL_BLEND);
    glColor4f(1.f,0.f,0.f,1.f); 
	glRasterPos2f(100.f,100.f);
	while (*frase)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *frase); 
		++frase;
	}
	if(!blending) glDisable(GL_BLEND); 
	SetProjection3D();
}

// dibuixa: Funci� que dibuixa els objectes segons obj
void dibuixa(char obj)
{
	switch(obj)
	{

// Cub
	case CUB:
		glColor3f(1.0,1.0,1.0);
		glPushMatrix();
		  glScalef(5.0f,5.0f,5.0f);
		  glutSolidCube(1.0);
		glPopMatrix();
		break;

// Esfera
	case ESFERA:
		glColor3f(1.0,1.0,1.0);	
		glPushMatrix();
		  glScalef(5.0f,5.0f,5.0f);
		 glutSolidSphere(1.0,40,40);
		glPopMatrix();
		break;

// Tetera
	case TETERA:
		glColor3f(1.0,1.0,1.0);
		glPushMatrix();
		  glScalef(5.0f,5.0f,5.0f);
		  glutSolidTeapot(1.0);
		glPopMatrix();
		break;
	}

}

void drawSelectionBox (float x1, float y1, float x2, float y2)
{
	float m_nHeight = GetViewportMatrix()[3];
	y1 = m_nHeight-y1;
	y2 = m_nHeight-y2;

	SetProjection2D();

	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
		glLineStipple( 2, 43690 );
		glEnable( GL_LINE_STIPPLE);
		WireRect(x1,y1,x2,y2);
		glLineStipple( 1, 65535);
		glDisable( GL_LINE_STIPPLE);
	glPopMatrix();

	SetProjection3D();
}
void WireRect( float x1, float y1, float x2, float y2 )
{
    DrawLine( SPoint3D(x1,y1,0), SPoint3D(x2,y1,0) );
    DrawLine( SPoint3D(x2,y1,0), SPoint3D(x2,y2,0) );
    DrawLine( SPoint3D(x1,y2,0), SPoint3D(x2,y2,0) );
    DrawLine( SPoint3D(x1,y1,0), SPoint3D(x1,y2,0) );
}

void DrawLine( const SPoint3D &P1, const SPoint3D &P2 )
{
	glBegin( GL_LINES );
	glVertex3f( P1.x, P1.y, P1.z );
	glVertex3f( P2.x, P2.y, P2.z );
	glEnd();
}

void SetProjection3D()
{
	float m_nWidth = GetViewportMatrix()[2];
	float m_nHeight = GetViewportMatrix()[3];

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	gluPerspective( 60, (GLdouble)m_nWidth/(GLdouble)m_nHeight, 5.0f, 30000.0f );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();	
}

void SetProjection2D()
{
	float m_nWidth = GetViewportMatrix()[2];
	float m_nHeight = GetViewportMatrix()[3];

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	gluOrtho2D( 0.0, (GLdouble)m_nWidth, 0.0, (GLdouble)m_nHeight );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();	
}

// OBJECTE Truck amb imatges textura si s�n actives
// Truck: Par�metres:
//    - textu: Flag de textures activades o no.
//    - VTextu: Vector d'imatges textura.
void truck(bool textu,GLuint VTextu[NUM_MAX_TEXTURES])
{
// Crear qu�driques de dibuix
		GLUquadricObj *eix;
		GLUquadricObj *TubEscapeEsq;
		GLUquadricObj *TubEscapeDrt;
		GLUquadricObj *CisternaDarrera;
		GLUquadricObj *CisternaCentre;
		GLUquadricObj *CisternaDavant;
		GLUquadricObj *CisternaDarreraTapa;
		GLUquadricObj *CisternaDavantTapa;

		eix = gluNewQuadric();
		TubEscapeEsq = gluNewQuadric();
		TubEscapeDrt = gluNewQuadric();
		CisternaDarrera = gluNewQuadric();
		CisternaCentre = gluNewQuadric();
		CisternaDavant = gluNewQuadric();

		CisternaDarreraTapa = gluNewQuadric();
		CisternaDavantTapa = gluNewQuadric();

glPushMatrix();
  glTranslatef(0.0f,0.0f,20.0f);

// MOTOR
// Textura carrosseria
	if (textu)  
		{	GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		  	GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };
// Activar textura planxa
			glBindTexture(GL_TEXTURE_2D,VTextu[5]) ;
			glEnable(GL_TEXTURE_2D);
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);

		}

// Color carrosseria sense textura
	glColor4f(0.5f,0.7f,1.0f,0.5f); 

	glPushMatrix();		
		glScalef(2.0f, 4.4f, 2.0f);
		glutSolidCube(10.0f);
	glPopMatrix();

// CABINA
// Cabina inferior
	glPushMatrix();
		glTranslatef(0.0f,32.0f,0.0f);
		glScalef(4.0f, 2.0f, 2.0f);
		glutSolidCube(10.0f);
	glPopMatrix();

// Cabina superior
	glPushMatrix();
		glTranslatef(0.0f,32.0f,15.0f);
		glScalef(2.0f, 2.0f, 1.0f);
		glutSolidCube(10.0f);
	glPopMatrix();

// Cabina trasera
	glPushMatrix();
		glTranslatef(0.0f,49.5f,12.5f);
		glScalef(4.0f, 1.5f, 4.5f);
		glutSolidCube(10.0f);
	glPopMatrix();

// CANTONADES
// Cantonada esquerra
	glPushMatrix() ;
	  glTranslatef(10.0f,22.0f,-10.0f);

  	  glBegin(GL_QUADS);  // Cara de 4 costats
	 	glNormal3f(200.0f, 200.0f, 0.0f);
		glVertex3f(10.0f ,  0.0f , 0.0f ); //P1
		glVertex3f(10.0f , 0.0f , 20.0f ); //P2
		glVertex3f(0.0f , -10.0f ,20.0f ); //P3
		glVertex3f(0.0f ,  -10.0f ,0.0f ); //P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Triangle d'abaix
		glNormal3f(0.0f, 0.0f, -200.0f);
		glVertex3f(0.0f ,  0.0f , 0.0f );  // T1
		glVertex3f(10.0f ,  0.0f ,0.0f );  // P1
		glVertex3f(0.0f , -10.0f , 0.0f ); // P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Triangle de dalt
		glNormal3f(0.0f, 0.0f, 200.0f);
		glVertex3f(0.0f ,  0.0f , 20.0f );	// T2
	    glVertex3f(0.0f , -10.0f , 20.0f ); // P3
		glVertex3f(10.0f ,  0.0f, 20.0f );  // P2
	  glEnd();
	glPopMatrix();

// Cantonada dreta
	glPushMatrix() ;
	  glTranslatef(-10.0f,22.0f,-10.0f);
	  glRotatef(-90.0f,0.0f,0.0f,1.0f);

  	  glBegin(GL_QUADS);  // Cara de 4 costats
	 	glNormal3f(200.0f, 200.0f, 0.0f);
		glVertex3f(10.0f ,  0.0f , 0.0f ); //P1
		glVertex3f(10.0f , 0.0f , 20.0f ); //P2
		glVertex3f(0.0f , -10.0f ,20.0f ); //P3
		glVertex3f(0.0f ,  -10.0f ,0.0f ); //P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Triangle d'abaix
		glNormal3f(0.0f, 0.0f, -200.0f);
		glVertex3f(0.0f ,  0.0f , 0.0f );  // T1
		glVertex3f(10.0f ,  0.0f ,0.0f );  // P1
		glVertex3f(0.0f , -10.0f , 0.0f ); // P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Triangle de dalt
		glNormal3f(0.0f, 0.0f, 200.0f);
		glVertex3f(0.0f ,  0.0f , 20.0f );	// T2
	    glVertex3f(0.0f , -10.0f , 20.0f ); // P3
		glVertex3f(10.0f ,  0.0f, 20.0f );  // P2
	  glEnd();
	glPopMatrix();


// PROTECCIONS DE RODA
// Textura Proteccions de roda (metall)
//	if (textu)
//		{				
//			glBindTexture(GL_TEXTURE_2D,VTextu[5]) ;
//			glEnable(GL_TEXTURE_2D) ;
//			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
//			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
//			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
//			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
//			}

// Color proteccions roda sense textura
	glColor4f(0.5f,0.7f,1.0f,0.5f);

// Protecci� de roda esquerra
	glPushMatrix();		
		glTranslatef(10.0f, 0.0f, 3.0f);
		glBegin(GL_QUADS);
		//  glNormal3f(200.0f, 200.0f, 0.0f);
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(0.0f , 5.0f , 0.0f );
			glVertex3f(0.0f , -5.0f , 0.0f );

			glVertex3f(7.0f , -12.0f , -8.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(0.0f , -5.0f , 0.0f );
			glVertex3f(0.0f , -12.0f , -8.0f );

			glVertex3f(0.0f , 15.0f , -10.0f );
			glVertex3f(0.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , 15.0f , -10.0f );

			glVertex3f(7.5f , -5.0f , -3.0f );
			glVertex3f(7.5f , 5.0f , -3.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
				
			glVertex3f(7.5f , -12.0f , -8.0f );
			glVertex3f(7.5f , -5.0f , -3.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(7.0f , -12.0f , -8.0f );
				
			glVertex3f(7.0f , 15.0f , -10.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.5f , 5.0f , -3.0f );
			glVertex3f(7.5f , 15.0f , -10.0f );

		glEnd();
	glPopMatrix();

// Protecci� de roda dreta
	glPushMatrix();		
		glTranslatef(-16.0f, 0.0f, 3.0f);
		glBegin(GL_QUADS);
		//  glNormal3f(200.0f, 200.0f, 0.0f);
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(0.0f , 5.0f , 0.0f );
			glVertex3f(0.0f , -5.0f , 0.0f );

			glVertex3f(7.0f , -12.0f , -8.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(0.0f , -5.0f , 0.0f );
			glVertex3f(0.0f , -12.0f , -8.0f );

			glVertex3f(0.0f , 15.0f , -10.0f );
			glVertex3f(0.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , 15.0f , -10.0f );

			glVertex3f(7.5f , -5.0f , -3.0f );
			glVertex3f(7.5f , 5.0f , -3.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
				
			glVertex3f(7.5f , -12.0f , -8.0f );
			glVertex3f(7.5f , -5.0f , -3.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(7.0f , -12.0f , -8.0f );
				
			glVertex3f(7.0f , 15.0f , -10.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.5f , 5.0f , -3.0f );
			glVertex3f(7.5f , 15.0f , -10.0f );
		glEnd();
	glPopMatrix();

// Textura Reixeta Motor
	if (textu)  
		{	GLfloat sPlane[4] = { 0.05f, 0.25f, 0.00f, 0.00f };
		  	GLfloat tPlane[4] = { 0.00f, 0.25f, 0.05f, 0.00f };
// Activar textura
			glBindTexture(GL_TEXTURE_2D,VTextu[3]) ;
	
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
		}

// Color reixeta motor sense textura
	glColor4f(0.5f,0.7f,1.0f,0.5f);	

// Reixeta Motor
	glPushMatrix();
		glTranslatef(0.0f,-22.0f,0.0f);
		glBegin(GL_QUADS);
		    glNormal3f(0.0f,-1.0f,0.0f);	
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-10.0f , -2.0f , -10.0f );
			glTexCoord2f(1.0f,0.00f);
			glVertex3f(10.0f , -2.0f , -10.0f );
			glTexCoord2f(1.0f,1.0);
			glVertex3f(10.0f , -2.0f , 10.0f );
			 glTexCoord2f(0.0f,1.0f);	
			glVertex3f(-10.0f , -2.0f , 10.0f );
		glEnd();
	glPopMatrix();

// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

// Color eix sense textura
	glColor4f(0.1f,0.4f,1.0f,0.5f);

// Eix Davanter
	glPushMatrix();
	  glTranslatef(0.0f,0.0f,-10.0f);
	  glRotatef(90.0f,0.0f,1.0f,0.0f);
  	  glTranslatef(0.0f,0.0f,-13.0f);
	  gluCylinder(eix, 2,2,26.0f,6,1);
	glPopMatrix();
	
// Roda Dreta Davantera
	glPushMatrix();
		glTranslatef(-10.0f,0.0f,-10.0f);
		neumatic(textu,VTextu);
	glPopMatrix();

// Roda Esquerra Davantera
	glPushMatrix();
		glTranslatef(17.0f,0.0f,-10.0f);
		neumatic(textu,VTextu);
	glPopMatrix();

// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

// FARS	
// Color fars sense textura
	glColor4f(1.0f,0.0f,0.0f,0.5f);

// Far Esquerra	
	glPushMatrix();
		glTranslatef(-13.5f,-17.0f,-8.0f);
		glScalef(7.0f, 2.0f, 4.0f);
		glutSolidCube(1.0f);
	glPopMatrix();

// Far dret
	glPushMatrix();
		glTranslatef(13.5f,-17.0f,-8.0f);
		glScalef(7.0f, 2.0f, 4.0f);
		glRotatef(90.0f,1.0f,0.0f,0.0f); // Per a la textura
		glutSolidCube(1.0f);
	glPopMatrix();

// Textura frontal fars
	  if (textu)  
		{	GLfloat sPlane[4] = { 0.15f, 0.0f, 0.0f, 0.5f };
	  		GLfloat tPlane[4] = { 0.0f, 0.35f, 0.25f, 0.15f };
// Activar textura
			glBindTexture(GL_TEXTURE_2D,VTextu[4]) ;
	
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
				
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
			}

// Color frontal fars sense textura
	glColor4f(1.0f,1.0f,1.0f,0.5f);

// Frontal far dret
	glPushMatrix();
		glTranslatef(-13.5f,-16.5f,-8.0f);
		glBegin(GL_QUADS);
			glNormal3f(0.0f,-1.0f,0.0f);	
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-3.5f , -2.0f , -2.0f );
			glTexCoord2f(1.0f,0.00f);
			glVertex3f(3.5f , -2.0f , -2.0f );
			glTexCoord2f(1.0f,1.0);
			glVertex3f(3.5f , -2.0f , 2.0f );
			glTexCoord2f(0.0f,1.0f);	
			glVertex3f(-3.5f , -2.0f , 2.0f );
		glEnd();	
	glPopMatrix();

// Frontal far esquerre
	glPushMatrix();
		glTranslatef(13.5f,-16.5f,-8.0f);
		glBegin(GL_QUADS);
			glNormal3f(0.0f,-1.0f,0.0f);	
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-3.5f , -2.0f , -2.0f );
			glTexCoord2f(1.0f,0.00f);
			glVertex3f(3.5f , -2.0f , -2.0f );
		glTexCoord2f(1.0f,1.0);
			glVertex3f(3.5f , -2.0f , 2.0f );
			glTexCoord2f(0.0f,1.0f);	
			glVertex3f(-3.5f , -2.0f , 2.0f );
		glEnd();
	glPopMatrix();

// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

// VIDRE CABINA (SENSE TEXTURA)
// Activar transpar�ncia
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

// Color vidre cabina sense textura
	glColor4f(0.3f,0.8f,0.7f,0.5f);

// Vidre
	glPushMatrix() ;
	  glTranslatef(0.0f,22.0f,10.0f);
	  glRotatef(-90.0f,1.0f,0.0f,0.0f);
	  glRotatef(90.0f,0.0f,1.0f,0.0f);
	  glTranslatef(0.0f,00.0f,-10.0f);

   	  glBegin(GL_QUADS);  // Cara de 4 costats
	 	glNormal3f(200.0f, 200.0f, 0.0f);
		glVertex3f(10.0f ,  0.0f , 0.0f ); //P1
		glVertex3f(10.0f , 0.0f , 20.0f ); //P2
		glVertex3f(0.0f , -10.0f ,20.0f ); //P3
		glVertex3f(0.0f ,  -10.0f ,0.0f ); //P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Triangle d'abaix
		glNormal3f(0.0f, 0.0f, -200.0f);
		glVertex3f(0.0f ,  0.0f , 0.0f );  // T1
		glVertex3f(10.0f ,  0.0f ,0.0f );  // P1
		glVertex3f(0.0f , -10.0f , 0.0f ); // P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Triangle de dalt
		glNormal3f(0.0f, 0.0f, 200.0f);
		glVertex3f(0.0f ,  0.0f , 20.0f );	// T2
	    glVertex3f(0.0f , -10.0f , 20.0f ); // P3
		glVertex3f(10.0f ,  0.0f, 20.0f );  // P2
	  glEnd();
	glPopMatrix();

// Desactivar transpar�ncia
	glDisable(GL_BLEND);

// TUBS D'ESCAPAMENT (SENSE TEXTURA)
// Color tub d'escapament sense textura
	glColor4f(1.0f,0.0f,0.0f,0.5f);

// Tub d'escapament esquerre
	glPushMatrix();
		glTranslatef(18.0f,42.0f,10.0f);	
		gluCylinder(TubEscapeEsq, 2,2,40.0f,12,1);	
	glPopMatrix();
	
// Tub d'escapament dret
	glPushMatrix();
		glTranslatef(-18.0f,42.0f,10.0f);	
		gluCylinder(TubEscapeDrt, 2,2,40.0f,12,1);	
	glPopMatrix();

// CARROSSERIA
// Textura carrosseria
	if (textu)
		{	GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		  	GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };

// Activar textura
			glBindTexture(GL_TEXTURE_2D,VTextu[5]) ;
	
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
		}

// Color porta-eix motriu sense textura
	glColor4f(0.5f,0.7f,1.0f,0.5f);

// Porta-eix motriu mig
	glPushMatrix();
	  glTranslatef(0.0f,82.0f,-5.0f);
	  glScalef(1.0f, 5.0f, 1.0f);
	  glutSolidCube(10.0f);
	glPopMatrix();

	if (textu) glDisable(GL_TEXTURE_2D);

// Conjunt eixos i rodes eix mig
	glPushMatrix();
// Despla�ament Eix Mig
	  glTranslatef(0.0f,72.0f,0.0f);

// Color eix sense textura
	  glColor4f(0.1f,0.4f,1.0f,0.5f);

// Eix Mig Davanter
	  glPushMatrix();
	    glTranslatef(0.0f,0.0f,-10.0f);
	    glRotatef(90.0f,0.0f,1.0f,0.0f);
	    glTranslatef(0.0f,0.0f,-13.0f);
	    gluCylinder(eix, 2,2,26.0f,6,1);
	  glPopMatrix();
	
// Roda Dreta Davantera Eix Mig Davanter
	  glPushMatrix();
	    glTranslatef(-10.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Roda Esquerra Davantera Eix Mig Davanter
	  glPushMatrix();
	    glTranslatef(17.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

// Despla�ament entre dos eixos
	  glTranslatef(0.0f,25.0f,0.0f);

// Color eix sense textura
	  glColor4f(0.1f,0.4f,1.0f,0.5f);

// Eix Mig Darrera
	  glPushMatrix();
	    glTranslatef(0.0f,0.0f,-10.0f);
	    glRotatef(90.0f,0.0f,1.0f,0.0f);
	    glTranslatef(0.0f,0.0f,-13.0f);
	    gluCylinder(eix, 2,2,26.0f,6,1);
	  glPopMatrix();
	
// Roda Dreta Davantera Eix Mig Darrera
	  glPushMatrix();
	    glTranslatef(-10.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Roda Esquerra Davantera Eix Mig Darrera
	  glPushMatrix();
	    glTranslatef(17.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Fi conjunt d'eixos i rodes eix mig
    glPopMatrix();

// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);


		
// REMOLC	
// Textura carrosseria
	if (textu)
		{	GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		  	GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };

// Activar textura
			glBindTexture(GL_TEXTURE_2D,VTextu[5]);
	
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
		}


// Color plataforma sense textura
	glColor4f(0.5f,0.7f,1.0f,0.5f);

// Plataforma
	glPushMatrix();
		glTranslatef(0.0f,127.0f,4.0f);
		glScalef(3.0f, 14.0f, 0.8f);
		glutSolidCube(10.0f);
	glPopMatrix();

// Textura Cisterna
	if (textu)
		{	glBindTexture(GL_TEXTURE_2D,VTextu[6]);
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_2D);			
		}


// Color cisterna sense textura
	glColor4f(0.9f,0.9f,1.0f,0.5f);

// Cisterna
	glPushMatrix();
	  glTranslatef(0.0f,60.0f,20.0f);
	  glScalef(0.75f,1.0f,0.5f);
	  glRotatef(270.0f,1.0f,0.0f,0.0f);
// Part de davant
	  gluCylinder(CisternaDavant, 20,25,5.0f,25,1);	
	  glPushMatrix();
	  	glRotatef(180.0f,1.0f,0.0f,0.0f);
		gluDisk(CisternaDavantTapa, 0.0f, 20.0f, 25, 1);	
	  glPopMatrix();
// Part Central
	  glTranslatef(0.0f,0.0f,5.0f);
	  gluCylinder(CisternaCentre, 25,25,125.0f,25,1);
// Part Darrera
	  glPushMatrix();
		glTranslatef(0.0f,0.0f,125.0f);
		gluCylinder(CisternaDarrera, 25,20,5.0f,25,1);
		glTranslatef(0.0f,0.0f,5.0f);
		gluDisk(CisternaDarreraTapa, 0.0f, 20.0f, 25, 1);	
	  glPopMatrix();
	glPopMatrix();

// Desactivar textura
//	if (textu) glDisable(GL_TEXTURE_2D);

// Textura planxa
	if (textu)  
		{	
			GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		  	GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };
// Activar textura planxa
			glBindTexture(GL_TEXTURE_2D,VTextu[5]) ;
	
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
		}

// Color porta-eix motriu
	glColor4f(0.5f,0.7f,1.0f,0.5f);

// Porta-eix motriu darrera
	glPushMatrix();
	  glTranslatef(0.0f,172.0f,-5.0f);
	  glScalef(1.0f, 5.0f, 1.0f);
	  glutSolidCube(10.0f);
	glPopMatrix();

// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

// Conjunt eixos i rodes eix darrera
	glPushMatrix();

// Despla�ament Eix Darrera
	  glTranslatef(0.0f,162.0f,0.0f);

// Color eix sense textura
	  glColor4f(0.1f,0.4f,1.0f,0.5f);

// Eix Darrera Davanter
	  glPushMatrix();
	    glTranslatef(0.0f,0.0f,-10.0f);
	    glRotatef(90.0f,0.0f,1.0f,0.0f);
	    glTranslatef(0.0f,0.0f,-13.0f);
	    gluCylinder(eix, 2,2,26.0f,6,1);
	  glPopMatrix();
	
// Roda Dreta Davantera Eix Darrera Davanter
	  glPushMatrix();
	    glTranslatef(-10.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Roda Esquerra Davantera Eix Darrera Davanter
	  glPushMatrix();
	    glTranslatef(17.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

// Despla�ament entre dos eixos
	  glTranslatef(0.0f,25.0f,0.0f);

// Color eix sense textura
	  glColor4f(0.1f,0.4f,1.0f,0.5f);

// Eix Darrera Darrera
	  glPushMatrix();
		glTranslatef(0.0f,0.0f,-10.0f);
	 	glRotatef(90.0f,0.0f,1.0f,0.0f);
		glTranslatef(0.0f,0.0f,-13.0f);
		gluCylinder(eix, 2,2,26.0f,6,1);
	  glPopMatrix();
	
// Roda Dreta Davantera Eix Darrera Darrera
	  glPushMatrix();
	    glTranslatef(-10.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Roda Esquerra Davantera Eix Darrera Darrera
	  glPushMatrix();
	    glTranslatef(17.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();
// Fi conjunt eixos i rodes eix darrera
	glPopMatrix();

// Fi dibuix Truck
glPopMatrix();

// Restaurar textura[0]
if (textu)
	{	glBindTexture(GL_TEXTURE_2D,VTextu[0]);
//		glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
//		glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_2D);			
	}

// Alliberar mem�ria qu�driques
	gluDeleteQuadric(CisternaDavantTapa);
	gluDeleteQuadric(CisternaDarreraTapa);
	gluDeleteQuadric(CisternaDavant);
	gluDeleteQuadric(CisternaCentre);
	gluDeleteQuadric(CisternaDarrera);
	gluDeleteQuadric(TubEscapeDrt);
	gluDeleteQuadric(TubEscapeEsq);
	gluDeleteQuadric(eix);
}


// Dibuix de roda
// neumatic: Par�metres:
//    - textur: Flag de textures activades o no.
//    - VTextur: Vector d'imatges textura.
void neumatic(bool textur, GLuint VTextur[NUM_MAX_TEXTURES])
{

// Crear qu�drigues per la roda
	GLUquadricObj *roda;
	GLUquadricObj *tapareraroda;
	GLUquadricObj *taparoda;

	roda = gluNewQuadric();
	tapareraroda = gluNewQuadric();
	taparoda = gluNewQuadric();

// Textura neum�tic
	if (textur)  
		{	
// Activar textura neum�tic
			glBindTexture(GL_TEXTURE_2D,VTextur[1]) ;
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_2D);
		}

// Color neum�tic sense textura
	glColor4f(0.2f,0.2f,0.2f,0.5f);	

	glPushMatrix();
// Tapa inferior neum�tic
	  glRotatef(90.0f,0.0f,1.0f,0.0f);
	  gluDisk(tapareraroda, 5.0f, 10.0f, RESOLUCIO_RODA, 1);

// Dibuix de la llanta
	  llanta(textur,VTextur);

// Textura neum�tic
	  if (textur)  
		{	
// Activar textura neum�tic
			glBindTexture(GL_TEXTURE_2D,VTextur[1]) ;	
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_2D);
		}

// Color neum�tic sense textura
	glColor4f(0.2f,0.2f,0.2f,0.5f);	

// Gruix del neum�tic
	  glTranslatef(0.0f,0.0f,-6.0f);
	  gluCylinder(roda, 10,10,6.0f,RESOLUCIO_RODA,1);
// Tapa superior neum�tic
	  glRotatef(180.0f,0.0f,1.0f,0.0f);
	  gluDisk(taparoda, 5.0f, 10.0f, RESOLUCIO_RODA, 1);
// Dibuix de la llanta
	  llanta(textur,VTextur);
	glPopMatrix();

// Desactivar textures
//	if (textur) glDisable(GL_TEXTURE_2D);

// Alliberar mem�ria qu�driques
	gluDeleteQuadric(tapareraroda);
	gluDeleteQuadric(taparoda);
	gluDeleteQuadric(roda);
}

// Dibuix de la llanta de la roda
// llanta: Par�metres:
//    - textur: Flag de textures activades o no.
//    - VTextur: Vector d'imatges textura.
void llanta(bool textur, GLuint VTextur[NUM_MAX_TEXTURES])
{

// Crear qu�drica per la llanta
	GLUquadricObj *tapacub;
	tapacub = gluNewQuadric();

// Textura de la llanta
	if (textur)  
		{	GLfloat sPlane[4] = { 0.0f, -0.1f, 0.5f, 0.5f };
		  	GLfloat tPlane[4] = { 0.1f, 0.0f, 0.5f, 0.5f };
// Activar la textura
			glBindTexture(GL_TEXTURE_2D,VTextur[2]) ;
			glEnable(GL_TEXTURE_2D) ;
		
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR) ;
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR) ;
			glEnable(GL_TEXTURE_GEN_S) ;
			glEnable(GL_TEXTURE_GEN_T) ;
		}

// Dibuix de la llanta (disc de radi 5 de color clar)
	glColor4f(0.7f,0.7f,0.7f,0.5f);	
	gluDisk(tapacub, 0.0f, 5.0f, RESOLUCIO_RODA, 1);

// Alliberar qu�drica
	gluDeleteQuadric(tapacub);

}


// Mar amb ondulacions
void sea(void)
{
	int i,j,step,it1,it2;
//     GLfloat pi=3.14159;
	 float angle,delay;

		//aigua plana
	/*	glColor3f(0.5,0.4,0.9);
		glNormal3f(0.0,0.0,1.0);
		glBegin(GL_POLYGON);
		glVertex3f(-250,-250,0);
		glVertex3f(250,-250,0);
		glVertex3f(250,250,0);
		glVertex3f(-250,250,0);
		glEnd();*/

// Aigua amb ondulacions simulades a partir de normals sinusoidals
	step=5;
    delay=0;
    it1=0;
	 
//   SeleccionaMaterial(MAT_DEFAULT);	

	 float h=2*pi*step/500;
	  for(j=-250;j<250-step;j=j+step)
	  {
		   
		 delay=1.0*h*it1;
		
		 it2=0;
		   glColor3f(0.5f,0.4f,0.9f);
		  for(i=-250;i<250-step;i=i+step)
		  {
			   glBegin(GL_POLYGON);
               angle=1.0*it2*h*15;
			   glNormal3f(-cos(angle),0,1);
	           glVertex3f(i,j,0); 

			   angle=1.0*(it2+1)*h*15;
	           glNormal3f(-cos(angle),0,1);
		       glVertex3f(i+step,j,0);

			   angle=1.0*(it2+1)*h*15;
	           glNormal3f(-cos(angle),0,1);
			   glVertex3f(i+step,j+step,0);
			   glEnd();

			   glBegin(GL_POLYGON);
			   angle=1.0*it2*h*15;
			   glNormal3f(-cos(angle),0,1);
			   glVertex3f(i,j,0);

			   angle=1.0*(it2+1)*h*15;
	           glNormal3f(-cos(angle),0,1);
			   glVertex3f(i+step,j+step,0);
			
			   angle=1.0*it2*h*15;
		       glNormal3f(-cos(angle),0,1);
			   glVertex3f(i,j+step,0);
			   glEnd();
			it2++;
		  }
		  it1++;
       	  }

}
