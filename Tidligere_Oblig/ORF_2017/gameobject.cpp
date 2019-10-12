#include "gameobject.h"
#include "vec3.h"
#include "transform.h"

#include <QVector2D>
#include <QVector3D>

GameObject::GameObject(float xPos, float yPos, float zPos, QString nameIn) :mParent(nullptr)
{
    initializeOpenGLFunctions();

    mTransform = new Transform(this);
    mTransform->setPosition(Vec3(xPos, yPos, zPos));
    name = nameIn;
}

GameObject::~GameObject()
{
    delete mTransform;
}

void GameObject::setParent(GameObject *parent)
{
    mParent = parent;

    //Do something to my own transform?
}

void GameObject::setViewMatrix(QMatrix4x4 viewMatrix)
{
    mViewMatrix = viewMatrix;
}

void GameObject::setprojectionMatrix(QMatrix4x4 projectionMatrix)
{
    mProjectionMatrix = projectionMatrix;
}

void GameObject::setName(QString nameIn)
{
    name = nameIn;
}

QString GameObject::getName()
{
    return name;
}

QMatrix4x4 GameObject::getMatrix()
{
    mModelMatrix.setToIdentity();
    mModelMatrix.translate(mTransform->getPosition().x, mTransform->getPosition().y, mTransform->getPosition().z );
    mModelMatrix.rotate(mTransform->getRotation().x, 1.0, 0.0, 0.0);
    mModelMatrix.rotate(mTransform->getRotation().y, 0.0, 1.0, 0.0);
    mModelMatrix.rotate(mTransform->getRotation().z, 0.0, 0.0, 1.0);
    mModelMatrix.scale(mTransform->getScale().x, mTransform->getScale().y, mTransform->getScale().z);
    //mModelMatrix.translate(mTransform.mPosition);

    return mModelMatrix;
}
