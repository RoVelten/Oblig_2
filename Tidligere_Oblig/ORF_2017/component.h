#ifndef COMPONENT_H
#define COMPONENT_H
#include "gameobject.h"

class GameObject;

class Component : protected QOpenGLFunctions
{
public:
    Component(GameObject *owner, QString cType);
    virtual ~Component();
    GameObject *getOwner();
    void setOwner(GameObject *newOwner);
    QString getComponentType();

    virtual void update() {}

protected:
    GameObject *mOwner;
    QString componentType;
};

#endif // COMPONENT_H
