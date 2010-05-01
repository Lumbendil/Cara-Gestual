#ifndef MUSCLEMANAGER_H
#define MUSCLEMANAGER_H

#include "SPoint3D.h"
#include "Objecte3D.h"
#include "Muscle.h"

//NONE és l'últim element ja que l'array arriba a l'element N-1.
//NONE és per definir un muscle quan no hi ha cap muscle seleccionada.
enum TypeMuscle {ECELLA, DCELLA, INFBOCA, EBOCA, DBOCA, EPARPELLA, DPARPELLA, EGALTA, DGALTA, NONE_MUSCLE};

class MuscleManager
{
private:

	Muscle**	muscles;
	Objecte3D* obj3D;
	int numMuscles;

public:

	MuscleManager();
	~MuscleManager();

	void			addVertexMuscle		( TypeMuscle numMuscle, unsigned int vertex, float delta );
	void			moveAMuscle			( TypeMuscle numMuscle, SPoint3D vecDir );
	void			deleteMuscle		( TypeMuscle numMuscle );

	Muscle**		getMuscleList		( void );
	int				getNumMuscles		( void );
};

#endif