#ifndef UTIL_H
#define UTIL_H
#define PI  3.15159f

#pragma warning
typedef signed char INT8;

#include "PlatformSetup.h"

#define ELEMENTS_OF(array) (sizeof(array)/sizeof(array[0]))
#define minmax(min_, x, max_) (min(max(min_,x), max_))

class PT3D
{
public:
   double x,y,z;
public:
   PT3D()                                    {};
   PT3D(double xx, double yy, double zz)     {x=xx; y=yy; z=zz;};
};

class PT2D 
{
public:
   double x,y;
public:
   PT2D()                                    {};
   PT2D(double xx, double yy)                {x=xx; y=yy;};
   PT2D& operator =(const PT3D& pt)          {x=pt.x; y=pt.y; return *this;};
};

inline float toRads(float fDegrees) {
	return fDegrees*2*PI/360;
}

inline float toDegs(float fRadians) {
	return fRadians*360/(2*PI);
}

int lineTest(const PT2D& ptLineStart, const PT2D& ptLineEnd, const CPoint& pt);
bool poly4InsideTest(const PT2D* pt2Corners, const CPoint& pt);
bool poly4InsideTest(PT3D* pt3Corners, const CPoint& pt);   
INT8 getYsection(PT2D* ptCorners, const CPoint& pt);
INT8 getYsection(PT3D* pt3Corners, const CPoint& pt);
INT8 getXsection(PT2D* ptCorners, const CPoint& pt);
INT8 getXsection(PT3D* pt3Corners, const CPoint& pt);
#endif
