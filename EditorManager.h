#ifndef EDITOR_H
#define EDITOR_H

#include "SPoint3D.h"
#include "MuscleManager.h"
#include "ExpressionManager.h"

class EditorManager
{
private:
	MuscleManager*	 MManager;

public:

	EditorManager(MuscleManager* MMan);
	~EditorManager();

	// Mètodes relacionats amb els muscles
	void		AddVertex		( TypeMuscle muscle, SPoint3D vertex, Objecte3D* objecte);
	void		DeleteVertex	( TypeMuscle muscle, SPoint3D vertex );
	void		CalculateDelta	( TypeMuscle muscle );

	// Mètodes relacionats amb les expressions
	void		DefineMovement	( TypeExpression expression, TypeMuscle muscle );

};

#endif