#include "stdafx.h"
#include "EditorManager.h"
#include "MuscleManager.h"
#include "ExpressionManager.h"
#include "SPoint3D.h"
#include "Objecte3D.h"

EditorManager::EditorManager(MuscleManager* MMan, Objecte3D* objecte)
{
	MManager = MMan;
	CurrentVertex = 0;
	CurrentMuscle = NONE_MUSCLE;
	this->objecte = objecte;
	int nVertex = objecte->GetNumVertexs();
	VertexList = (bool*) malloc (nVertex*(sizeof(bool)));
	DeltaList = (float*) malloc (nVertex*(sizeof(float)));
	for ( int i = 0; i < nVertex; ++i ) {
		VertexList[i] = false;
		DeltaList[i] = 0.0;
	}
}

EditorManager::~EditorManager()
{
	free(MManager);
	delete [] VertexList;
}

//Afegeix un vèrtex al muscle definit
void EditorManager::AddVertex(SPoint3D vertex)
{
	int v = this->objecte->buscarPunt(vertex);
	this->VertexList[v] = true;
	++CurrentVertex;
}

//Calcula i assigna les deltes del muscle concret
void EditorManager::CalculateDelta(TypeMuscle muscle, SPoint3D vertexPrincipal)
{
	int numVertex;
	numVertex = objecte->GetNumVertexs();
	for (int i = 0; i < numVertex; i++) {
		if (this->VertexList[i]) {
			this->DeltaList[i] = (float) 1/(1 + objecte->RetornaPunt(i).calcularDistancia(vertexPrincipal));
		}
	}
}

//Elimina un vèrtex del muscle definit
void EditorManager::DeleteVertex(SPoint3D vertex)
{
	int v = objecte->buscarPunt(vertex);
	VertexList[v] = false;
	--CurrentVertex;
}

//Defineix el moviment del muscle per a una expressió
void EditorManager::DefineMovement(TypeExpression expression, TypeMuscle muscle)
{
}

void EditorManager::AddVertexFromTriangle(SPoint3D colisio, SPoint3D* triangle)
{
	puntFinal = triangle[0];
	float distanciaMinima, distanciaActual;
	distanciaMinima = colisio.calcularDistancia(puntFinal);
	for (int i = 1; i < 3; i++) {
		distanciaActual = colisio.calcularDistancia(triangle[i]);
		if (distanciaActual < distanciaMinima) {
			puntFinal = triangle[i];
			distanciaMinima = distanciaActual;
		}
	}
}

void EditorManager::SetMuscle(TypeMuscle muscle)
{
	int i = 0, maxVertex;
	maxVertex = objecte->GetNumVertexs();
	if ( CurrentMuscle != NONE_MUSCLE) {
		while (CurrentVertex) {
			if (VertexList[i]) {
				// Afegir el vertex al muscle
				MManager->addVertexMuscle(CurrentMuscle, (unsigned int) i, DeltaList[i]);
				// Eliminar el vertex ja guardat
				VertexList[i] = false;
				--CurrentVertex;
			}
			++i;
		}
	}
	// Canviar el muscle que s'està editant
	this->CurrentMuscle = muscle;
}
/*
void EditorManager::RenderVertexs()
{
}

void EditorManager::RenderSelection(float x1, float y1, float x2, float y2 )
{	
}
*/