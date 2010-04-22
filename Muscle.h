#ifndef MUSCLE_H
#define MUSCLE_H

#include "SPoint3D.h"
#include "Objecte3D.h"

class Muscle
{
private:

	unsigned int*	vertexIndex;
	float*			vertexDelta;
	int				size;

	int				searchMuscle	(unsigned int vertex);

public:

	Muscle();
	~Muscle();

	int				addVertex		( unsigned int vertex, float delta );
	void			moveMuscle		( Objecte3D* obj3D, SPoint3D vecDir );
	int				alterDelta		( unsigned int vertex, float newDelta );
	int				deleteVertex	( unsigned int vertex );

	unsigned int*	getVertexIndex	( void );
	float*			getVertexDelta	( void );
	int				getNumVertexs	( void );
};

#endif