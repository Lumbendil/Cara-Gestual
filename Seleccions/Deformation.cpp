#include "../stdafx.h"
#include "Deformation.h"
#include "../visualitzacio.h"
#include "../lectorsModels/Objecte3D.h"
#include "../Expresions/ExpressionManager.h"
#include "../Muscles/MuscleManager.h"
#include "../SPoint3D.h"


Deformation::Deformation( ExpressionManager* manager, Objecte3D* obj, EditorManager *editor )
{
	this->EManager = manager;
	this->ObOBJ = obj;
	this->muscle = NONE_MUSCLE;
	this->editorM = editor;
}

Deformation::~Deformation()
{
	this->EManager = NULL;
	this->ObOBJ = NULL;
	this->editorM = NULL;
}

void Deformation::ButtonDown(float mouseX, float mouseY, SPoint3D opv)
{
	SPoint3D LP1, LP2;

	if (ObOBJ != NULL)
	{
		GetLine(LP1, LP2, mouseX, mouseY);

		SPoint3D dominant = editorM->GetDominantVertex();
		normalPla = opv;
		normalPla.normalizeVector();

		SPoint3D HitP(0.0f, 0.0f,0.0f);
		bool coll = CheckLinePlane(normalPla, dominant, LP1, LP2, HitP);
		if (coll)
		{
			vecDir = HitP - dominant;
			editorM->DefineMovement(expression,muscle,vecDir);
			EManager->RenderExpression(expression);
			ObOBJ->Dibuixar(5);
		}
		
	}
}

void Deformation::ButtonMove(float mouseX, float mouseY)
{
	SPoint3D LP1, LP2;
	SPoint3D HitP(0.0f, 0.0f,0.0f);
	SPoint3D dominant = editorM->GetDominantVertex();

	GetLine(LP1, LP2, mouseX, mouseY);

	bool coll = CheckLinePlane(normalPla, dominant, LP1, LP2, HitP);
	if (coll)
	{
		vecDir = HitP - dominant;
		editorM->DefineMovement(expression,muscle,vecDir);
	}
	EManager->RenderExpression(expression);
	ObOBJ->Dibuixar(5);
}

void Deformation::ButtonUp()
{
	editorM->DefineMovement(expression, muscle, vecDir);
	EManager->RenderExpression(expression);
	ObOBJ->Dibuixar(5);
}

void Deformation::GetLine( SPoint3D &L1, SPoint3D &L2, float mouseX, float mouseY )
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
void Deformation::SetMuscle( TypeMuscle muscle )
{
	this->muscle = muscle;
}

void Deformation::SetExpression( TypeExpression expression )
{
	this->expression = expression;
}

void Deformation::SetObjecte( Objecte3D* Obj )
{
	this->ObOBJ = Obj;
}