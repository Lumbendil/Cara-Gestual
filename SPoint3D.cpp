#include "stdafx.h"
#include "SPoint3D.h"

SPoint3D::SPoint3D( Point& p )
{
	x = p.x;
	y = p.y;
	z = p.z;
}

SPoint3D::SPoint3D(float *p)
{
	x = p[0];
	y = p[1];
	z = p[2];
}

SPoint3D::SPoint3D(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

//Casting
SPoint3D::operator float* ()
{
	return (float *) &x;
}

SPoint3D::operator const float* () const
{
	return (const float *) &x;
}

//Assignment Operators
SPoint3D& SPoint3D::operator += (const SPoint3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

SPoint3D& SPoint3D::operator -= (const SPoint3D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

SPoint3D& SPoint3D::operator *= (float v)
{
	x *= v;
	y *= v;
	z *= v;
	return *this;
}

SPoint3D& SPoint3D::operator /= (float v)
{
	x /= v;
	y /= v;
	z /= v;
	return *this;
}

//Unary Operators
SPoint3D SPoint3D::operator + () const
{
	return *this;
}

SPoint3D SPoint3D::operator - () const
{
	return SPoint3D(-x, -y, -z);
}

//Binary Operators
SPoint3D SPoint3D::operator +(const SPoint3D& v) const
{
	return SPoint3D(x + v.x, y + v.y, z + v.z);
}

SPoint3D SPoint3D::operator -(const SPoint3D& v) const
{
	return SPoint3D(x - v.x, y - v.y, z - v.z);
}

SPoint3D SPoint3D::operator *(float v) const
{
	return SPoint3D(x * v, y * v, z * v);
}

SPoint3D SPoint3D::operator /(float v) const
{
	float vInv = 1.0f / v;
	return SPoint3D(x * vInv , y * vInv, z * vInv);
}

//Bool Operators
bool SPoint3D::operator ==( const SPoint3D& v ) const
{
	return (x == v.x) && (y == v.y) && (z == v.z);
}

bool SPoint3D::operator !=( const SPoint3D& v ) const
{
	return (x != v.x) || (y != v.y) || (z != v.z);
}
void SPoint3D::normalizeVector(void)
{
	float modul = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
	x/=modul;
	y/=modul;
	z/=modul;
}
double SPoint3D::calcularDistancia(const SPoint3D& v) const
{
	return sqrt(pow(x - v.x,2) + pow(y - v.y,2) + pow(z - v.z,2));
}
SPoint3D SPoint3D::CrossProduct(const SPoint3D& v)
{
	return SPoint3D(y *v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

float SPoint3D::Dot (const SPoint3D& v)
{
	return (x*v.x + y*v.y + z*v.z);
}