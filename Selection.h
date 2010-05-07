#ifndef SELECTION_H
#define SELECTION_H

#include "SPoint3D.h"
#include "Objecte3D.h"
#include "EditorManager.h"
#include "intersection.h"
#include "constants.h"

enum SelectionModes{ SELECT_ADD, SELECT_SUB };
enum TriFlags{ TF_SELECTED = 1, NTF_SELECTED = 2, TF_BACKFACING = (1<<1) };

class Selection
{
private:
	float nStartX, nStartY, nEndX, nEndY;
	bool buttonState;
	SPoint3D m_vLineP[2];
	Objecte3D* ObOBJ;
	EditorManager* editorM;

	int *m_pTriFlags;
	int m_nSelMode;

	int		FrustumSelect		( SPoint3D Normals[4], SPoint3D Points[8] );
	int		LineSelect			( const SPoint3D &LP1, const SPoint3D &LP2 );
	void	SetSelectionMode	( int nMode );
	void	SelectTriangle		( int nTri );
	void	SetFlagsTriangles	( void );
	

public:
	Selection(Objecte3D* obj, EditorManager* editor);
	~Selection();

	void	ButtonDown			( float mouseX, float mouseY );
	void	ButtonMove			( float mouseX, float mouseY );
	void	ButtonUp			( void );
	void	GetLine				( SPoint3D &L1, SPoint3D &L2, float mouseX, float mouseY );
	void	GetFrustum			( SPoint3D Normals[4], SPoint3D P[8] );
	void	Render				( void );
	void	NoRender			( void );
	void	SetObj				( Objecte3D* obj );
	bool	IsTriangleSelected	( int nTri );
	
	
	
};

#endif