#ifndef BALL_H
#define BALL_H

#include <QtGui/QOpenGLFunctions>
#include <cmath>
#include "gameobject.h"
#include "vertex.h"
#include "material.h"

class Ball : public GameObject
{
public:
    //Setter in kode fra cubeklassen her for å prøve å implementere som GameObject.
    Ball(float xPos = 0.0, float yPos = 0.0, float zPos = 0.0, QString name = "Ball");
    ~Ball();

    void drawGeometry();
    int initGeometry();
    void setRendermode(int mode);

    void setMaterial(Material *materialIn);

    //Under er koden fra gamle ballklassen.
    void triangle(GLfloat *a, GLfloat *b, GLfloat *c);
    void tetrahedron(int n);
    void normalize(GLfloat *p);
    void divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int n);

private:
    GLuint mVertexBuffer;
    GLuint mIndexBuffer;

    Material *mMaterial;

    QMatrix4x4 mMVPMatrix;

public:
    GLfloat ballRadius = 7;
    GLfloat ballKoordinater[100000];
    GLfloat ballFarger[100000];

    GLfloat m_x = 0.0f;
    GLfloat m_y = 0.0f;
    GLfloat m_z = 0.0f;
    GLfloat m_r = 0.5f;
    GLfloat m_teta = 0.0f;
    GLfloat m_retning = -1.0f;

public:
    int minTeller = 0;
    int noeTeller = 0;
    int storrelse = 4;

    GLfloat v[4][3] = {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.942809f, -0.333333f},
        {-0.816497f, -0.471405f, -0.333333f},
        {0.816497f, -0.471405f, -0.333333f}
    };

};

#endif // BALL_H

