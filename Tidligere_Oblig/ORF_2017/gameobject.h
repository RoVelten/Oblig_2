#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "material.h"

class GameObject : protected QOpenGLFunctions
{
public:
    GameObject(float xPos = 0.0, float yPos = 0.0, float zPos = 0.0, QString nameIn = "GameObject");
    virtual ~GameObject();

    virtual void drawGeometry() = 0;
    virtual void setMaterial(Material *materialIn) = 0;
    virtual void setRendermode(int mode) = 0;

    void setViewMatrix(QMatrix4x4 viewMatrix);
    void setprojectionMatrix(QMatrix4x4 projectionMatrix);
    void setName(QString nameIn);
    bool mSelectedInEditor {false};

    QString getName();

    QMatrix4x4 getMatrix();

    class Transform *mTransform;

    GameObject* getParent() { return mParent; }
    void setParent(GameObject *parent);

protected:
    virtual int initGeometry() = 0;

    QMatrix4x4 mModelMatrix;
    QMatrix4x4 mViewMatrix;
    QMatrix4x4 mProjectionMatrix;
    QMatrix4x4 mMVPMatrix;

    GLuint mVertexBuffer;
    GLuint mIndexBuffer;

    Material *mMaterial;

    GameObject* mParent;
    QString name;

    bool mWireFrame = false;
};

#endif // GAMEOBJECT_H
