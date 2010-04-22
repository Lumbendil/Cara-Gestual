#include "stdafx.h"
#include "Expression.h"
#include "MuscleManager.h"
#include "SPoint3D.h"

Expression::Expression()
{
	MManager = new MuscleManager();
	movements = (SPoint3D*) malloc (MManager->getNumMuscles()*sizeof(SPoint3D));
}

Expression::~Expression()
{
	delete[] movements;
	MManager = NULL;
}

void Expression::modifyMuscle( TypeMuscle muscle, SPoint3D movement )
{
	movements[muscle] = movement;	
}

SPoint3D Expression::getMovement( TypeMuscle muscle )
{
	return movements[muscle];
}

void Expression::resetMuscles( void )
{
	for (int i=0; i<MManager->getNumMuscles(); ++i)
	{
		movements[i] = SPoint3D(0.f,0.f,0.f);
	}
}

void Expression::RenderExpression( void )
{
	for (int i=0; i<MManager->getNumMuscles(); ++i)
	{
		MManager->moveAMuscle((TypeMuscle)i, movements[i]);
	}
}