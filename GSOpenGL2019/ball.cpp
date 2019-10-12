#include "ball.h"
#include "vec3.h"
#include "vec2.h"

//Burde skrive om denne klassen så den arver fra GameObject,
//og implementeres i GameEngine. Må da sende den til mGeometry vectoren.
//Denne klassen holder på koordinater, men siden den ikke tegnes noe sted gjør den
//ingenting ennå.

//Må lage et Ball minBall i GameEngine.
/*
Ball::Ball()
{
    Ball::tetrahedron(storrelse);
}
*/
Ball::Ball(float xPos, float yPos, float zPos, QString name) : GameObject(xPos, yPos, zPos, name)
{
     initGeometry();
     Ball::tetrahedron(storrelse);

}

Ball::~Ball()
{
}

void Ball::drawGeometry()
{
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    mMaterial->useMaterial();

    //refresh modelMatrix:
    getMatrix();

    mMVPMatrix = mProjectionMatrix*mViewMatrix*mModelMatrix;
    mMaterial->setMVPMatrix(mMVPMatrix);

    // Offset for position
    // Positions are the first data, therefor offset is 0
    int offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getPositionAttribute()), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offset));

    // Offset for vertex coordinates
    // before normals
    offset += sizeof(Vec3);

    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getNormalAttribute()), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offset));

    // Offset for normal coordinates
    // before UVs
    offset += sizeof(Vec3);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getTextureAttribute()), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offset));

    // Draw cube geometry using indices from VBO 1
    if (!mWireFrame)
        glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
    else
        glDrawElements(GL_LINES, 34, GL_UNSIGNED_SHORT, 0);

    //Write errors if any:

//    GLenum err = GL_NO_ERROR;
//    while((err = glGetError()) != GL_NO_ERROR)
//    {
//        qDebug() << "glGetError returns " << err;
//    }

    //Unbind buffers:
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Unbind shader
    glUseProgram(0);
}

//Her lages trekantene.
void Ball::triangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
    ballFarger[minTeller] = 0.0f;
    ballFarger[minTeller+1] = 2.0f;
    ballFarger[minTeller+2] = 0.0f;
    ballFarger[minTeller+3] = 5.0f;
    ballFarger[minTeller+4] = 0.0f;
    ballFarger[minTeller+5] = 5.0f;
    ballFarger[minTeller+6] = 0.0f;
    ballFarger[minTeller+7] = 2.0f;
    ballFarger[minTeller+8] = 0.0f;

    ballKoordinater[minTeller] = c[noeTeller];
    ballKoordinater[minTeller+1] = c[noeTeller+1];
    ballKoordinater[minTeller+2] = c[noeTeller+2];

    ballKoordinater[minTeller+3] = b[noeTeller];
    ballKoordinater[minTeller+4] = b[noeTeller+1];
    ballKoordinater[minTeller+5] = b[noeTeller+2];

    ballKoordinater[minTeller+6] = a[noeTeller];
    ballKoordinater[minTeller+7] = a[noeTeller+1];
    ballKoordinater[minTeller+8] = a[noeTeller+2];

    minTeller +=9;
}

void Ball::normalize(GLfloat *p)
{
    double d = 0.0f;
    int i;

    for( i=0; i<3; i++ )
    {
        d += p[i]*p[i];
    }

    d = sqrt(d);

    if( d > 0.0 )
    {
        for( i=0; i<3; i++)
        {
            p[i] /= d;
        }
    }
}

void Ball::divide_triangle(GLfloat *a, GLfloat *b, GLfloat *c, int n)
{
    GLfloat v1[3], v2[3], v3[3];
    int j;

    if(n>0)
    {
        for( j=0; j<3; j++)
        {
            v1[j] = a[j] + b[j];
        }
        Ball::normalize(v1);

        for( j=0; j<3; j++)
        {
            v2[j] = a[j] + c[j];
        }
        Ball::normalize(v2);

        for( j=0; j<3; j++)
        {
            v3[j] = c[j] + b[j];
        }
        Ball::normalize(v3);

        Ball::divide_triangle(a, v2, v1, n-1);
        Ball::divide_triangle(c, v3, v2, n-1);
        Ball::divide_triangle(b, v1, v3, n-1);
        Ball::divide_triangle(v1, v2, v3, n-1);
    }

    else
    {
        Ball::triangle(a, b, c);
    }
}

void Ball::tetrahedron(int n)
{
    Ball::divide_triangle(v[0], v[1], v[2], n);
    Ball::divide_triangle(v[3], v[2], v[1], n);
    Ball::divide_triangle(v[0], v[3], v[1], n);
    Ball::divide_triangle(v[0], v[2], v[3], n);
}

int Ball::initGeometry()
{
    //For now hard coded as a cube:

    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.

    //qDebug() << "Init Geometry - Cube";
    //Format: Position, Normal, UV
    Vertex vertices[] = {
        // Vertex data for face 0 - front

    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {

    };

    initializeOpenGLFunctions();

    // Transfer vertex data to VBO 0
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 24*sizeof(Vertex), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34*sizeof(GLushort), indices, GL_STATIC_DRAW);

    return 0;
}

void Ball::setRendermode(int mode)
{
    if (mode == 1)
        mWireFrame = true;
    else if (mode == 0)
        mWireFrame = false;
}

void Ball::setMaterial(Material *materialIn)
{
    mMaterial = materialIn;
}
