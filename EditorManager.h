#ifndef EDITOR_H
#define EDITOR_H

#include "SPoint3D.h"
#include "MuscleManager.h"
#include "ExpressionManager.h"

class EditorManager
{
private:
	MuscleManager*	 MManager;
	unsigned int *VertexList, TotalVertex;
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
	void		AddVertexs	( float x1, float y1, float x2, float y2 );
	void		DeleteVertexs ( float x1, float y1, float x2, float y2 );

	void		RenderVertexs	( void );
	void		RenderSelection	( float x1, float y1, float x2, float y2 );
};

#endif