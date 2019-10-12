#ifndef VEC2_H
#define VEC2_H

// Small class without cpp-file
#define _USE_MATH_DEFINES
#include <QtDebug>
#include <qmatrix4x4.h>

#include <qgl.h>    // definerer GLfloat
#include <cmath>

#include "vec3.h"

struct Vec2
{
    GLfloat x;
    GLfloat y;
    Vec2(GLfloat a=0.0, GLfloat b=0.0) : x(a), y(b) { }
    const Vec2& operator = (const Vec2& v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }
    Vec2 operator + (const Vec2& v) const
    {
        Vec2 u;
        u.x = x + v.x;
        u.y = y + v.y;
        return u;
    }
    Vec2 operator - (const Vec2& v) const
    {
        Vec2 u;
        u.x = x - v.x;
        u.y = y - v.y;
        return u;
    }
    float operator ^ (const Vec2& v) const      //To get the cross product of two vectors.
    {
        float u;
        u =  x*v.y - y*v.x;
        return u;
    }
    void Vec3_XZtoVec2(Vec3 &in)    //To get the XZ plane from a Vec3. Used for barycentric coordinates.
    {
        this->x = in.x;
        this->y = in.z;
    }

    Vec3 barycentricCoordinates(const Vec3& P1, const Vec3& P2, const Vec3& P3) //Finds the Baricentric coordinates and return it as a Vec3.
    {
        Vec3 P1P2 = P2 - P1;
        Vec3 P1P3 = P3 - P1;

        float areal = P1P2.x * P1P3.z -  P1P2.z * P1P3.x; //Arealet til trekanten

        Vec2 PP1;
        PP1.x = P1.x - x;
        PP1.y = P1.z - y;

        Vec2 PP2;
        PP2.x = P2.x - x;
        PP2.y = P2.z - y;

        Vec2 PP3;
        PP3.x = P3.x - x;
        PP3.y = P3.z - y;

        float u = (PP2 ^ PP3)/areal;
        float v = (PP3 ^ PP1)/areal;
        float w = (PP1 ^ PP2)/areal;

        //float check = u + v + w;
        //qDebug() << check;
        //qDebug() << "u: " << u;
        //qDebug() << "v: " << v;
        //qDebug() << "w: " << w;
        Vec3 barycentricPos(u, v, w);

        return barycentricPos;
    }
};

#endif // VEC2_H
