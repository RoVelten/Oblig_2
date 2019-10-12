#include "transform.h"
#include "gameobject.h"

Transform::Transform(GameObject* owner)
{
    mLocalPosition = Vec3(0, 0, 0);
    mLocalRotation = Vec3(0, 0, 0);
    mLocalScale = Vec3(1, 1, 1);

    mGameObject = owner;
}

Vec3 Transform::getPosition()
{
    if (mGameObject->getParent())
    {
        Vec3 parentPos = mGameObject->getParent()->mTransform->getPosition();
        return mLocalPosition + parentPos;
    }

    return mLocalPosition;
}

Vec3 Transform::getRotation()
{
    if (mGameObject->getParent())
    {
        Vec3 parentRot = mGameObject->getParent()->mTransform->getRotation();
        return mLocalRotation + parentRot;
    }

    return mLocalRotation;
}

Vec3 Transform::getScale()
{
    if (mGameObject->getParent() != nullptr)
    {
        Vec3 parentScale = mGameObject->getParent()->mTransform->getScale();
        return mLocalScale + parentScale;
    }

    return mLocalScale;
}

void Transform::setPosition(float x, float y, float z)
{
    mLocalPosition = Vec3(x, y, z);
}

void Transform::setRotation(float x, float y, float z)
{
    mLocalRotation = Vec3(x, y, z);
}

void Transform::setScale(float x, float y, float z)
{
    mLocalScale = Vec3(x, y, z);
}

void Transform::translate(float x, float y, float z)
{
    mLocalPosition = mLocalPosition + Vec3(x, y, z);
}

void Transform::rotate(float x, float y, float z)
{
    mLocalRotation = mLocalRotation + Vec3(x, y, z);
}

//void Transform::rotate(float amount, QVector3D axis)
//{
//    amount = 1.2f;
//    QMatrix4x4 temp{};
//    temp.rotate(amount, axis);
//    QVector4D tempRot(mLocalPosition);

//    tempRot = tempRot*temp;
//    mLocalPosition = QVector3D(tempRot);
//    qDebug() << mLocalRotation;
//}
