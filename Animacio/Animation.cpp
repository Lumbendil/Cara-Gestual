#include "../stdafx.h"
#include "Animation.h"


Animation::Animation(ExpressionManager* manager, MuscleManager* muscle)
{
	step = 0;
	transitionTime = 4;
	totalTime = 0.5;
	divisionTime = 0.f;

	animationActive = false;

	expression = NONE_EXPRESSION;
	EManager = manager;
	MManager = muscle;
	
	sizeExpression = MManager->getNumMuscles();
	totalMovement = new SPoint3D [sizeExpression];
	partialMovement = new SPoint3D [sizeExpression];
	for (int i=0; i<sizeExpression; ++i)
	{
		totalMovement[i] = SPoint3D(0.0f, 0.0f, 0.0f);
		partialMovement[i] = SPoint3D(0.0f, 0.0f, 0.0f);
	}
}

Animation::~Animation()
{
	delete [] totalMovement;
	delete [] partialMovement;
}

void Animation::SetTime(int transitionTime, float totalTime)
{
	this->transitionTime = transitionTime;
	this->totalTime = totalTime;
}

void Animation::StartAnimation(TypeExpression expression)
{
	if (expression != NONE_EXPRESSION)
	{
		divisionTime = (totalTime / (float)transitionTime)*1000.f;

		this->expression = expression;
		for (int i=0; i < sizeExpression; ++i)
		{
			partialMovement[i] = EManager->getExpressionList()[expression]->getMovement( (TypeMuscle)i ) - totalMovement[i];
			totalMovement[i] = EManager->getExpressionList()[expression]->getMovement( (TypeMuscle)i );

			partialMovement[i]/divisionTime;
		}
	}
	
	animationActive = true;
	++step;
}

void Animation::NextStepAnimation()
{
	++step;
}

void Animation::FinalizeAnimation()
{
	animationActive = false;
	step = 0;
}

bool Animation::IsActiveAnimation( void )
{
	return animationActive;
}

void Animation::Render()
{
	if (divisionTime < (float) step)
		EManager->ExternalRender(expression,partialMovement);
}