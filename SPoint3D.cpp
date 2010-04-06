#include "stdafx.h"
#include "SPoint3D.h"

Point3D::Point3D( Point& p )
{
	x = p.x;
	y = p.y;
	z = p.z;
}

Point3D::Point3D(float *p)
{
	x = p[0];
	y = p[1];
	z = p[2];
}

Point3D::Point3D(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

//Casting
Point3D::operator float* ()
{
	return (float *) &x;
}

Point3D::operator const float* () const
{
	return (const float *) &x;
}

//Assignment Operators
Point3D& Point3D::operator += (const Point3D& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Point3D& Point3D::operator -= (const Point3D& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Point3D& Point3D::operator *= (float v)
{
	x *= v;
	y *= v;
	z *= v;
	return *this;
}

Point3D& Point3D::operator /= (float v)
{
	x /= v;
	y /= v;
	z /= v;
	return *this;
}

//Unary Operators
Point3D Point3D::operator + () const
{
	return *this;
}

Point3D Point3D::operator - () const
{
	return Point3D(-x, -y, -z);
}

//Binary Operators
Point3D Point3D::operator +(const Point3D& v) const
{
	return Point3D(x + v.x, y + v.y, z + v.z);
}

Point3D Point3D::operator -(const Point3D& v) const
{
	return Point3D(x - v.x, y - v.y, z - v.z);
}

Point3D Point3D::operator *(float v) const
{
	return Point3D(x * v, y * v, z * v);
}

Point3D Point3D::operator /(float v) const
{
	float vInv = 1.0f / v;
	return Point3D(x * vInv , y * vInv, z * vInv);
}

//Bool Operators
bool Point3D::operator ==( const Point3D& v ) const
{
	return (x == v.x) && (y == v.y) && (z == v.z);
}

bool Point3D::operator !=( const Point3D& v ) const
{
	return (x != v.x) || (y != v.y) || (z != v.z);
}