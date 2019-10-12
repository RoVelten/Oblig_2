#ifndef CAMERA_H
#define CAMERA_H

#include <QVector4D>
#include <QMatrix4x4>
#include "transform.h"
#include "gameobject.h"

class Camera : public GameObject
{
public:
    Camera(int height = 800, int width = 1200, float nearPlane = 1.0f, float farPlane = 400.0f, float fov = 45.0f);
    void rotate(float angle, const QVector3D &axis);
    void translate (float x, float y, float z);
    void setAspectRatio(int w, int h, bool ortho = false);
    void setBackgroundColor(float r, float g, float b, float a);

    void drawGeometry();
    int initGeometry();
    //for compability with GameObject
    //will be used when main camera is visible in editor
    //qDebug-stuff just to silence warnings...
    void setMaterial(Material *materialIn){qDebug() << materialIn;}
    void setRendermode(int mode){qDebug() << mode;}

    QMatrix4x4 getPerspectiveMatrix() {return mPerspectiveMatrix;}

    QVector4D mBackgroundColor ;

private:

    float mNearPlane;
    float mFarPlane;
    float mFieldOfView;
    int mHeight;
    int mWidth;
    float mAspectRatio;

    QMatrix4x4 mPerspectiveMatrix{};
    QMatrix4x4 mViewMatrix{};
};

#endif // CAMERA_H
