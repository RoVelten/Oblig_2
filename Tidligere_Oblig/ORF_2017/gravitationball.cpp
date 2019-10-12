#include "gravitationball.h"

GravitationBall::GravitationBall(float gravity)
{
    g = gravity;
    mVelocity = Vec3(0,0,0);
    previousColor[0] = Vec3 (0,0,0);
    previousColor[1] = Vec3 (0,0,0);
    previousColor[2] = Vec3 (0,0,0);
}

void GravitationBall::setCurrentTriangle(int triangle)
{
    currentTriangle = triangle;
}

int GravitationBall::getCurrentTriangle()
{
    return currentTriangle;
}

float GravitationBall::getGravity()
{
    return g;
}

void GravitationBall::setPreviousColor(Vec3 prevColor, int i)
{
    previousColor[i] = prevColor;
}

Vec3 GravitationBall::getPreviousColor(int i)
{
    return previousColor[i];
}
