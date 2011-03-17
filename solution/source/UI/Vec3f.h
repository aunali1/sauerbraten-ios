// Vec3f.h: interface for the Vec3f class.
//
//////////////////////////////////////////////////////////////////////

#ifndef VEC3F_H
#define VEC3F_H


#include <math.h>



class Vec3f  
{
public:
   float x,y,z;

public:
	Vec3f();
	Vec3f(float xx, float yy, float zz);
	virtual ~Vec3f();

	void crossProd( Vec3f &v1, Vec3f &v2 );
	static float dotProd(Vec3f &v1, Vec3f &v2 );
	float Length();
	void Normalize();
	void crossProd( Vec3f &v1, Vec3f& v2, Vec3f& v3 );
	friend Vec3f operator *( const Vec3f& v1, const float scale );
	friend Vec3f operator +( const Vec3f& v1, const Vec3f& v2 );
	friend Vec3f operator -( const Vec3f& v1, const Vec3f& v2 );
	friend Vec3f operator *( const float scale, const Vec3f& v1 );
	//Vec3f& Vec3f::operator *=(const float scale);
	//Vec3f& Vec3f::operator +=(const Vec3f& v1);
	//Vec3f& Vec3f::operator -=(const Vec3f& v1);

	operator float*()    {return (float*)&x;};
};

#endif //VEC3F_H
