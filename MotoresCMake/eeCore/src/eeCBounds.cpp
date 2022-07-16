#include "eeCBounds.h"

#include <eeVector4.h>

#include "eeActor.h"
#include "eeCStaticMesh.h"
#include "eeStaticMesh.h"
#include "eeCSkeletalMesh.h"
#include "eeSkeletalMesh.h"
#include "eeCTransform.h"

namespace eeEngineSDK {
void
CBounds::update()
{
  Vector3f furtherPosition = Vector3f(0.0f, 0.0f, 0.0f);

  SPtr<CStaticMesh> actorModel = m_actor->getComponent<CStaticMesh>();
  if (actorModel) {
    SPtr<StaticMesh> cmpModel = actorModel->getStaticMesh();
    if (cmpModel) {
      m_sphereBound = cmpModel->getBoundingSphere();
      furtherPosition = cmpModel->getFurtherPosition();
      m_boxBound = cmpModel->getBoundingBox();
    }
    else {
      return;
    }
  }
  else {
    SPtr<CSkeletalMesh> actorSkeletalMesh = m_actor->getComponent<CSkeletalMesh>();
    if (actorSkeletalMesh) {
      SPtr<SkeletalMesh> cmpSkeletalMesh = actorSkeletalMesh->getModel();
      if (cmpSkeletalMesh) {
        m_sphereBound = cmpSkeletalMesh->getBoundingSphere();
        furtherPosition = cmpSkeletalMesh->getFurtherPosition();
        m_boxBound = cmpSkeletalMesh->getBoundingBox();
      }
      else {
        return;
      }
    }
    else {
      return;
    }
  }

  SPtr<CTransform> trans = m_actor->getTransform();

  m_sphereBound =
  Sphere(trans->getGlobalPosition(), m_sphereBound.getRadious() * trans->getScale().getMagnitud());


  Matrix4f modelMatrix = trans->getModelMatrix();

  Vector3f A = m_boxBound.getA();
  Vector3f B = m_boxBound.getB();

  Vector<Vector4f> Corners;

  Corners.emplace_back(Vector4f(A.x, A.y, A.z, 0.0f));
  Corners.emplace_back(Vector4f(B.x, A.y, A.z, 0.0f));
  Corners.emplace_back(Vector4f(A.x, B.y, A.z, 0.0f));
  Corners.emplace_back(Vector4f(B.x, B.y, A.z, 0.0f));
  Corners.emplace_back(Vector4f(A.x, A.y, B.z, 0.0f));
  Corners.emplace_back(Vector4f(B.x, A.y, B.z, 0.0f));
  Corners.emplace_back(Vector4f(A.x, B.y, B.z, 0.0f));
  Corners.emplace_back(Vector4f(B.x, B.y, B.z, 0.0f));

  Vector3f maxBound(-99999.99f, -99999.99f, -99999.99f);
  Vector3f minBound(99999.99f, 99999.99f, 99999.99f);
  for (int32 i = 0; i < 6; ++i) {
    Vector4f newCorner = modelMatrix * Corners[i];

    maxBound.x = newCorner.x > maxBound.x ? newCorner.x : maxBound.x;
    maxBound.y = newCorner.y > maxBound.y ? newCorner.y : maxBound.y;
    maxBound.z = newCorner.z > maxBound.z ? newCorner.z : maxBound.z;

    minBound.x = newCorner.x < minBound.x ? newCorner.x : minBound.x;
    minBound.y = newCorner.y < minBound.y ? newCorner.y : minBound.y;
    minBound.z = newCorner.z < minBound.z ? newCorner.z : minBound.z;
  }

  m_boxBound = BoxAAB(trans->getGlobalPosition() + minBound, maxBound - minBound);
}
Sphere
CBounds::getSphereBound()
{
  return m_sphereBound;
}
BoxAAB
CBounds::getBoxBound()
{
  return m_boxBound;
}
}