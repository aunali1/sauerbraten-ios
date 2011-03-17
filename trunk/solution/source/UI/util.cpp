#include <math.h>
#include "util.h"
#define ALMOST_ZERO 1e-6     // error tolerance
//Give a 4 sided polygon and an X-Y point, test to see if the point lies
//inside the polygon
//ptCorners is an array of 4 x,y corner points,
//pt is the point to test
bool poly4InsideTest(const PT2D* ptCorners, const CPoint& pt)
{
   int nResult1, nResult2;
   nResult1 = lineTest(ptCorners[0], ptCorners[1], pt);
   nResult2 = lineTest(ptCorners[2], ptCorners[3], pt);
   if (nResult1 > 0 && nResult2 > 0  || 
	   nResult1 < 0 && nResult2 < 0) {
      return FALSE;
   }
   nResult1 = lineTest(ptCorners[0], ptCorners[3], pt);
   nResult2 = lineTest(ptCorners[1], ptCorners[2], pt);
   if (nResult1 > 0 && nResult2 > 0  || 
	   nResult1 < 0 && nResult2 < 0) {
      return FALSE;
   }
   return TRUE;
}
//This function just reformats 3D data into 2D data and calls the 2D test,
//ignoring the Z coordinate.
bool poly4InsideTest(PT3D* pt3Corners, const CPoint& pt) {
   PT2D pt2Corners[4];
   for (int i=0; i<4; i++) 
      pt2Corners[i] = pt3Corners[i];
   return poly4InsideTest(pt2Corners, pt);
}
//Given a line and a point, returns:
//    1 if the point is above/right of the line
//   -1 if the point is below/left of the line
//    0 if the point is on the line
int lineTest(const PT2D& ptLineStart, const PT2D& ptLineEnd, const CPoint& pt) {
   double dx = ptLineEnd.x - ptLineStart.x;
   double dy = ptLineEnd.y - ptLineStart.y;
   if (fabs(dx)>fabs(dy)) {
      double yOnline = dy/dx * (pt.x - ptLineStart.x) + ptLineStart.y;
      return pt.y >  yOnline ? 1 : (pt.y < yOnline ? -1 : 0);
   } else {
      double xOnline = dx/dy * (pt.y - ptLineStart.y) + ptLineStart.x;
      return pt.x >  xOnline ? 1 : (pt.x < xOnline ? -1 : 0);
   }
}
/////////////////////////////////////////////////////////////////////////////
//HACK - MOVE MOST OF THIS STUFF INTO CUBE object!
/////////////////////////////////////////////////////////////////////////////

//This is similar to the poly4InsideTest, but in this case we already
//know the 2D point is inside the 4 sided polygon, and the mouse movement
//was "roughly parallel" to vector from corner 0 to corner 1.
//We want to know which Y stripe the point's in when we divide the 
//shape into 3 strips.   
//-1 is most negative section,
// 0 is middle section,
// 1 is most positive section
INT8 getYsection(PT2D* ptCorners, const CPoint& pt)
{
   int rc0, rc1, rc2;
   PT2D ptLineStart, ptLineEnd;
   double dx, dy;

   dx = (ptCorners[2].x - ptCorners[1].x)/3;
   dy = (ptCorners[2].y - ptCorners[1].y)/3;



   ptLineStart.x = ptCorners[0].x;
   ptLineStart.y = ptCorners[0].y;
   ptLineEnd.x   = ptCorners[1].x;
   ptLineEnd.y   = ptCorners[1].y;
   rc0 = lineTest(ptLineStart, ptLineEnd, pt);

   ptLineStart.x += dx;
   ptLineStart.y += dy;
   ptLineEnd.x   += dx;
   ptLineEnd.y   += dy;
   rc1 = lineTest(ptLineStart, ptLineEnd, pt);

   ptLineStart.x += dx;
   ptLineStart.y += dy;
   ptLineEnd.x   += dx;
   ptLineEnd.y   += dy;
   rc2 = lineTest(ptLineStart, ptLineEnd, pt);

   if (rc1 >= 0 && rc2 <= 0 
       || rc1 <= 0 && rc2 >= 0)
   {
      return 0;         //Center section
   }


   if (rc0 == 0)
      return -1;        //On the lower section line


   if (rc1 > 0 && rc0 > 0 
       || rc1 < 0 && rc0 < 0)
   {
      return 1;         //Upper section
   }

       
   return -1;           //Lower section
}


//This function just reformats 3D data into 2D data and calls the 2D test,
//ignoring the Z coordinate.
INT8 getYsection(PT3D* pt3Corners, const CPoint& pt)
{
   PT2D pt2Corners[4];

   for (int i=0; i<4; i++) 
      pt2Corners[i] = pt3Corners[i];

   return getYsection(pt2Corners, pt);
}




//This is similar to the poly4InsideTest, but in this case we already
//know the 2D point is inside the 4 sided polygon, and the mouse movement
//was "roughly parallel" to vector from corner 1 to corner 2.
//We want to know which X stripe the point's in when we divide the 
//shape into 3 strips.   
//-1 is most negative section,
// 0 is middle section,
// 1 is most positive section
INT8 getXsection(PT2D* ptCorners, const CPoint& pt)
{
   int rc0, rc1, rc2;
   PT2D ptLineStart, ptLineEnd;
   double dx, dy;

   dx = (ptCorners[1].x - ptCorners[0].x)/3;
   dy = (ptCorners[1].y - ptCorners[0].y)/3;


   //Now that we know point isn't in the center strip, 
   //test a line down the center
   ptLineStart.x = ptCorners[0].x;
   ptLineStart.y = ptCorners[0].y;
   ptLineEnd.x   = ptCorners[3].x;
   ptLineEnd.y   = ptCorners[3].y;
   rc0 = lineTest(ptLineStart, ptLineEnd, pt);
   
   ptLineStart.x += dx;
   ptLineStart.y += dy;
   ptLineEnd.x   += dx;
   ptLineEnd.y   += dy;
   rc1 = lineTest(ptLineStart, ptLineEnd, pt);

   ptLineStart.x += dx;
   ptLineStart.y += dy;
   ptLineEnd.x   += dx;
   ptLineEnd.y   += dy;
   rc2 = lineTest(ptLineStart, ptLineEnd, pt);

   if (rc1 >= 0 && rc2 <= 0 
       || rc1 <= 0 && rc2 >= 0)
   {
      return 0;         //Center section
   }


   if (rc0 == 0)
      return -1;        //On the lower section line


   if (rc1 > 0 && rc0 > 0 
       || rc1 < 0 && rc0 < 0)
   {
      return 1;         //Upper section
   }

       
   return -1;           //Lower section
}



//This function just reformats 3D data into 2D data and calls the 2D test,
//ignoring the Z coordinate.
INT8 getXsection(PT3D* pt3Corners, const CPoint& pt)
{
   PT2D pt2Corners[4];

   for (int i=0; i<4; i++) 
      pt2Corners[i] = pt3Corners[i];

   return getXsection(pt2Corners, pt);
}

