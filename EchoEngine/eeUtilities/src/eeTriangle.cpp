#include "eeTriangle.h"
#include "eePlane.h"
#include "eeVector3.h"

namespace eeEngineSDK {
Vector<Vector<Triangle>>
Triangle::getSplitTrianglesByPlane(const Triangle& splitTriangle,
                                   const Plane& splitterPlane)
{
  Vector<ComplexVertex> sideAVertices;
  Vector<ComplexVertex> sideBVertices;

  // Obtain plain info
  Vector3f plainPoint;
  if (splitterPlane.x != 0) {
    plainPoint = Vector3f(splitterPlane.d / splitterPlane.x, 0.0f, 0.0f);
  }
  else if (splitterPlane.y != 0) {
    plainPoint = Vector3f(0.0f, splitterPlane.d / splitterPlane.y, 0.0f);
  }
  else if (splitterPlane.z != 0) {
    plainPoint = Vector3f(0.0f, 0.0f, splitterPlane.d / splitterPlane.z);
  }
  else {
    return { {splitTriangle}, {} };
  }
  Vector3f plainNormal = splitterPlane.getNormal();
  float newW = splitterPlane.d / plainNormal.getMagnitude();
  plainNormal.normalize();

  // Separate points depending on which side of the plain they are.
  int8 aSide = -1;
  Vector3f pX = Vector3f(splitTriangle.x.position.x, splitTriangle.x.position.y, splitTriangle.x.position.z);
  Vector3f pY = Vector3f(splitTriangle.y.position.x, splitTriangle.y.position.y, splitTriangle.y.position.z);
  Vector3f pZ = Vector3f(splitTriangle.z.position.x, splitTriangle.z.position.y, splitTriangle.z.position.z);
  if (plainNormal.dot(pX - plainPoint) <= 0.0f) {
    sideAVertices.emplace_back(splitTriangle.x);
    aSide = 1;
  }
  else {
    sideBVertices.emplace_back(splitTriangle.x);
    aSide = 2;
  }
  if (plainNormal.dot(pY - plainPoint) <= 0.0f) {
    sideAVertices.emplace_back(splitTriangle.y);
  }
  else {
    sideBVertices.emplace_back(splitTriangle.y);
  }
  if (plainNormal.dot(pZ - plainPoint) <= 0.0f) {
    if (aSide == 1) {
      sideAVertices[0] = splitTriangle.z;
      sideAVertices.emplace_back(splitTriangle.x);
    }
    else {
      sideAVertices.emplace_back(splitTriangle.z);
    }
  }
  else {
    if (aSide == 2) {
      sideBVertices[0] = splitTriangle.z;
      sideBVertices.emplace_back(splitTriangle.x);
    }
    else {
      sideBVertices.emplace_back(splitTriangle.z);
    } 
  }

  // If a side is empty, return the triangle on the side is on.
  if (sideAVertices.empty()) {
    return { {}, {splitTriangle} };
  }
  if (sideAVertices.size() == 3) {
    return { {splitTriangle}, {} };
  }

  // Get points positions for the formula
  Vector3f pA;
  ComplexVertex vA;
  Vector3f pB;
  ComplexVertex vB;
  Vector3f pC;
  ComplexVertex vC;
  if (sideAVertices.size() == 1) {
    vA = sideAVertices[0];
    pA = Vector3f(vA.position.x, vA.position.y, vA.position.z);

    vB = sideBVertices[0];
    pB = Vector3f(vB.position.x, vB.position.y, vB.position.z);
    vC = sideBVertices[1];
    pC = Vector3f(vC.position.x, vC.position.y, vC.position.z);
  }
  else {
    vA = sideBVertices[0];
    pA = Vector3f(vA.position.x, vA.position.y, vA.position.z);

    vB = sideAVertices[0];
    pB = Vector3f(vB.position.x, vB.position.y, vB.position.z);
    vC = sideAVertices[1];
    pC = Vector3f(vC.position.x, vC.position.y, vC.position.z);
  }

  // Gets the values needed for the las part
  Vector3f dAB = pB - pA;
  float dABm = dAB.getMagnitude();
  dAB.normalize();
  Vector3f dAC = pC - pA;
  float dACm = dAC.getMagnitude();
  dAC.normalize();

  float dtAB = (newW - plainNormal.dot(pA)) / plainNormal.dot(dAB);
  float dtAC = (newW - plainNormal.dot(pA)) / plainNormal.dot(dAC);

  // Place the two new points that touch the plane 
  Vector3f pD = pA + dAB * dtAB;
  Vector3f pE = pA + dAC * dtAC;

  // And gets its ratio on the line between its original points
  float ratioAD = dtAB / dABm;
  float ratioAE = dtAC / dACm;

  // Adds the new points to both sides of the plane.
  Vector4f pD4 = Vector4f(pD.x, pD.y, pD.z, 1.0f);
  Vector4f UVD = vA.uvCoord - (vA.uvCoord - vB.uvCoord) * ratioAD;
  Vector4f normD = vA.normal - (vA.normal - vB.normal) * ratioAD;
  Vector4f binormD = vA.binormal - (vA.binormal - vB.binormal) * ratioAD;
  Vector4f tanD = vA.tangent - (vA.tangent - vB.tangent) * ratioAD;
  sideAVertices.emplace_back(ComplexVertex{pD4, UVD, normD, binormD, tanD});
  sideBVertices.emplace_back(ComplexVertex{pD4, UVD, normD, binormD, tanD});

  Vector4f pE4 = Vector4f(pE.x, pE.y, pE.z, 1.0f);
  Vector4f UVE = vA.uvCoord - (vA.uvCoord - vC.uvCoord) * ratioAE;
  Vector4f normE = vA.normal - (vA.normal - vC.normal) * ratioAE;
  Vector4f binormE = vA.binormal - (vA.binormal - vC.binormal) * ratioAE;
  Vector4f tanE = vA.tangent - (vA.tangent - vC.tangent) * ratioAE;
  sideAVertices.emplace_back(ComplexVertex{ pE4, UVE, normE, binormE, tanE });
  sideBVertices.emplace_back(ComplexVertex{ pE4, UVE, normE, binormE, tanE });

  // Create the new triangles and return
  Vector<Vector<Triangle>> r;
  r.resize(2, Vector<Triangle>());
  if (sideAVertices.size() == 3) {
    r[0].emplace_back(Triangle(sideAVertices[0],
                               sideAVertices[1],
                               sideAVertices[2]));

    r[1].emplace_back(Triangle(sideBVertices[0],
                               sideBVertices[1],
                               sideBVertices[2]));
    r[1].emplace_back(Triangle(sideBVertices[1],
                               sideBVertices[3],
                               sideBVertices[2]));
  }
  else {
    r[0].emplace_back(Triangle(sideAVertices[0],
                               sideAVertices[1],
                               sideAVertices[2]));
    r[0].emplace_back(Triangle(sideAVertices[1],
                               sideAVertices[3],
                               sideAVertices[2]));

    r[1].emplace_back(Triangle(sideBVertices[0],
                               sideBVertices[1],
                               sideBVertices[2]));
  }


  return r;
}
bool
Triangle::isTrianglesCollidingPlane(const Triangle& checkingTriangle,
                                    const Plane& collidingPlane)
{
  // Obtain plain info
  Vector3f plainPoint;
  if (collidingPlane.x != 0) {
    plainPoint = Vector3f(collidingPlane.d / collidingPlane.x, 0.0f, 0.0f);
  }
  else if (collidingPlane.y != 0) {
    plainPoint = Vector3f(0.0f, collidingPlane.d / collidingPlane.y, 0.0f);
  }
  else if (collidingPlane.z != 0) {
    plainPoint = Vector3f(0.0f, 0.0f, collidingPlane.d / collidingPlane.z);
  }
  else {
    return false;
  }
  Vector3f plainNormal = collidingPlane.getNormal().getNormalize();

  Vector3f pX = Vector3f(checkingTriangle.x.position.x,
                         checkingTriangle.x.position.y, 
                         checkingTriangle.x.position.z);
  Vector3f pY = Vector3f(checkingTriangle.y.position.x,
                         checkingTriangle.y.position.y, 
                         checkingTriangle.y.position.z);
  Vector3f pZ = Vector3f(checkingTriangle.z.position.x,
                         checkingTriangle.z.position.y, 
                         checkingTriangle.z.position.z);

  // Check on which side of the plane is each point of the triangle.
  int8 triSides = 0;
  triSides += plainNormal.dot(pX - plainPoint) >= 0.0f ? 1 : -1;
  triSides += plainNormal.dot(pY - plainPoint) >= 0.0f ? 1 : -1;
  triSides += plainNormal.dot(pZ - plainPoint) >= 0.0f ? 1 : -1;

  // If every vertex is in the same side, the value is 3 or -3 and it's not
  // colliding.
  return abs(triSides) < 3;
}
}