#ifndef DEFORMATION_H
#define DEFORMATION_H

#include "../SPoint3D.h"
#include "../lectorsModels/Objecte3D.h"
#include "../Expresions/ExpressionManager.h"
#include "../Muscles/MuscleManager.h"
#include "EditorManager.h"

class Deformation
{
private:
	Objecte3D* ObOBJ;
	ExpressionManager* EManager;
	EditorManager* editorM;
	TypeMuscle muscle;
	TypeExpression expression;
	SPoint3D pla[4];
	SPoint3D vecDir;
	SPoint3D normalPla;

	void		GetLine				( SPoint3D &L1, SPoint3D &L2, float mouseX, float mouseY );

public:
	Deformation( ExpressionManager* manager, Objecte3D* obj, EditorManager *editor );
	~Deformation();

	void	ButtonDown			( float mouseX, float mouseY, SPoint3D opv );
	void	ButtonMove			( float mouseX, float mouseY );
	void	ButtonUp			( void );

	void	SetMuscle			( TypeMuscle muscle );
	void	SetExpression		( TypeExpression expression );
	void	SetObjecte			( Objecte3D* Obj );

	

};

#endif