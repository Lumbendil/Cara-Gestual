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

struct SPoint3D : public Point
{
public:
	SPoint3D	() {};
	SPoint3D (Point& );
	SPoint3D ( float * );
	SPoint3D	( float fx, float fy, float fz );

	//Casting
	operator float* ();
	operator const float* () const;

	//Assignment Operators
	SPoint3D& operator += ( const SPoint3D& );
	SPoint3D& operator -= ( const SPoint3D& );
	SPoint3D& operator *= ( float );
	SPoint3D& operator /= ( float );

	//Unary Operators
	SPoint3D operator + () const;
	SPoint3D operator - () const;

	//Binary Operators
	SPoint3D operator + ( const SPoint3D& ) const;
	SPoint3D operator - ( const SPoint3D& ) const;
	SPoint3D operator * ( float ) const;
	SPoint3D operator / ( float ) const;

	//Bool Operators
	bool operator == (const SPoint3D& ) const;
	bool operator != (const SPoint3D& ) const;

	//Functions
	void		SPoint3D::normalizeVector	( void );
	double		SPoint3D::calcularDistancia	(const SPoint3D& ) const;
};

#endif