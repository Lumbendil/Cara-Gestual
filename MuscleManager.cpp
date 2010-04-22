#include "stdafx.h"
#include "Muscle.h"
#include "MuscleManager.h"
#include "SPoint3D.h"

MuscleManager::MuscleManager()
{
	numMuscles = (sizeof(TypeMuscle)/sizeof(int))-1;
	muscles = (Muscle**) malloc (numMuscles*sizeof(Muscle));
	for(int i=0; i<numMuscles; ++i)
	{
		muscles[i] = new Muscle();
	}
}
MuscleManager::~MuscleManager()
{
	for (int i=0; i<numMuscles; ++i)
	{
		delete [] muscles[i];
	}
	delete [] muscles;
}

void MuscleManager::addVertexMuscle(TypeMuscle numMuscle, unsigned int vertex, float delta)
{
	muscles[numMuscle]->addVertex(vertex, delta);
}

void MuscleManager::moveAMuscle( TypeMuscle numMuscle, SPoint3D vecDir )
{
	muscles[numMuscle]->moveMuscle(obj3D,vecDir);
}

void MuscleManager::deleteMuscle( TypeMuscle numMuscle )
{
	for (unsigned int i=0; i< (unsigned int)muscles[numMuscle]->getNumVertexs(); ++i)
	{
		muscles[numMuscle]->deleteVertex(i);
	}
}

Muscle** MuscleManager::getMuscleList(void)
{
	return muscles;
}

int MuscleManager::getNumMuscles ()
{
	return numMuscles;
}