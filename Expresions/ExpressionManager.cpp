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
<<<<<<< HEAD
	if (nameExpression != NONE_EXPRESSION)
		Expressions[nameExpression]->resetMuscles();	
=======
	if ( nameExpression != NONE_EXPRESSION ) {
		Expressions[nameExpression]->resetMuscles();
	}
>>>>>>> ed23bb751c341edf0a69ac4ada0d4d740629dd19
}

void ExpressionManager::modifyMuscleExpression(TypeExpression nameExpression, TypeMuscle nameMuscle, SPoint3D movement)
{
<<<<<<< HEAD
	if (nameExpression != NONE_EXPRESSION)
		Expressions[nameExpression]->modifyMuscle(nameMuscle, movement);
=======
	if ( nameExpression != NONE_EXPRESSION ) {
		Expressions[nameExpression]->modifyMuscle(nameMuscle, movement);
	}
>>>>>>> ed23bb751c341edf0a69ac4ada0d4d740629dd19
}

void ExpressionManager::RenderExpression( TypeExpression nameExpression )
{
<<<<<<< HEAD
	if (nameExpression != NONE_EXPRESSION)
		Expressions[nameExpression]->RenderExpression();
=======
	if ( nameExpression != NONE_EXPRESSION ) {
		Expressions[nameExpression]->RenderExpression();
	}
>>>>>>> ed23bb751c341edf0a69ac4ada0d4d740629dd19
}

Expression** ExpressionManager::getExpressionList(void)
{
	return Expressions;
}

int ExpressionManager::getNumExpressions ()
{
	return NEXPRESSIONS;
}