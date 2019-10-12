#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "vec3.h"
#include "gameobject.h"
#include <vector>

class BezierCurve : public GameObject
{
public:
    BezierCurve(const Vec3 &b0,const Vec3 &b1,const Vec3 &b2,const Vec3 &b3);
    ~BezierCurve();
    void drawGeometry();
    int initGeometry();
    void setRendermode(int mode);
    void setMaterial(Material *materialIn);
    void addControlPoints(const Vec3 &firstPoint,const Vec3 &secondPoint);
    void setControlPoints(const Vec3 &b0,const Vec3& b1, const Vec3& b2,const Vec3 &b3);
    Vec3 getControlPoints(int controlPointNumber);
    Vec3 evaluateBezier(int degree,float t);
    Vec3 getPath(unsigned int number) const;

private:
    Vec3 b[4];
    std::vector<Vec3> mControlPoints;
    std::vector<Vec3> mPath;
    int mVertices;
    int mIndicesCount;
};

#endif // BEZIERCURVE_H
