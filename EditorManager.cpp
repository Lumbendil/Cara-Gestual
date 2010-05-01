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

//Afegeix un v�rtex al muscle definit
void EditorManager::AddVertex(TypeMuscle muscle, SPoint3D vertex)
{
	//S'ha de buscar el punt mitjan�ant Objecte3D, i afegir el v�rtex al muscle.
}

//Calcula i assigna les deltes del muscle concret
void EditorManager::CalculateDelta(TypeMuscle muscle)
{
}

//Elimina un v�rtex del muscle definit
void EditorManager::DeleteVertex(TypeMuscle muscle, SPoint3D vertex)
{
	//S'ha de buscar el punt mitjan�ant Objecte3D, i borrar el v�rtex del muscle.
}

//Defineix el moviment del muscle per a una expressi�
void EditorManager::DefineMovement(TypeExpression expression, TypeMuscle muscle)
{
}