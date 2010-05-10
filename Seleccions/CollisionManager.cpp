#include "stdafx.h"
#include "CollisionManager.h"
#include "SPoint3D.h"
#include "constants.h"
#include <coldet/coldet.h>
#include <math.h>

CCollisionManager* CCollisionManager::m_Obj = 0;

CCollisionManager::CCollisionManager()
{
	m_CollObj = newCollisionModel3D(true);
	m_Obj = NULL;
}

CCollisionManager::~CCollisionManager()
{
	m_CollObj = NULL;
}

CCollisionManager*	CCollisionManager::getInstance(void)
{
	if (m_Obj == NULL)
	{
		m_Obj = new CCollisionManager();
	}
	return m_Obj;
}
void CCollisionManager::CleanUp(void)
{
	CCollisionManager::~CCollisionManager();
}

void CCollisionManager::addTriangle(SPoint3D coord1, SPoint3D coord2, SPoint3D coord3)
{
	m_CollObj->addTriangle( coord1.x, coord1.y, coord1.z,
							coord2.x, coord2.y, coord2.z,
							coord3.x, coord3.y, coord3.z);	
}

void CCollisionManager::Finalize()
{
	float *transform = new float[16];  
	for(int i=0;i<16; transform[i++]=0);  
    transform[0] = transform[5] = transform[10] = transform[15] = 1;
	m_CollObj->finalize();
	m_CollObj->setTransform(transform);
	delete(transform);
}

bool CCollisionManager::TestCollisionRay(SPoint3D &coordA, SPoint3D &coordB, float distance, SPoint3D &CollisionPoint)
{
	SPoint3D vecDir = coordB - coordA;
	vecDir.normalizeVector();

	if ( m_CollObj->rayCollision(coordA, vecDir, true, 0, distance) )
	{
		m_CollObj->getCollisionPoint(CollisionPoint, true);
		return true;
	}

	return false;
}
