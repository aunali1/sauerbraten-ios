#ifndef TRACKBALL_H
#define TRACKBALL_H
#include "PlatformSetup.h"
#include "vec3f.h"

class WTrackball 
{
protected:
   GLfloat m_mxRotation[16];     //Accumulated rotation matrix
   Vec3f m_vLastMouse;
   int m_ctRotations;            //# of rotations since last rotation matrix correction or reset


public:
   WTrackball();
   virtual ~WTrackball();

   void OnButtonDown(CPoint& point, CPoint& wndSize);
   bool OnMouseMove(CPoint& point, CPoint& wndSize);

   GLfloat* getRotMatrix(void)      {return m_mxRotation;};

   void reset(void);
   //void serialize(CArchive& ar, WORD wFileFormat);



protected:
   bool calcRotation(Vec3f vMouse);
   void correctRotationMatrix(void);

   Vec3f map(CPoint& point, CPoint& wndSize);
};

#endif //TRACKBALL_H