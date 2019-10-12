//#ifndef PLANE_H
//#define PLANE_H

//#include <QOpenGLFunctions>
//#include <QOpenGLShaderProgram>
//#include <QOpenGLBuffer>
//#include <QMatrix4x4>

//#include "transform.h"
//#include "gameobject.h"
//#include "vec3.h"
//#include "vec2.h"
//#include "vertex.h"


//class Plane : public GameObject
//{
//public:
//    Plane(float xPos = 0.0, float yPos = 0.0, float zPos = 0.0, int mSize = 50, float mSpacing = 3.0f, QString name = "Plane");

//    void setRendermode(int mode);
//    void setMaterial(Material *materialIn);
//    void drawGeometry();

//    Vec3 findTriangle(Vec2 objectPos);
//    void colorTriangle(Vec2 objectPos);
//    Vec3 normalOfCurrentTriangle();
//    float angleOfCurrentTriangle();
//    Vec3 currTriangleHighY();
//    Vec3 currTriangleLowY();

//private:
//    int initGeometry();
//    void refreshVertices();

//    //mapSize should be set to the same as pixles on one side of the height map
//    //This sets how many vertecies there will be;
//    int mapSize; //= 16; Try to disable, see what happens.
//    //int heightFactor = 500;   //used to scale height - not used now
//    float mapFactor; // = 3.0; Try disabling it, reenable if something goes wrong.      //used to scale width/length - length between vertecies

//    Vertex *vertices;
//    GLsizei indexCount;
//    QMatrix4x4 mModelMatrix;

//    GLuint mVertexBuffer;
//    GLuint mIndexBuffer;

//    Material *mMaterial;

//    QMatrix4x4 mMVPMatrix;

//    //VSIM
//    Vec3 previousTriangle;
//    Vec3 prevColorP1 = 0;
//    Vec3 prevColorP2 = 0;
//    Vec3 prevColorP3 = 0;
//};

//#endif // PLANE_H


