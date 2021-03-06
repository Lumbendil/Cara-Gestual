#ifndef EDITOR_H
#define EDITOR_H

#include "../SPoint3D.h"
#include "../Muscles/MuscleManager.h"
#include "../Expresions/ExpressionManager.h"

class EditorManager
{
private:

	MuscleManager*		MManager;
	ExpressionManager*	EManager;
	bool				*VertexList;
	float				*DeltaList;
	int					CurrentVertex;
	int					DominantVertex;
	TypeMuscle			CurrentMuscle;
	Objecte3D*			objecte;

	void		CalculateDelta			( );
	SPoint3D	PuntMesProximTriangle	( SPoint3D colisio, SPoint3D* triangle );

public:

	EditorManager(MuscleManager* MMan, ExpressionManager* EMan, Objecte3D* objecte);
	~EditorManager();
	
	// Roger
	// Metodes relacionats amb els muscles
	void		AddVertex				( SPoint3D vertex );
	void		DeleteVertex			( SPoint3D vertex );
	void		SetMuscle				( TypeMuscle m );
	void		SaveMuscle				( void );
	void		AddVertexFromTriangle	( SPoint3D colisio, SPoint3D* triangle );
	void		DeleteVertexFromTriangle( SPoint3D colisio, SPoint3D* triangle );
	void		SetDominantVertex		( SPoint3D colisio, SPoint3D* triangle );
	SPoint3D*	GetPointList			( int* tamany, int* dominant );
	SPoint3D	GetDominantVertex		( void );

	// Metodes relacionats amb les expresions
	void		DefineMovement	( TypeExpression expression, TypeMuscle muscle, SPoint3D desplašament );
};

#endif
