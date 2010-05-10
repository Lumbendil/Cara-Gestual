#include "../SPoint3D.h"

bool CheckLineBox( SPoint3D L1, SPoint3D L2, SPoint3D B1, SPoint3D B2, SPoint3D &HitP );
bool CheckLineTri( const SPoint3D &L1, const SPoint3D &L2, const SPoint3D &PV1, const SPoint3D &PV2, const SPoint3D &PV3, SPoint3D &HitP );
bool PointInFrustum( const SPoint3D &P, SPoint3D Normals[4], SPoint3D Points[8] );
bool TriInFrustum( SPoint3D vTri[3], SPoint3D Normals[4], SPoint3D Points[8] );
bool LineInFrustum( const SPoint3D &LP1, const SPoint3D &LP2, SPoint3D Normals[4], SPoint3D Points[8] );