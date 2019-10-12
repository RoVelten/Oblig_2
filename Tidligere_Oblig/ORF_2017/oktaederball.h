#ifndef OKTAEDERBALL_H
#define OKTAEDERBALL_H
#include <cmath>
#include <string>
#include "gameobject.h"
#include "vec3.h"
#include "material.h"

class Vertex;
class OktaederBall : public GameObject
{
public:
    OktaederBall(int n=0);
    ~OktaederBall();
    int initGeometry();
    void drawGeometry();
    void setRendermode(int mode);

    void setMaterial(Material *materialIn);

private:
    int mRecursions = 0;
    int mIndex = 0;
    float mRadius = 0;

    Vertex* mVertices;

    GLuint mVertexBuffer;
    GLuint mIndexBuffer;
    GLuint mNumOfVertices;

    Material *mMaterial;

    QMatrix4x4 mMVPMatrix;

    void lagTriangel(const Vec3& v1, const Vec3& v2, const Vec3& v3);
    void subDivide(const Vec3& a, const Vec3& b, const Vec3& c, int n);
    void oktaederUnitBall();

};

#endif
