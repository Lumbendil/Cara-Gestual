#include "stdafx.h"
#include "EditorManager.h"
#include "MuscleManager.h"
#include "ExpressionManager.h"
#include "SPoint3D.h"
#include "Objecte3D.h"

EditorManager::EditorManager(MuscleManager* MMan)
{
	MManager = MMan;
}

EditorManager::~EditorManager()
{
	free(MManager);
}

//Afegeix un vèrtex al muscle definit
void EditorManager::AddVertex(TypeMuscle muscle, SPoint3D vertex)
{
	//S'ha de buscar el punt mitjançant Objecte3D, i afegir el vèrtex al muscle.
}

//Calcula i assigna les deltes del muscle concret
void EditorManager::CalculateDelta(TypeMuscle muscle)
{
}

//Elimina un vèrtex del muscle definit
void EditorManager::DeleteVertex(TypeMuscle muscle, SPoint3D vertex)
{
	//S'ha de buscar el punt mitjançant Objecte3D, i borrar el vèrtex del muscle.
}

//Defineix el moviment del muscle per a una expressió
void EditorManager::DefineMovement(TypeExpression expression, TypeMuscle muscle)
{
}