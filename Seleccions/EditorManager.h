#ifndef EDITOR_H
#define EDITOR_H

#include "../SPoint3D.h"
#include "../Muscles/MuscleManager.h"
#include "../Expresions/ExpressionManager.h"

class EditorManager
{
private:
	MuscleManager*	 MManager;
	bool *VertexList;
	float *DeltaList;
	int CurrentVertex;
	int DominantVertex;
	TypeMuscle CurrentMuscle;
	Objecte3D* objecte;


	SPoint3D	PuntMesProximTriangle	( SPoint3D colisio, SPoint3D* triangle );

public:

	EditorManager(MuscleManager* MMan, Objecte3D* objecte);
	~EditorManager();
	
	// Roger
	// Metodes relacionats amb els muscles
	void		AddVertex				( SPoint3D vertex );
	void		DeleteVertex			( SPoint3D vertex );
	void		CalculateDelta			( TypeMuscle m, SPoint3D vertexPrincipal );
	void		SetMuscle				( TypeMuscle m );
	void		AddVertexFromTriangle	( SPoint3D colisio, SPoint3D* triangle );
	void		DeleteVertexFromTriangle( SPoint3D colisio, SPoint3D* triangle );
	void		SetDominantVertex		( SPoint3D colisio, SPoint3D* triangle );

	// Metodes relacionats amb les expresions
	void		DefineMovement	( TypeExpression expression, TypeMuscle muscle );
	/*
	void		RenderVertexs	( void );
	void		RenderSelection	( float x1, float y1, float x2, float y2 );
	*/
};

#endif