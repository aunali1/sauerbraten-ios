#include <math.h>
#include "Vec2f.h"
#include "util.h"

#define ALMOST_ZERO   1e-6        //Error tolerance for comparisons, etc

Vec2f::Vec2f()
: x(0.0f), y(0.0f)
{
}

Vec2f::Vec2f(float xx, float yy)
: x(xx), y(yy)
{
}



float Vec2f::dotProd(Vec2f& v1, Vec2f& v2)
{
   return v1.x*v2.x + v1.y*v2.y;
}


//Get angle in degrees between unit vectors v1 and v2
float Vec2f::getAngle(Vec2f& v1, Vec2f& v2)
{
//   ASSERT(fabs(v1.getLength()-1) <= ALMOST_ZERO);      //Make sure these are unit vectors
//   ASSERT(fabs(v2.getLength()-1) <= ALMOST_ZERO);
   return toDegs((float)acos(dotProd(v1,v2)));
}

float Vec2f::getLength(void)
{
	return sqrtf(x*x + y*y);
}



void Vec2f::normalize(void)
{
	float L = getLength();
	x /= L;
	y /= L;
}





