#include "Vec3f.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Vec3f::Vec3f()
{
  x=0.0; y=0.0; z=0.0;
}

Vec3f::Vec3f(float xx, float yy, float zz)
: x(xx), y(yy), z(zz)
{
}

Vec3f::~Vec3f()
{
}
/*
Vec3f& Vec3f::operator*=(const float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

Vec3f& Vec3f::operator +=(const Vec3f &v1)
{
	x += v1.x;
	y += v1.y;
	z += v1.z;
	return *this;
}

Vec3f& Vec3f::operator -=(const Vec3f &v1)
{
	x -= v1.x;
	y -= v1.y;
	z -= v1.z;
	return *this;
}
*/
//
// Friends
//
Vec3f operator *(const Vec3f &v1, const float scale)
{
	return Vec3f( scale*v1.x, scale*v1.y, scale*v1.z );
}

Vec3f operator * (const float scale, const Vec3f &v1)
{
	return Vec3f( scale*v1.x, scale*v1.y, scale*v1.z );
}

Vec3f operator + (const Vec3f &v1, const Vec3f &v2)
{
	return Vec3f(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z );
}

Vec3f operator - (const Vec3f &v1, const Vec3f &v2)
{
	return Vec3f(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z );
}

//
// Take the cross product between two vectors and store it in the local
//    vector.
void Vec3f::crossProd(Vec3f &v1, Vec3f &v2)
{
	x = v1.y*v2.z - v1.z*v2.y;
	y = v1.z*v2.x - v1.x*v2.z;
	z = v1.x*v2.y - v1.y*v2.x;
	Normalize();
}


float Vec3f::dotProd(Vec3f& v1, Vec3f& v2)
{
   return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}



//
// This really isn't a cross-product, but it finds the plane normal 
//   from the triangle defined by the three input points.
//
void Vec3f::crossProd(Vec3f &v1, Vec3f &v2, Vec3f &v3)
{
	float x1, y1, z1, x2, y2, z2;
	x1 = v3.x-v2.x;
	y1 = v3.y-v2.y;
	z1 = v3.z-v2.z;

	x2 = v1.x-v2.x;
	y2 = v1.y-v2.y;
	z2 = v1.z-v2.z;

	x = y1*z2 - y2*z1;
	y = x2*z1 - x1*z2;
	z = x1*y2 - x2*y1;
	Normalize();
}


void Vec3f::Normalize()
{
	float length = Length();
	x /= length;
	y /= length;
	z /= length;

}

float Vec3f::Length()
{
	return sqrtf( x*x + y*y + z*z );
}


