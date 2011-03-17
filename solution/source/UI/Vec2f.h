// 
// Vec2f.h
//
// This software is licensed/distributed under the GPL 
// WITHOUT ANY WARRANTY - see gpl.license.txt for details
// Written by Ross Wolin/Mystic Industries - Copyright 2003
//


#ifndef VEC2F_H
#define VEC2F_H


class Vec2f  
{
public:
   float x,y;

public:
	Vec2f();
	Vec2f(float xx, float yy);

   static float getAngle(Vec2f& v1, Vec2f& v2);

	static float dotProd(Vec2f& v1, Vec2f& v2);
	float getLength(void);
	void normalize(void);
};

#endif //VEC2F_H
