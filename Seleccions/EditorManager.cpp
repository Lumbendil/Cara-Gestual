#include "../stdafx.h"
#include "EditorManager.h"
#include "../Muscles/MuscleManager.h"
#include "../Expresions/ExpressionManager.h"
#include "../SPoint3D.h"
#include "../lectorsModels/Objecte3D.h"

EditorManager::EditorManager(MuscleManager* MMan, ExpressionManager* EMan, Objecte3D* objecte)
{
	MManager = MMan;
	EManager = EMan;
	CurrentVertex = 0;
	CurrentMuscle = NONE_MUSCLE;
	this->objecte = objecte;
	int nVertex = objecte->GetNumVertexs();
	VertexList = new bool[nVertex];
	DeltaList = new float[nVertex];
	for ( int i = 0; i < nVertex; ++i ) {
		VertexList[i] = false;
		DeltaList[i] = 0.0;
	}
}

EditorManager::~EditorManager()
{
	delete [] VertexList;
	delete [] DeltaList;
}

//Afegeix un v�rtex al muscle definit
void EditorManager::AddVertex(SPoint3D vertex)
{
	int v = this->objecte->buscarPunt(vertex);
	if(!this->VertexList[v]) {
		this->VertexList[v] = true;
		++CurrentVertex;
		if (CurrentVertex == 1)
			this->DominantVertex = v;
	}
}

SPoint3D* EditorManager::GetPointList(int* tamany, int* dominant)
{
	*tamany = this->CurrentVertex;
	int i = -1, nVertex;
	nVertex = *tamany;
	SPoint3D *llista = new SPoint3D[*tamany];
	while (nVertex) {
		if(this->VertexList[++i]) {
			if (i == this->DominantVertex) {
				*dominant = *tamany - nVertex;
			}
			llista[*tamany - nVertex] = objecte->GetPoint(i) + objecte->GetMovement(i);
			--nVertex;
		}
	}
	return llista;
}

//Calcula i assigna les deltes del muscle concret
void EditorManager::CalculateDelta()
{
	int numVertex;
	numVertex = objecte->GetNumVertexs();
	for (int i = 0; i < numVertex; i++) {
		if (this->VertexList[i]) {
			this->DeltaList[i] = (float) 1/(1 + objecte->GetPoint(i).calcularDistancia(objecte->GetPoint(DominantVertex)));
		}
	}
}

//Elimina un v�rtex del muscle definit
void EditorManager::DeleteVertex(SPoint3D vertex)
{
	int v = objecte->buscarPunt(vertex);
	if(this->VertexList[v]) {
		this->VertexList[v] = false;
		--CurrentVertex;
		if (v == DominantVertex)
			for (DominantVertex = 0; !VertexList[DominantVertex]; ++DominantVertex);
	}
}

//Defineix el moviment del muscle per a una expressi�
void EditorManager::DefineMovement(TypeExpression expression, TypeMuscle muscle, SPoint3D despla�ament)
{
	EManager->modifyMuscleExpression(expression,muscle,despla�ament);
}

void EditorManager::AddVertexFromTriangle(SPoint3D colisio, SPoint3D* triangle)
{
	SPoint3D puntFinal;
	puntFinal = this->PuntMesProximTriangle(colisio,triangle);
	this->AddVertex(puntFinal);
}

void EditorManager::DeleteVertexFromTriangle(SPoint3D colisio, SPoint3D* triangle)
{
	SPoint3D puntFinal;
	puntFinal = this->PuntMesProximTriangle(colisio,triangle);
	this->DeleteVertex(puntFinal);
}

void EditorManager::SetMuscle(TypeMuscle muscle)
{
	int i = 0,index, maxVertex;
	unsigned int *llistatVertex;
	float *llistatDelta;
	Muscle *m;

	maxVertex = objecte->GetNumVertexs();
	if ( CurrentMuscle != NONE_MUSCLE) {
		this->CalculateDelta();
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
	// Canviar el muscle que s'est� editant
	this->CurrentMuscle = muscle;
	// Carregar les dades del nou muscle
	m = MManager->getMuscleList()[muscle];
	llistatVertex = m->getVertexIndex();
	llistatDelta = m->getVertexDelta();
	CurrentVertex = m->getNumVertexs();
	float maxDelta = 0.0;
	for (i = 0; i < CurrentVertex; i++) {
		index = llistatVertex[i];
		this->VertexList[index] = true;
		this->DeltaList[index] = llistatDelta[i];
		if (this->DeltaList[index] > maxDelta) {
			this->DominantVertex = index;
			maxDelta = this->DeltaList[index];
		}
	}
}

void EditorManager::SaveMuscle()
{
	int i = 0, maxVertex;
	int CurrentTemp = CurrentVertex;

	maxVertex = objecte->GetNumVertexs();
	if ( CurrentMuscle != NONE_MUSCLE) {
		this->CalculateDelta();
		while (CurrentTemp) {
			if (VertexList[i]) {
				// Afegir el vertex al muscle
				MManager->addVertexMuscle(CurrentMuscle, (unsigned int) i, DeltaList[i]);
				--CurrentTemp;
			}
			++i;
		}
	}
}

SPoint3D EditorManager::PuntMesProximTriangle(SPoint3D colisio, SPoint3D* triangle)
{
	SPoint3D puntFinal = triangle[0];
	float distanciaMinima, distanciaActual;
	distanciaMinima = colisio.calcularDistancia(puntFinal);
	for (int i = 1; i < 3; i++) {
		distanciaActual = colisio.calcularDistancia(triangle[i]);
		if (distanciaActual < distanciaMinima) {
			puntFinal = triangle[i];
			distanciaMinima = distanciaActual;
		}
	}
	return puntFinal;
}
void EditorManager::SetDominantVertex( SPoint3D colisio, SPoint3D* triangle )
{
	SPoint3D puntFinal;

	puntFinal = this->PuntMesProximTriangle(colisio,triangle);
	this->AddVertex(puntFinal);
	DominantVertex = objecte->buscarPunt(puntFinal);
}
SPoint3D EditorManager::GetDominantVertex( void )
{
	return objecte->GetPoint(DominantVertex);
}
