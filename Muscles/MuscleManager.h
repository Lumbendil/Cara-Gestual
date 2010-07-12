#ifndef MUSCLEMANAGER_H
#define MUSCLEMANAGER_H

#include "../SPoint3D.h"
#include "../lectorsModels/Objecte3D.h"
#include "Muscle.h"

#define NMUSCLES 12
//NONE �s l'�ltim element ja que l'array arriba a l'element N-1.
//NONE �s per definir un muscle quan no hi ha cap muscle seleccionada.
enum TypeMuscle {ECELLA, DCELLA, INFBOCA, EBOCA, DBOCA, EPARPELLA, DPARPELLA, EGALTA, DGALTA, SUPBOCA, LATEBOCA, LATDBOCA, NONE_MUSCLE};

class MuscleManager
{
private:

	Muscle**	muscles;
	Objecte3D* obj3D;

public:

	MuscleManager();
	~MuscleManager();

	void			addVertexMuscle		( TypeMuscle numMuscle, unsigned int vertex, float delta );
	void			moveAMuscle			( TypeMuscle numMuscle, SPoint3D vecDir );
	void			deleteMuscle		( TypeMuscle numMuscle );
	void			RenderMuscle		( TypeMuscle numMuscle );
	void			SetModel			( Objecte3D* ObOBJ );

	Muscle**		getMuscleList		( void );
	int				getNumMuscles		( void );
};

#endif