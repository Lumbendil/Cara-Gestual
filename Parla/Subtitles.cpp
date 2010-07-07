#include "../stdafx.h"
#include "Subtitles.h"
#include "../escena.h"

CSubtitles::CSubtitles()
{
	red = 1.f;
	green = 1.f;
	blue = 1.f;
	alpha = 1.f;
	posX = 300.f;
	posY = 100.f;
	subtitle = "Com que no em puc menjar una mandarina, em compro un pressec.";
}

CSubtitles::~CSubtitles()
{
}

void CSubtitles::SetColor(float r, float g, float b, float a)
{
	red = (GLfloat) r;
	green = (GLfloat) g;
	blue = (GLfloat) b;
	alpha = (GLfloat) a;
}

void CSubtitles::SetPosition(float x, float y)
{
	posX = (GLfloat) x;
	posY = (GLfloat) y;
}

void CSubtitles::SetText (char* text)
{
	subtitle = text;
}

void CSubtitles::ParseSubtitles()
{
	//Controla el temps entre cada letra
	//Anar llegint cada lletra del subtítol
	//Cridar a l'animació (expressió) corresponent
}

void CSubtitles::RenderSubtitles()
{
	char* frase = subtitle;
	SetProjection2D();
	glColor4f(red,green,blue,alpha); 
	glPushMatrix();
		glRasterPos2f(posX,posY);
		while (*frase)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *frase); 
			++frase;
		}
	glPopMatrix();
	SetProjection3D();
}