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
	delete [] Expressions;
}

void ExpressionManager::resetExpression( TypeExpression nameExpression )
{
	if (nameExpression != NONE_EXPRESSION)
		Expressions[nameExpression]->resetMuscles();	
}

void ExpressionManager::modifyMuscleExpression(TypeExpression nameExpression, TypeMuscle nameMuscle, SPoint3D movement)
{
	if (nameExpression != NONE_EXPRESSION)
		Expressions[nameExpression]->modifyMuscle(nameMuscle, movement);
}

void ExpressionManager::RenderExpression( TypeExpression nameExpression )
{
	if (nameExpression != NONE_EXPRESSION)
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

void ExpressionManager::ExternalRender(TypeExpression nameExpression, SPoint3D *newMovements)
{
	if (nameExpression != NONE_EXPRESSION)
		Expressions[nameExpression]->ExternalRender(newMovements);
}