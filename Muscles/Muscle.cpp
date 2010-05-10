#include "../stdafx.h"
#include "Muscle.h"
#include "../lectorsModels/Objecte3D.h"
#include "../SPoint3D.h"

Muscle::Muscle()
{
	size=0;
}
Muscle::~Muscle()
{
	delete [] vertexIndex;
	delete [] vertexDelta;
}

int Muscle::addVertex(unsigned int vertex, float delta)
{
	if ( searchMuscle(vertex) == -1) {
		size++;
		//Si el vector no existia el creem. Si ja existia, el fem més gran per tal de fer caber les noves dades
		if(size==1)
		{
			vertexIndex = (unsigned int *) malloc(sizeof(unsigned int));
			vertexDelta = (float *) malloc(sizeof(float));
		}
		else
		{
			vertexIndex = (unsigned int *) realloc (vertexIndex, size*sizeof(unsigned int));
			vertexDelta = (float *) realloc(vertexDelta, size*sizeof(float));
		}
		
		vertexIndex[size-1] = vertex;
		vertexDelta[size-1] = delta;
	}

	return size;
}

int Muscle::alterDelta(unsigned int vertex, float newDelta)
{
	int posicio;

	posicio=searchMuscle(vertex);
	
	if(posicio!=-1) 
	{
		vertexDelta[posicio]=newDelta;
	}

	return posicio;		
}
int Muscle::deleteVertex(unsigned int vertex)
{
	int posicio;

	posicio=searchMuscle(vertex);
	
	if(posicio!=-1)
	{
		//Fem un shift a l'esquerra dels elements a partir de la posició eliminada
		//Un cop fet el shift es fa un realloc del vector per fer-lo més petit (size-1)
		size--;
		for(posicio;posicio<(size);posicio++)
		{
			vertexIndex[posicio]=vertexIndex[posicio+1];
			vertexDelta[posicio]=vertexDelta[posicio+1];
		}

		vertexIndex = (unsigned int *) realloc (vertexIndex, size*sizeof(unsigned int));
		vertexDelta = (float *) realloc (vertexDelta, size*sizeof(float));

		return size;
	}
	else
	{
		return -1;
	}
}
void Muscle::moveMuscle(Objecte3D* obj3D, SPoint3D vecDir)
{
	unsigned short i;
	for(i=0; i<size; i++)
	{
		obj3D->mourePunt(vertexIndex[i], vecDir*vertexDelta[i]);
	}
}
float* Muscle::getVertexDelta(void)
{
	return vertexDelta;
}
unsigned int* Muscle::getVertexIndex(void)
{
	return vertexIndex;
}

int	Muscle::searchMuscle(unsigned int vertex)
{
	//Buscar on es troba el vertex
	for (int i = 0; i < size; i++) {
		if ( vertexIndex[i] == vertex ) {
			return i;
		}
	}
	return -1;
}

int Muscle::getNumVertexs()
{
	return size;
}

void Muscle::RenderMuscle( Objecte3D* obj3D )
{
	SPoint3D vertex;

	for (int i=0; i < size; ++i)
	{
		vertex = obj3D->RetornaPunt( (int)vertexIndex[i] );
		glColor3f(1.0,1.0,1.0);	
		glPushMatrix();
			glTranslatef(vertex.x, vertex.y, vertex.z);
			glutSolidSphere(0.1,5,5);
		glPopMatrix();
	}
}