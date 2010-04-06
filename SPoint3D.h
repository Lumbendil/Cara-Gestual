#ifndef POINT_H
#define POINT_H

#ifndef Point_DEF
typedef struct _Point
{
	float x;
	float y;
	float z;
}Point;
#define Point_DEF
#endif

struct Point3D : public Point
{
public:
	Point3D	() {};
	Point3D (Point& );
	Point3D ( float * );
	Point3D	( float fx, float fy, float fz );

	//Casting
	operator float* ();
	operator const float* () const;

	//Assignment Operators
	Point3D& operator += ( const Point3D& );
	Point3D& operator -= ( const Point3D& );
	Point3D& operator *= ( float );
	Point3D& operator /= ( float );

	//Unary Operators
	Point3D operator + () const;
	Point3D operator - () const;

	//Binary Operators
	Point3D operator + ( const Point3D& ) const;
	Point3D operator - ( const Point3D& ) const;
	Point3D operator * ( float ) const;
	Point3D operator / ( float ) const;

	//Bool Operators
	bool operator == (const Point3D& ) const;
	bool operator != (const Point3D& ) const;
};
#endif