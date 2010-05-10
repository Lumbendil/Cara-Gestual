// Obj_3DS.h: interface for the Obj_3DS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCTREE_H__54F8D5DE_6B64_4C7F_970E_632FBE9510C6__INCLUDED_)
#define AFX_OCTREE_H__54F8D5DE_6B64_4C7F_970E_632FBE9510C6__INCLUDED_

#include "Load3DS.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Load3DS.h"

#define MAX_TEXTURES 200

struct nomfitxer {
	char nom[255];
	int num;
};

class Obj_3DS
{
public:
	CDocument *pDoc;
	bool fet3DS;

	void Inicialitzar();
	void EliminarMemoria();
	
	Obj_3DS();
	virtual ~Obj_3DS();

	bool Carregar3DS(char *nom);
	void Dibuixa3DS(bool actualitza, int obj);
	vector<struct nomfitxer> fitxerstextures;

// Array de textures dels materials
	GLuint g_Texture[MAX_TEXTURES];
	
	// Model carregat de 3DStudio
	t3DModel g_3DModel;

protected:

// Array de textures dels materials
//	GLuint g_Texture[MAX_TEXTURES];
	
// Model carregat de 3DStudio
//	t3DModel g_3DModel;
	
};

#endif // !defined(AFX_OCTREE_H__54F8D5DE_6B64_4C7F_970E_632FBE9510C6__INCLUDED_)
