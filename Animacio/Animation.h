#ifndef ANIMATION_H
#define ANIMATION_H

#include "../Expresions/ExpressionManager.h"
#include "../Muscles/MuscleManager.h"
#include "../SPoint3D.h"

class Animation
{
private:

	int sizeExpression;
	int transitionTime;
	float totalTime;
	float divisionTime;
	int step;
	bool animationActive;

	TypeExpression expression;

	SPoint3D* totalMovement;
	SPoint3D* partialMovement;

	ExpressionManager* EManager;
	MuscleManager* MManager;

public:

	Animation(ExpressionManager* manager, MuscleManager* muscle);
	~Animation();

	void		SetTime				( int transitionTime, float totalTime );
	bool		IsActiveAnimation	( void );

	void		StartAnimation		( TypeExpression expression );
	void		NextStepAnimation	( void );
	void		FinalizeAnimation	( void );

	void		Render				( void );
};

#endif