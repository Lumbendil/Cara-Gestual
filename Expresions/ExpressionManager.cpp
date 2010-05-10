#include "stdafx.h"
#include "ExpressionManager.h"
#include "MuscleManager.h"
#include "Expression.h"
#include "SPoint3D.h"

ExpressionManager::ExpressionManager(MuscleManager* MMan)
{
	numExpressions = (sizeof(TypeExpression)/sizeof(int))-1;
	Expressions = (Expression**) malloc (numExpressions*sizeof(Expression));
	for (int i=0; i<numExpressions; ++i)
	{
		Expressions[i] = new Expression(MMan);
	}
}

ExpressionManager::~ExpressionManager()
{
	for (int i=0; i<numExpressions; ++i)
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
	return numExpressions;
}