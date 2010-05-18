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
	portionMovement = new SPoint3D[sizeExpression];
	backMovement = new SPoint3D[sizeExpression];

	for (int i=0; i<sizeExpression; ++i)
	{
		totalMovement[i] = SPoint3D(0.0f, 0.0f, 0.0f);
		partialMovement[i] = SPoint3D(0.0f, 0.0f, 0.0f);
		backMovement[i] = SPoint3D(0.0f, 0.0f, 0.0f);
	}
}

Animation::~Animation()
{
	delete [] totalMovement;
	delete [] partialMovement;
	delete [] portionMovement;
	delete [] backMovement;
}

void Animation::SetTime(int transitionTime, float totalTime)
{
	this->transitionTime = transitionTime;
	this->totalTime = totalTime;
}

void Animation::StartAnimation(TypeExpression expression)
{
	step = 0;
	if (expression != NONE_EXPRESSION)
	{
		divisionTime = totalTime / ((float)transitionTime*0.001f);

		this->expression = expression;
		for (int i=0; i < sizeExpression; ++i)
		{
			partialMovement[i] = EManager->getExpressionList()[expression]->getMovement( (TypeMuscle)i ) - totalMovement[i];
			totalMovement[i] = EManager->getExpressionList()[expression]->getMovement( (TypeMuscle)i );

			partialMovement[i]/=divisionTime;
			portionMovement[i] = partialMovement[i];
		}
		Render();
	}
	
	animationActive = true;
	++step;
}

void Animation::NextStepAnimation()
{
	++step;
	for (int i=0; i<sizeExpression; ++i)
	{
		partialMovement[i] += portionMovement[i];
	}
}

void Animation::FinalizeAnimation()
{
	for (int i=0; i<sizeExpression; ++i)
		backMovement[i] = totalMovement[i];

	animationActive = false;
	step = 0;
}

bool Animation::IsActiveAnimation( void )
{
	return animationActive;
}

void Animation::Render()
{
	SPoint3D* actualMovement = new SPoint3D [sizeExpression];

	for (int i=0; i<sizeExpression; ++i)
	{
		actualMovement[i] = backMovement[i] + partialMovement[i];
	}

	if (divisionTime > (float) step)
	{
		EManager->ExternalRender(expression,actualMovement);
	}
	
	delete []actualMovement;
}
