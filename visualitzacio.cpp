//******** PRACTICA GRAFICS PER COMPUTADOR 2
//******** Entorn b�sic VS2005 MONOFINESTRA amb interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Febrer 2010)
// visualitzacio.cpp : Funcions de visualitzaci� i pantalla
// FUNCIONS:	- Iluminaci� (Ilumina)
//				- Projecci� Ortogr�fica (ProjeccioOrto i Ortografica)
//				- Projecci� Perspectiva (ProjeccioPerspectiva,Perspectiva)
//				- Dibuixar els eixos (deixos)
//				- Dibuixar fons: blanc (FonsW) i negre (Fons)
//				- Carregar imatges textura (loadBMP)
//				- Carregar imatges de formats compatibles amb DevIL/OpenIL com a textura (loadIMA)
//				- Inicialitzar imatges textura per l'objecte Truck
//

#include "stdafx.h"
#include "visualitzacio.h"
#include "escena.h"
#include "constants.h"
#include "Seleccions/Selection.h"
#include "Muscles/MuscleManager.h"

// TEXTURES: Vector de noms de textura
GLuint textures[NUM_MAX_TEXTURES]={0,1,2,3,4,5,6,7,8,9};

GLdouble projectionMatrix[16];
GLint viewportMatrix[4];
GLdouble ModelViewMatrix[16];
TypeMuscle muscle = NONE_MUSCLE;
float wx1 = 0.0,wy1 = 0.0,wx2 = 0.0, wy2 = 0.0;

GLdouble* GetProjectionMatrix (void)
{
	return projectionMatrix;
}

GLdouble* GetModelviewMatrix (void)
{
	return ModelViewMatrix;
}

GLint* GetViewportMatrix (void)
{
	return viewportMatrix;
}

void SetRenderMuscle ( TypeMuscle numMuscle )
{
	muscle = numMuscle;
}

void RenderBox (float x1, float y1, float x2, float y2)
{
	wx1 = x1; wy1 = y1; wx2 = x2;wy2 = y2;
}

// Iluminaci�: Configurar iluminaci� de l'escena
void Iluminacio(char ilumin,bool textur,char obj,bool bc_lin)
{   
	
// Configuraci� de la font de llum LIGHT0
	GLfloat position[]={ 0.0,0.0,1.0,0.0};
	GLfloat especular[]={0.0,0.0,0.0,1.0};
    GLfloat ambientg[]={.5,.5,.5,1.0};
	glLightfv(GL_LIGHT0,GL_SPECULAR,especular);
    glLightfv(GL_LIGHT0,GL_POSITION,position);
     
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientg);

// Selecci� del model d'iluminaci� segons variable ilumin
	switch(ilumin)
	{
	case FILFERROS:
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glDisable(GL_COLOR_MATERIAL);

// Desactivaci� de l'ocultaci� de cares
		glDisable(GL_DEPTH_TEST);

// Desactivaci� de la il-luminaci�
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		break;

    case PLANA:
// C�lcul de les normals a les cares si l'objecte �s un fractal
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
// Dibuix de les cares back com a l�nies en Il.luminacio PLANA i SUAU
		if (bc_lin) glPolygonMode(GL_BACK,GL_LINE);
		
		glEnable(GL_COLOR_MATERIAL);

// Ocultaci� de cares
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_NORMALIZE);    
// Il.luminaci� per cares planes
		glShadeModel(GL_FLAT); 

// Activaci� de la llum
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		break;
	case SUAU:

// C�lcul de les normals als vertexs si l'objecte �s un fractal
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
// Dibuix de les cares back com a l�nies en Il.luminacio PLANA i SUAU
		if (bc_lin) glPolygonMode(GL_BACK,GL_LINE);
		
		glEnable(GL_COLOR_MATERIAL);

// Ocultaci� de cares
    	glEnable(GL_DEPTH_TEST);

		glEnable(GL_NORMALIZE); 
		
// Il.luminaci� suau 
        glShadeModel(GL_SMOOTH); 

// Activaci� de la llum
    	glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		break;
	
	}

// Configuraci� de les textures.
if (textur)
	{

// Activaci� de la textura 0.
	  glBindTexture(GL_TEXTURE_2D,textures[0]) ;

// Pregunta 8 enunciat
//	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);	
//	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	
	 
	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
  	  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

// Pregunta 9 enunciat
	  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE) ;
//	  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

// Pregunta 7 enunciat
//	  glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
//	  glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);

	  glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
	  glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);

// Generaci� coordenades textura.
	  GLfloat sPlane[4] = { -1.0f, 1.0f, 0.0f, 1.0f };
	  GLfloat tPlane[4] = { -1.0f, 0.0f, 1.0f, 1.0f };

	  glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
	  glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
				
	  glEnable(GL_TEXTURE_GEN_S);
	  glEnable(GL_TEXTURE_GEN_T);
	  glEnable(GL_TEXTURE_2D) ;
	}
	else { glDisable(GL_TEXTURE_2D);
	       glDisable(GL_TEXTURE_GEN_S);
	       glDisable(GL_TEXTURE_GEN_T);
		}

// Creaci� de la llista que dibuixar� els eixos
//   funci� on est� codi per dibuixar eixos
	glNewList(EIXOS,GL_COMPILE);
// Dibuix dels eixos sense il.luminaci�
//	if (ilumin!=FILFERROS) 
		glDisable(GL_LIGHTING);           	
// Dibuixar eixos sense textures
//	if (textura) 
		glDisable(GL_TEXTURE_2D);
	deixos();
	if (ilumin!=FILFERROS) glEnable(GL_LIGHTING);   
	if (textur) glEnable(GL_TEXTURE_2D);
	glEndList();

}

// PROJECCI� ORTOGR�FICA (Funcions Projeccio_Orto i Ortografica)

// Projeccio_Orto: Definici� Viewport i glOrtho
void Projeccio_Orto()
{   
//	----GC2: ESPECIFICACIO DELS PAR�METRES DE PROJECCI� ORTOGR�FICA
//			QUE ES CARREGUEN A LA MATRIU DE PROJECCI� GL_PROJECTION
}


// Ortografica: Crida a la funci� gluLookAt segons la variable prj 
//				(planta, al�at, perfil o axonometrica), 
//              Ilumina i dibuixa l'escena
void Ortografica(int prj,CColor col_fons,char objecte,bool TR, 
				 CPunt3D VScl,CPunt3D VTr,CPunt3D VRot,bool oculta,bool testv,
				 bool bck_ln,char iluminacio,bool textur,bool ifix,bool eix)
{
//	int i,j;

// Iluminacio movent-se amb la camara (abans gluLookAt)
	if (!ifix) Iluminacio(iluminacio,textur,objecte,bck_ln);

// ESPECIFICACIO DEL PUNT DE VISTA
// Cal definir el punt de vista (gluLookAt) en funci� del
//     tipus de projecci� definit a la variable prj.

// Neteja dels buffers de color i profunditat
	Fons(col_fons);

	glEnable(GL_COLOR_MATERIAL);

// Iluminacio fixe respecte la camara (despr�s gluLookAt)
	if (ifix) Iluminacio(iluminacio,textur,objecte,bck_ln);	

// Test de Visibilitat
	if (testv) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);

// Ocultacions (Z-buffer)
	if (oculta) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);

// Dibuix dels eixos
	if (eix) glCallList(EIXOS);

// Dibuixa l'objecte
    glPushMatrix();
// Transformacions geom�triques sobre objecte (Traslaci�, Rotacions i Escalatge)
	if (TR) 
		{	glTranslatef(VTr.x,VTr.y,VTr.z);
			glRotatef(VRot.x,1,0,0);
			glRotatef(VRot.y,0,1,0);
			glRotatef(VRot.z,0,0,1);
			glScalef(VScl.x,VScl.y,VScl.z);
		}

	switch (objecte)
	{

		case TRUCK:
// Dibuix del Truck
		glDisable(GL_TEXTURE_2D);
		sea();
		truck(textur,textures);
		break;

		case OBJ3DS:
// Objecte 3DS: Dibuix de l'objecte 3DS
			glCallList(OBJECTE3DS);
			break;

		case OBJOBJ:
// Objecte OBJ: Dibuix de l'objecte OBJ
			glCallList(OBJECTEOBJ);
			break;

		default:
// Dibuix de la resta d'objectes
		dibuixa(objecte);
		break;
	}

	glPopMatrix();

// Enviar les comandes gr�fiques a pantalla
    glFlush();

}

// PROJECCIO PERSPECTIVA
// Projeccio_Perspectiva: Definici� Viewport i gluPerspective
void Projeccio_Perspectiva(int minx,int miny,GLsizei w,GLsizei h,float zoom)
{   

	GLfloat rang=1.0;
// Desactivaci� del retall de pantalla
    glDisable(GL_SCISSOR_TEST);

// Definici� Viewport
	glViewport(minx,miny,w,h);
	if (h==0) h=1;

// Activaci� i inicialitzaci� matriu PROJECTION
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

// PROJECCIO PERSPECTIVA.Definim volum de visualitzaci� adaptant-lo 
//	 a les mides actuals de la finestra windows	

// Amb gluPerspective
	if (w>=h) 
	gluPerspective(60.0,1.0*w/h,p_near,p_far+zoom);
	else gluPerspective(60.0*h/w,1.0*w/h,p_near,p_far+zoom);

// Amb glFrustum (no actualitzar R)
//	if (w>=h) glFrustum(-rang*w/h,rang*w/h,-rang,rang,p_near,p_far+zoom);
//	else glFrustum(-rang,rang,-rang*h/w,rang*h/w,p_near,p_far+zoom);

// Activaci� matriu MODELVIEW (tancar matriu PROJECTION)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glGetIntegerv (GL_VIEWPORT, viewportMatrix);
	glGetDoublev (GL_PROJECTION_MATRIX, projectionMatrix);
}

// Perspectiva: Definici� gluLookAt amb possibilitat de moure 
//				el punt de vista interactivament amb el ratol�, 
//				ilumina i dibuixa l'escena
void Perspectiva(float anglex,float angley,float R,char VPol,bool pant,GLfloat tr[3],
				 CColor col_fons,char objecte,bool TR, 
				 CPunt3D VScl,CPunt3D VTr, CPunt3D VRot,bool oculta,bool testv,
				 bool bck_ln,char iluminacio,bool textur,bool ifix,bool eix,
				 EditorManager* EdManager, Objecte3D* ObOBJ, MuscleManager* MManager, bool flags, bool subtitles)
{    
	GLfloat cam[3],up[3];

// Conversi� angles radians -> graus
   	angley=angley*2*pi/360;
    anglex=anglex*2*pi/360;
//    R=300.0+zoom; 
	if(R<1.0) R=1.0;

// Neteja dels buffers de color i profunditat
	Fons(col_fons);

// Posici� c�mera i vector cap amunt
/*    cam[0]=R*cos(angley)*cos(anglex);
	cam[1]=R*sin(angley)*cos(anglex);
	cam[2]=R*sin(anglex);
    up[0]=-cos(angley)*sin(anglex);
	up[1]=-sin(angley)*sin(anglex);
	up[2]=cos(anglex);
*/

	if (VPol==POLARZ) { cam[0]=R*cos(angley)*cos(anglex);
						cam[1]=R*sin(angley)*cos(anglex);
						cam[2]=R*sin(anglex);
						up[0]=-cos(angley)*sin(anglex);
						up[1]=-sin(angley)*sin(anglex);
						up[2]=cos(anglex);	}
		else if (VPol==POLARY) {	cam[0]=R*sin(angley)*cos(anglex);
									cam[1]=R*sin(anglex);
									cam[2]=R*cos(angley)*cos(anglex);
									up[0]=-sin(angley)*sin(anglex);
									up[1]=cos(anglex);
									up[2]=-cos(angley)*sin(anglex);	}
			else {	cam[0]=R*sin(anglex);
					cam[1]=R*cos(angley)*cos(anglex);
					cam[2]=R*sin(angley)*cos(anglex);
					up[0]=cos(anglex);
					up[1]=-cos(angley)*sin(anglex);
					up[2]=-sin(angley)*sin(anglex);	}

// Iluminacio movent-se amb la camara (abans glLookAt)
	if (!ifix) Iluminacio(iluminacio,textur,objecte,bck_ln);

// Opci� pan: despla�ament del Centre de l'esfera (pant=1)
	if (pant) glTranslatef(tr[0],tr[1],tr[2]);

// Especificaci� del punt de vista
   gluLookAt(cam[0],cam[1],cam[2],0.,0.,0.,
		 up[0],up[1],up[2]);

// Iluminacio fixe respecte la camara (despr�s glLookAt)
	if (ifix) Iluminacio(iluminacio,textur,objecte,bck_ln);

// Test de Visibilitat
	if (testv) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);

// Ocultacions (Z-buffer)
	if (oculta) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);

//  Dibuix dels eixos
	if (eix) glCallList(EIXOS);

// Dibuixa l'objecte
    glPushMatrix();

// Transformacions geom�triques sobre objecte (Traslaci�, Rotacions i Escalatge)
	if (TR) 
		{	glTranslatef(VTr.x,VTr.y,VTr.z);
			glRotatef(VRot.x,1,0,0);
			glRotatef(VRot.y,0,1,0);
			glRotatef(VRot.z,0,0,1);
			glScalef(VScl.x,VScl.y,VScl.z);
		}

	switch (objecte)
	{

		case TRUCK:
// Dibuix del Truck
			glDisable(GL_TEXTURE_2D);
			sea();
			truck(textur,textures);
			break;

		case OBJ3DS:
		case OBJOBJ:
// Objecte OBJ: Dibuix de l'objecte OBJ
			//glCallList(OBJECTEOBJ);
			if (ObOBJ != NULL)
				ObOBJ->Render();

			break;

		default:
// Dibuix de la resta d'objectes
			dibuixa(objecte);
			break;
	}
	// RenderSelectedMuscle(muscle,MManager,ObOBJ);
	renderSphereSelection(EdManager, muscle);

	drawSelectionBox(wx1,wy1,wx2,wy2);

	// Dibuixar els subt�tols
	if (subtitles)
		DrawSubtitles();

	
	glPopMatrix();
	
	glGetDoublev (GL_MODELVIEW_MATRIX, ModelViewMatrix);
// Enviar les comandes gr�fiques a pantalla
	glFlush();
}


//PerspectivaN: Definici� gluLookAt directament per par�metre, sense esf�riques.
//              amb possibilitat de moure el punt de vista interactivament amb les
//				tecles de cursor per poder navegar.
void PerspectivaN(CPunt3D pv,bool pvb,GLfloat n[3],GLfloat v[3],
				 bool pant,GLfloat tr[3],CColor col_fons,char objecte,bool color,
				 bool TR,CPunt3D VScl,CPunt3D VTr,CPunt3D VRot,
				 bool oculta,bool testv,bool bck_ln,char iluminacio,
				 bool textur,bool ifix,bool eix)
{    
//    int i,j;
	double altfar=0;
//	GLfloat pvZ=0.0;

// Neteja dels buffers de color i profunditat
	Fons(col_fons);

// Test de Visibilitat
	if (testv) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);

// Ocultacions (Z-buffer)
	if (oculta) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);


// Iluminacio movent-se amb la camara (abans glLookAt)
	if (!ifix) Iluminacio(iluminacio,textur,objecte,bck_ln);

// Opci� pan: despla�ament del Centre de l'esfera (pant=true)
	if (pant) glTranslatef(tr[0],tr[1],tr[2]);

// Especificaci� del punt de vista
	gluLookAt(pv.x,pv.y,pv.z,n[0],n[1],n[2],v[0],v[1],v[2]);

// Iluminacio fixe respecte la camara (despr�s glLookAt)
	if (ifix) Iluminacio(iluminacio,textur,objecte,bck_ln);

// Dibuix dels eixos
	if (eix) glCallList(EIXOS);

// Dibuixa l'objecte
    glPushMatrix();
// Transformacions geom�triques sobre objecte (Traslaci�, Rotacions i Escalatge)
	if (TR) 
		{	glTranslatef(VTr.x,VTr.y,VTr.z);
			glRotatef(VRot.x,1,0,0);
			glRotatef(VRot.y,0,1,0);
			glRotatef(VRot.z,0,0,1);
			glScalef(VScl.x,VScl.y,VScl.z);
		}

	switch (objecte)
	{

// Dibuix del Truck
	case TRUCK:
		glDisable(GL_TEXTURE_2D);
		sea();
		truck(textur,textures);
		break;

		case OBJ3DS:
// Objecte 3DS: Dibuix de l'objecte 3DS
			glCallList(OBJECTE3DS);
			break;

		case OBJOBJ:
// Objecte OBJ: Dibuix de l'objecte OBJ
			glCallList(OBJECTEOBJ);
			break;

	default:
// Dibuix de la resta d'objectes
		dibuixa(objecte);
		break;
	}
	glPopMatrix();
	
// Enviar les comandes gr�fiques a pantalla
	glFlush();

}


// deixos: Dibuix dels eixos coordenats
void deixos()
{

// Eix X (vermell)
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	 glVertex3f(0.0,0.0,0.0);
	 glVertex3f(300.0,0.0,0.0);
	glEnd();

// Eix Y (verd)
    glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	 glVertex3f(0.0,0.0,0.0);
	 glVertex3f(0.0,300.0,0.0);
	glEnd();

// Eix Z (blau) 
	glColor3f(0.0,1.0,1.0);
	glBegin(GL_LINES);
	 glVertex3f(0.0,0.0,0.0);
	 glVertex3f(0.0,0.0,300.0);
	glEnd();

}

// Fons: Dibuixa el fons variable sefons el color int_fons
void Fons(CColor int_fons)
{
	glClearColor(int_fons.r,int_fons.g,int_fons.b,1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f,0.f,0.f,1.f);
	glClear(GL_DEPTH_BUFFER_BIT);
   glFlush();

}

// FonsN: Dibuixa el fons negre
void FonsN()
{
	glClearColor(0.f,0.f,0.f,1.f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glFlush();

}

// FonsB: Dibuixa el fons blanc
void FonsB()
{
	glClearColor(1.f,1.f,1.f,1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f,0.f,0.f,1.f);
	glClear(GL_DEPTH_BUFFER_BIT);
   glFlush();

}

// TEXTURES------------------------------------------------------
// loadBMP: This function receives as input the image filename and an 
// integer identifier (0 for the first texture) and creates an OpenGL 
// texture which is stored in the global array 'textures'
// Par�metres:
//		- filename: Fitxer que cont� la imatge BMP quadrada
//		- texID: Identificador dins la taula textures on volem
//                assignar la imatge BMP
bool loadBMP(CString filename, int texID)				
{
	FILE *file=NULL;	
	
// Create some space to store indermediate image data	
   AUX_RGBImageRec *localTexture[1];
   int errno;
	
// Open the image file for reading
// file=fopen(filename,"r");					// Funci� Visual Studio 6.0
   errno=fopen_s(&file,filename,"r");			// Funci� Visual 2005

// If the file is empty (or non existent) print an error and return false
// if (file == NULL)
   if (errno!=0)
 {
//  printf("Could not open file '%s'.\n",filename) ;

	 return false ;
 }

//    printf("Texture file:'%s' opened\n",filename) ;

// Load the image into the temporary storage
 localTexture[0] = auxDIBImageLoad(filename);

// Close the image file
 fclose(file);
	
// Generate space for one texture
 glGenTextures(1, &textures[texID]);

// Tell OpenGL that your texture is 2D (ie, has x and y values)
 glBindTexture(GL_TEXTURE_2D, textures[texID]);

// Create the texture
 glTexImage2D(GL_TEXTURE_2D, 0, 3, localTexture[0]->sizeX, localTexture[0]->sizeY,
		      0, GL_RGB, GL_UNSIGNED_BYTE, localTexture[0]->data);

// If the local storage area is not empry, empty it!
 if (localTexture[0])
 {
 	if (localTexture[0]->data)
 		free(localTexture[0]->data);
 	
 	free(localTexture[0]);					
 }

// If execution arrives here it means that all went well. Return true
 return true;

}


// TEXTURES------------------------------------------------------
// loadIMA: This function receives as input the image filename and an 
// integer identifier (0 for the first texture) and creates an OpenGL 
// texture which is stored in the global array 'textures'
// Par�metres:
//		- filename: Fitxer que cont� la imatge de qualsevol format:
//					BMP, JPG, TIFF, TGA, GIF, i d'altres suportats per OpenIL
//		- texID: Identificador dins la taula textures on volem
//                assignar la imatge
bool loadIMA(CString filename, int texID)				
{
	FILE *file=NULL;
	int errno;
	
// Open the image file for reading
// file=fopen(filename,"r");					// Funci� Visual Studio 6.0
   errno=fopen_s(&file,filename,"r");			// Funci� Visual 2005

// If the file is empty (or non existent) print an error and return false
// if (file == NULL)
   if (errno!=0)
 {
//	printf("Could not open file '%s'.\n",filename) ;

	 return false ;
 }

// Close the image file
 fclose(file);

// ilutGLLoadImage: Funci� que llegeix la imatge del fitxer filename
//				si �s compatible amb els formats DevIL/OpenIL (BMP,JPG,GIF,TIF,TGA,etc.)
//				i defineix la imatge com a textura OpenGL retornant l'identificador 
//				de textura OpenGL.
// GetBuffer: Funci� de converi� d'una variable CString -> char *
textures[texID] = ilutGLLoadImage(filename.GetBuffer(3));

// If execution arrives here it means that all went well. Return true
 return true;

}


// Inicialitzar imatges textures pel Truck
void Init_Textures()
{
	
//	loadBMP("vent.bmp",1);
	loadIMA("vent.bmp",1);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	
 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE) ;

//	loadBMP("plat.bmp",2);
	loadIMA("plat.bmp",2);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	
 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE) ;

//	loadBMP("reixeta.bmp",3);
	loadIMA("reixeta.bmp",3);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	
 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE) ;

//	loadBMP("fars.bmp",4);
	loadIMA("fars.bmp",4);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE) ;

//	loadBMP("txapa.bmp",5);
	loadIMA("txapa.bmp",5);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	
 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE) ;

//	loadBMP("metall.bmp",6); 
	loadIMA("metall.bmp",6); 

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);	
	 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE) ;
	

}

