#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector3D>
#include "vec3.h"
#include "vec2.h"

//forward declaration:
class GameObject;

class Transform
{
public:
    Transform(GameObject* owner);
    Vec3 getPosition();
    Vec3 getRotation();
    Vec3 getScale();

    void setPosition(float x, float y, float z);
    void setPosition(Vec3 pos) { mLocalPosition = pos; }

    void setRotation(float x, float y, float z);
    void setRotation(Vec3 rot) { mLocalRotation = rot; }

    void setScale(float x, float y, float z);
    void setScale(Vec3 scale) { mLocalScale = scale; }

    void translate(float x, float y, float z);
    void rotate(float x, float y, float z);
    //void rotate(float amount, QVector3D axis);

private:
    GameObject* mGameObject;

    Vec3 mLocalPosition;
    Vec3 mLocalRotation;
    Vec3 mLocalScale;
};

#endif // TRANSFORM_H
