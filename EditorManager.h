#ifndef EDITOR_H
#define EDITOR_H

#include "SPoint3D.h"
#include "MuscleManager.h"
#include "ExpressionManager.h"

class EditorManager
{
private:
	MuscleManager*	 MManager;
	unsigned int *VertexList, TotalVertex = 0;
	TypeMuscle Muscle;

public:

	EditorManager(MuscleManager* MMan, int nVertex);
	~EditorManager();
	
	// Roger
	// M�todes relacionats amb els muscles
	void		AddVertex	( SPoint3D vertex, Objecte3D* objecte);
	void		DeleteVertex	( SPoint3D vertex );
	void		CalculateDelta	( TypeMuscle m );
	void		SetMuscle	( TypeMuscle m );

	// M�todes relacionats amb les expressions
	void		DefineMovement	( TypeExpression expression, TypeMuscle muscle );

	// Kusku
	// dimensioIgnorada = 0 / dimensioIgnorada: x, etc.
	void		AddVertexs	( int x1, int y1, int x2, int y2, int dimensioIgnorada );
	void		DeleteVertexs ( int x1, int y1, int x2, int y2, int dimensioIgnorada );
};

#endif