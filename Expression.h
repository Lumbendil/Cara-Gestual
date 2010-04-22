#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "SPoint3D.h"
#include "MuscleManager.h"

class Expression
{
private:
	
	SPoint3D*			movements;
	MuscleManager*		MManager;

public:

	Expression();
	~Expression();

	void		resetMuscles		( void );
	void		modifyMuscle		( TypeMuscle muscle, SPoint3D movement );
	SPoint3D		getMovement			( TypeMuscle muscle );

	// Mou tots els muscles per a generar l'expressió
	void		RenderExpression	( void );

};

#endif
