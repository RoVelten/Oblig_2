#ifndef MESH_H
#define MESH_H
#include "component.h"
#include "material.h"

class Mesh : public Component
{
public:
    Mesh(GameObject* owner = nullptr, GLenum mType = GL_TRIANGLES, int LODlevels = 0);
    unsigned int drawGeometry();
    void setMaterial(Material *materialIn);
    void setRendermode(int mode);
    void distanceFromCameraLOD(Vec3 camPos);

    void setViewMatrix(QMatrix4x4 viewMatrix);
    void setprojectionMatrix(QMatrix4x4 projectionMatrix);
    QMatrix4x4 getMatrix();

protected:
    int numOfIndices[3] = {0,0,0};
    int numOfVertices[3] = {0,0,0};
    int LODlvl{0};
    int activeLOD{0};
    QString LODpaths[3];
    GLenum meshType = GL_TRIANGLES;

    QMatrix4x4 mModelMatrix;
    QMatrix4x4 mViewMatrix;
    QMatrix4x4 mProjectionMatrix;

    GLuint mVertexBuffer[3];
    GLuint mIndexBuffer[3];

    Material *mMaterial{nullptr};

    QMatrix4x4 mMVPMatrix;

    bool mWireFrame = false;
};

#endif // MESH_H
