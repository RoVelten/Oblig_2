#include "beziercurve.h"
#include "vertex.h"

BezierCurve::BezierCurve(const Vec3 &b0, const Vec3 &b1, const Vec3 &b2, const Vec3 &b3)
{
    addControlPoints(b0,b1);
    addControlPoints(b2,b3);
    initGeometry();
    name = "BezierCurve";
}

BezierCurve::~BezierCurve()
{
    //Clear the vector and frees the memory
    mControlPoints.clear();
    mControlPoints.shrink_to_fit();
    mPath.clear();
    mPath.shrink_to_fit();

}

int BezierCurve::initGeometry()
{
    //Clears the path
    mPath.clear();
    mPath.shrink_to_fit();

    unsigned int controlPoints = mControlPoints.size();
    unsigned int arrays = (controlPoints - 2) / 2;
    mVertices = arrays * 11;

    //mIndicesCount = mVertices * 2;
    Vertex v[mVertices];
    int indiceArray[mVertices];
    Vec3 lastControlPoint;

    for(unsigned int i=0;i<arrays;i++)
    {
        if(i == 0)
        {
            setControlPoints(mControlPoints[i], mControlPoints[i+1], mControlPoints[i+2], mControlPoints[i+3]);
            lastControlPoint = mControlPoints[i+3];
        }
        else
        {
            setControlPoints(lastControlPoint, lastControlPoint * 1.2f, mControlPoints[i * 2 + 2], mControlPoints[i*2 + 3]);
            lastControlPoint = mControlPoints[i*2 + 3];
        }
        qDebug() << " |:" << i*2 <<  " ||:"<< i*2+1 <<  " |||:" << i*2+2 <<  " |V:" << i*2+3;

        for(int u{0}; u<=10;u++)
        {
            float t = 0.1*u;
            Vec3 b = evaluateBezier(3,t);

            v[(11*i) + u].set_xyz(b.x,b.y,b.z);
            v[(11*i) + u].set_rgb(b.x,b.y,b.z);//midlertidig}
            indiceArray[(11*i) + u] = (11*i) + u;
            mPath.push_back(v[11*i + u].get_xyz()); //for those who want path.
        }
    }


    initializeOpenGLFunctions();

    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mVertices*sizeof(Vertex), v, GL_STATIC_DRAW);

    return 0;
}

void BezierCurve::drawGeometry()
{
    initializeOpenGLFunctions();    //makeCurrent();

    //fra DrawGeometry cube.
    getMatrix();
    mMVPMatrix = mProjectionMatrix*mViewMatrix*mModelMatrix;
    mMaterial->setMVPMatrix(mMVPMatrix);
    //slutt

    int offset = 0;

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);

    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getPositionAttribute()), 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), reinterpret_cast<const void*> (offset));
    offset = 3*sizeof(GLfloat);

    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getNormalAttribute()), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<const void*> (offset));

    //    if (textureAttribute != -1)
    //    {
    //    offset = 6*sizeof(GLfloat);
    //    glVertexAttribPointer(textureAttribute, 2, GL_FLOAT, GL_FALSE,
    //    sizeof(Vertex), reinterpret_cast<const void*> (offset));

    //    glBindTexture(GL_TEXTURE_2D, m_texture);
    //    }

    glDrawArrays(GL_LINE_STRIP, 0, mVertices);

    //Unbind buffers:
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Unbind shader
    glUseProgram(0);
}


void BezierCurve::setRendermode(int mode)
{
    if (mode == 1)
        mWireFrame = true;
    else if (mode == 0)
        mWireFrame = false;
}

void BezierCurve::setMaterial(Material *materialIn)
{
    mMaterial = materialIn;
}

void BezierCurve::addControlPoints(const Vec3 &firstPoint, const Vec3 &secondPoint)
{
    mControlPoints.push_back(firstPoint);
    mControlPoints.push_back(secondPoint);
    initGeometry();
}

void BezierCurve::setControlPoints(const Vec3 &b0, const Vec3 &b1, const Vec3 &b2, const Vec3 &b3)
{
    b[0]=b0;
    b[1]=b1;
    b[2]=b2;
    b[3]=b3;
}

Vec3 BezierCurve::getControlPoints(int controlPointNumber)
{
    return b[controlPointNumber];
}

Vec3 BezierCurve::evaluateBezier(int degree, float t)
{
    Vec3 c[4];

    for(int i=0;i<4;i++)
        c[i]=b[i];

    for(int k=1;k<=degree;k++)
    {
        for(int i=0;i<degree-k+1;i++)
            c[i]=c[i]*(1-t)+c[i+1]*t;
    }

    return c[0];
}

Vec3 BezierCurve::getPath(unsigned int number) const
{
    if(number < mPath.size())
        return mPath.at(number);
    else
        return Vec3 (1337,1337,1337);
}


