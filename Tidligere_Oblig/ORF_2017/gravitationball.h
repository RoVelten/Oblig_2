#ifndef GRAVITATIONBALL_H
#define GRAVITATIONBALL_H


#include "oktaederball.h"
#include "plane.h"
#include "vec3.h"

class GravitationBall : public OktaederBall
{
public:
    GravitationBall(float gravity = 0.002f);
    int getCurrentTriangle();
    void setCurrentTriangle(int triangle);
    float getGravity();
    void setPreviousColor(Vec3 prevColor, int i);
    Vec3 getPreviousColor(int i);

private:
    float g;
    int currentTriangle{-1};
    Vec3 previousColor[3];

};
#endif // GRAVITATIONBALL_H
