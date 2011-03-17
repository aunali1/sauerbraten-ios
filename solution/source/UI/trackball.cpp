#include <math.h>
#include "trackball.h"

static const float ROT_SCALE = 135.0;
static const int CORRECTION_INTERVAL = 100;       //How many rotations before we normalize the rotation matrix?
WTrackball::WTrackball() 
: m_vLastMouse(0,0,0), m_ctRotations(0)
{
   reset();
}

WTrackball::~WTrackball()
{
}

void WTrackball::OnButtonDown(CPoint& ptMouse, CPoint& wndSize)
{
   m_vLastMouse = map(ptMouse, wndSize);
}



//Returns TRUE if rotation angle and vector changed
//Only call this when the mouse button of interest is down.
//We assume there will be a button down event before a mouse move
//with the buttion down.
bool WTrackball::OnMouseMove(CPoint& ptMouse, CPoint& wndSize)
{
   Vec3f vMouse;
   bool rc = FALSE;

   vMouse = map(ptMouse, wndSize);
   rc = calcRotation(vMouse);
   m_vLastMouse = vMouse;
   return rc;
}



//Load an indentity matrix into the rotation matrix. 
void WTrackball::reset(void)
{
   m_ctRotations = 0;

   m_mxRotation[0]=1.0f;      //Column 1
   m_mxRotation[1]=0.0f;
   m_mxRotation[2]=0.0f;
   m_mxRotation[3]=0.0f;

   m_mxRotation[4]=0.0f;      //Column 2
   m_mxRotation[5]=1.0f;
   m_mxRotation[6]=0.0f;
   m_mxRotation[7]=0.0f;

   m_mxRotation[8]=0.0;       //Column 3
   m_mxRotation[9]=0.0;
   m_mxRotation[10]=1.0;
   m_mxRotation[11]=0.0;

   m_mxRotation[12]=0.0;      //Column 4
   m_mxRotation[13]=0.0;
   m_mxRotation[14]=0.0;
   m_mxRotation[15]=1.0;
}



/////////////////////////////////////////////////////////////////////
//Local functions
/////////////////////////////////////////////////////////////////////


bool WTrackball::calcRotation(Vec3f vMouse)
{
	Vec3f vDirection;
   float fVelocity;
   
   float rotAngle;
   Vec3f rotAxis;


   vDirection = vMouse - m_vLastMouse;
   fVelocity = vDirection.Length();
   if (fVelocity <= 0.0001) 
      return FALSE;

	// Rotate about the axis that is perpendicular to the great circle connecting the mouse movements.
	rotAxis.crossProd(m_vLastMouse, vMouse);
	rotAngle = fVelocity * ROT_SCALE;

   //Assume that the MODELVIEW matrix is loaded
   // We need to apply the rotation as the last transformation.
	//   1. Get the current modelview matrix and save it.
	//   2. Set the matrix to the identity matrix (clear it).
	//   3. Apply the trackball rotation.
	//   4. Pre-multiply it by the saved matrix.
   glPushMatrix();
      glLoadIdentity();

      //Rotate the modelview matrix
      glRotatef(rotAngle, rotAxis.x, rotAxis.y, rotAxis.z);
      glMultMatrixf((GLfloat*)m_mxRotation);
      glGetFloatv(GL_MODELVIEW_MATRIX, m_mxRotation);  //Store this back into rotation matrix
   glPopMatrix();

   m_ctRotations++;
   if (m_ctRotations >= CORRECTION_INTERVAL) {
      correctRotationMatrix();
      m_ctRotations = 0;
   }

   return TRUE;
}



//Because of accumulated rounding error in the rotation matrix, every Nth rotation
//we should "correct the orthogonalness" of the rotation vectors by doing a 
//Gram-Schmidt matrix normalization.
void WTrackball::correctRotationMatrix(void)
{
   //OpenGL and C++ have a different opinion of which number is row and which is column...
   //In OpenGL, the indices are [column][row]
   //We want 3 vectors that are the rows of the rotation matrix.
   Vec3f v1(m_mxRotation[0], m_mxRotation[4], m_mxRotation[8]);
   Vec3f v2(m_mxRotation[1], m_mxRotation[5], m_mxRotation[9]);
   Vec3f v3;
   
   v1.Normalize();
   v2.Normalize();
   m_mxRotation[1] = v2.x;       //Put normalized row 2 back into matrix
   m_mxRotation[5] = v2.y;
   m_mxRotation[9] = v2.z;

   v3.crossProd(v1, v2);
   m_mxRotation[2]  = v3.x;      //Put new "orthogonalized" row 3 back into matrix
   m_mxRotation[6]  = v3.y;
   m_mxRotation[10] = v3.z;
   v1.crossProd(v2, v3);         //Put new "orthogonalized" row 1 back into matrix
   m_mxRotation[0] = v1.x;
   m_mxRotation[4] = v1.y;
   m_mxRotation[8] = v1.z;
}

//Map a point on a window to a 3D location on a sphere.
Vec3f WTrackball::map(CPoint& point, CPoint& wndSize)
{
	Vec3f v;
	float d;
	v.x = (2.0f*point.x - wndSize.x) / wndSize.x;
	v.y = (wndSize.y - 2.0f*point.y) / wndSize.y;
	v.z = 0.0;
	d = v.Length();
	d = (d < 1.0f) ? d : 1.0f;    // If d is > 1, then clamp it at one.
	v.z = sqrtf(1.0f+.001f - d*d);    // project the line segment up to the surface of the sphere.
	v.Normalize();  // We forced d to be less than one, not v, so need to normalize somewhere.
	return v;
}

//////////////////////////////////////////////////////////////////////////
// Serialization stuff
//////////////////////////////////////////////////////////////////////////

//void WTrackball::serialize(CArchive& ar, WORD wFileFormat)
//{
//   if (ar.IsStoring()) {
//      ar.Write(m_mxRotation, sizeof(m_mxRotation));
//      ar << m_ctRotations;
//   }
//   else {
//      ar.Read(m_mxRotation, sizeof(m_mxRotation));
//      ar >> m_ctRotations;
//   }
//}
