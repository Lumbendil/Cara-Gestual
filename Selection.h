#ifndef SELECTION_H
#define SELECTION_H

#include "SPoint3D.h"
#include "Objecte3D.h"
#include "EditorManager.h"
#include "constants.h"

class Selection
{
private:
	float nStartX, nStartY, nEndX, nEndY;
	bool buttonState;
	SPoint3D m_vLineP[2];
	Objecte3D* ObOBJ;
	EditorManager* editorM;

public:
	Selection(Objecte3D* obj, EditorManager* editor);
	~Selection();

	void	ButtonDown		( float mouseX, float mouseY, CPunt3D opv );
	void	ButtonMove		( float mouseX, float mouseY, CPunt3D opv );
	void	ButtonUp		( void );
	void	GetLine			( SPoint3D &L1, SPoint3D &L2, float mouseX, float mouseY );
	void	GetFrustum		( SPoint3D Normals[4], SPoint3D P[8] );
	void	Render			( void );
	void	NoRender		( void );
};

#endif