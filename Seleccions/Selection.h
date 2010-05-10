#ifndef SELECTION_H
#define SELECTION_H

#include "../SPoint3D.h"
#include "../lectorsModels/Objecte3D.h"
#include "EditorManager.h"
#include "intersection.h"
#include "../constants.h"

enum SelectionModes{ SELECT_ADD, SELECT_SUB };
enum TriFlags{ TF_SELECTED = 1, NTF_SELECTED = 2, TF_BACKFACING = 3, NTF_BACKFACING = 4 };

class Selection
{
private:
	float nStartX, nStartY, nEndX, nEndY;
	bool buttonState, dominantSelect;
	SPoint3D m_vLineP[2];
	Objecte3D* ObOBJ;
	EditorManager* editorM;

	int *m_pTriFlags;
	int *m_pTriBackFacing;
	int m_nSelMode;

	/* Mètodes de selecció */
	int			FrustumSelect		( SPoint3D Normals[4], SPoint3D Points[8] );
	int			LineSelect			( const SPoint3D &LP1, const SPoint3D &LP2 );
	void		SelectTriangle		( int nTri );

	/* Mètodes de Set i Get */
	void		SetSelectionMode	( int nMode );
	void		GetFrustum			( SPoint3D Normals[4], SPoint3D P[8] );
	void		GetLine				( SPoint3D &L1, SPoint3D &L2, float mouseX, float mouseY );

public:
	Selection(Objecte3D* obj, EditorManager* editor);
	~Selection();

	/* Mètodes de pulsacions del ratolí */

	void	ButtonDown			( float mouseX, float mouseY, int flag );
	void	ButtonMove			( float mouseX, float mouseY );
	void	ButtonUp			( void );
	void	ButtonRDown			( float mouseX, float mouseY );

	/* Mètodes de Render */
	void	Render				( void );
	void	NoRender			( void );

	/* Mètodes de Set */
	void	SetObj				( Objecte3D* obj );
	void	SetZBufferTriangles	( SPoint3D camera );
	void	SetFlagsTriangles	( void );

	bool	IsTriangleSelected	( int nTri );
};

#endif