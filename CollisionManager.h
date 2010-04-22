#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <coldet/coldet.h>
#include "SPoint3D.h"
#include "constants.h"

class CCollisionManager
{
public:

	//Crear Instància
	CCollisionManager*		getInstance		( void );

	//Netega la memòria
	void		CleanUp		( void );

	//Afegeix un triangle al model de ColDet
	void		addTriangle			( SPoint3D coord1, SPoint3D coord2, SPoint3D coord3 );

	//Finalitza el model un cop carregat amb el mètode addTriangle
	void		Finalize			( void );

	//Genera una col·lisió de raig contra el model
	// coordA - Inici del raig, coordB - Punt cap a on va el raig ("on s'ha clickat"), 
	//distance - distància del raig, CollisionPoint - Punt on s'ha col·lisionat
	bool		TestCollisionRay	( SPoint3D &coordA, SPoint3D &coordB, float distance, SPoint3D &CollisionPoint); 


private:

	CCollisionManager*		m_Obj;
	CollisionModel3D*		m_CollObj;

	CCollisionManager();
	~CCollisionManager();
	
};
#endif