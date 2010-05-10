#include "../stdafx.h"
#include "ExpressionManager.h"
#include "../Muscles/MuscleManager.h"
#include "Expression.h"
#include "../SPoint3D.h"

ExpressionManager::ExpressionManager(MuscleManager* MMan)
{
	Expressions = (Expression**) malloc (NEXPRESSIONS*sizeof(Expression));
	for (int i=0; i<NEXPRESSIONS; ++i)
	{
		Expressions[i] = new Expression(MMan);
	}
}

ExpressionManager::~ExpressionManager()
{
	for (int i=0; i<NEXPRESSIONS; ++i)
	{
		delete [] Expressions[i];
	}
	delete [] Expressions;
}

void ExpressionManager::resetExpression( TypeExpression nameExpression )
{
	Expressions[nameExpression]->resetMuscles();	
}

void ExpressionManager::modifyMuscleExpression(TypeExpression nameExpression, TypeMuscle nameMuscle, SPoint3D movement)
{
	Expressions[nameExpression]->modifyMuscle(nameMuscle, movement);
}

void ExpressionManager::RenderExpression( TypeExpression nameExpression )
{
	Expressions[nameExpression]->RenderExpression();
}

Expression** ExpressionManager::getExpressionList(void)
{
	return Expressions;
}

int ExpressionManager::getNumExpressions ()
{
	return NEXPRESSIONS;
}