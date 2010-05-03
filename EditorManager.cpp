#include "stdafx.h"
#include "EditorManager.h"
#include "MuscleManager.h"
#include "ExpressionManager.h"
#include "SPoint3D.h"
#include "Objecte3D.h"

EditorManager::EditorManager(MuscleManager* MMan, int nVertex)
{
	MManager = MMan;
	VertexList = (unsigned int*) malloc (nVertex*sizeof(unsigned int));
	TotalVertex = 0;
}

EditorManager::~EditorManager()
{
	free(MManager);
	delete [] VertexList;
}

//Afegeix un vèrtex al muscle definit
void EditorManager::AddVertex(SPoint3D vertex, Objecte3D* objecte)
{
	//S'ha de buscar el punt mitjançant Objecte3D, i afegir el vèrtex al muscle.
}

//Calcula i assigna les deltes del muscle concret
void EditorManager::CalculateDelta(TypeMuscle muscle)
{
}

//Elimina un vèrtex del muscle definit
void EditorManager::DeleteVertex(SPoint3D vertex)
{
	//S'ha de buscar el punt mitjançant Objecte3D, i borrar el vèrtex del muscle.
}

//Defineix el moviment del muscle per a una expressió
void EditorManager::DefineMovement(TypeExpression expression, TypeMuscle muscle)
{
}

void EditorManager::AddVertexs	( float x1, float y1, float x2, float y2, int dimensioIgnorada )
{
}

void EditorManager::DeleteVertexs ( float x1, float y1, float x2, float y2, int dimensioIgnorada )
{
}

void EditorManager::RenderVertexs()
{
}

void EditorManager::RenderSelection(float x1, float y1, float x2, float y2)
{
	
}