//#ifndef TRIANGLESURFACE_H
//#define TRIANGLESURFACE_H

//#include "gameobject.h"
//#include "vec3.h"
//#include "vertex.h"
//#include "transform.h"
//#include "gravitationball.h"

//class TriangleSurface : public GameObject
//{
//public:
//    TriangleSurface(QString fileName = "", float scale = 1.0f, float xPos = 0.0f, float yPos = 0.0f, float zPos = 0.0f, QString name = "TriangleSurface");
//    ~TriangleSurface();

//    void drawGeometry();

//    void setRendermode(int mode);
//    void setMaterial(Material *materialIn);
//    void checkCollision(GravitationBall *collisionObject);
//    Vec3 normalOfTriangle();

//private:
//    int initGeometry();
//    int initGeometry(std::string inPath);
//    void setCurrentTriangle(Vec2 objectPos);
//    int getS1Neighbour(int currTriangle);
//    int getS2Neighbour(int currTriangle);
//    int getS3Neighbour(int currTriangle);

//    void colorTriangle(GravitationBall *collisionObject);
//    Vertex* mVertices;
//    GLushort* mIndices;
//    int mNumOfVertices{0};
//    int mNumOfIndices{0};
//    float mScale{0.0f};

//    int currentTriangle{-1};
//};
//#endif // TRIANGLESURFACE_H
