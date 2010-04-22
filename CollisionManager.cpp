#include "stdafx.h"
#include "CollisionManager.h"
#include "SPoint3D.h"
#include "constants.h"
#include <coldet/coldet.h>
#include <math.h>


CCollisionManager::CCollisionManager()
{
	m_CollObj = newCollisionModel3D(true);
}

CCollisionManager::~CCollisionManager()
{
	m_CollObj = NULL;
	m_Obj = NULL;
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
	m_CollObj->finalize();
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
