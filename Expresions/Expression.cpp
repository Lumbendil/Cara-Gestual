#include "../stdafx.h"
#include "Expression.h"
#include "../Muscles/MuscleManager.h"
#include "../SPoint3D.h"

Expression::Expression(MuscleManager* MMan)
{
	MManager = MMan;
	movements = (SPoint3D*) malloc (MManager->getNumMuscles()*sizeof(SPoint3D));
	activeMuscles = new bool[MManager->getNumMuscles()];
	resetMuscles();
}

Expression::~Expression()
{
	delete[] movements;
	delete[] activeMuscles;
	MManager = NULL;
}

void Expression::modifyMuscle( TypeMuscle muscle, SPoint3D movement )
{
	movements[muscle] = movement;
	activeMuscles[muscle] = true;
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
		activeMuscles[i] = false;
	}
}

void Expression::RenderExpression( void )
{
	for (int i=0; i<MManager->getNumMuscles(); ++i)
	{
		if (activeMuscles[i])
			MManager->moveAMuscle((TypeMuscle)i, movements[i]);

		activeMuscles[i] = false;
	}
}