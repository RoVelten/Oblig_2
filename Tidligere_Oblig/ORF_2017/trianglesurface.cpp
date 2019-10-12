//// Trianglesurface.cpp 15/2/17
//#include <QDebug>
//#include <QImage>
//#include <cstdio>
//#include <iostream>
//#include "trianglesurface.h"
//#include "vertex.h"

//TriangleSurface::TriangleSurface(QString fileName, float scale, float xPos, float yPos, float zPos, QString name) : GameObject(xPos, yPos, zPos, name)
//{
//    mScale = scale;
//    initGeometry(fileName.toStdString());
//}

//TriangleSurface::~TriangleSurface()
//{

//}

//int TriangleSurface::initGeometry(std::string inPath)
//{
//    const char* path = inPath.c_str();

//    //Open File
//    FILE * file = fopen(path, "r");

//    if(file == nullptr)
//    {
//        qDebug() << "Could not open file at: " << path;
//    }

//    char oneWord[64] = "";
//    int remaining;

//    remaining = fscanf(file, "%s", &oneWord);

//    mNumOfVertices = std::stoi(oneWord);
//    std::vector<Vec3> pointPos;

//    for(int i{0}; i < mNumOfVertices; i++)
//    {
//        Vec3 tempVec(0.0f, 0.0f, 0.0f);
//        remaining = fscanf(file, "%f %f %f", &tempVec.x, &tempVec.z, &tempVec.y);
//        tempVec = tempVec * mScale;
//        pointPos.push_back(tempVec);
//    }

//    fclose(file);

//    mVertices = new Vertex[pointPos.size()];

//    for (int i = 0; i < mNumOfVertices; i++)
//    {
//        mVertices[i].set_xyz(pointPos[i]);
//        mVertices[i].set_normal(0.0f + i*0.1f, 1.0f - i*0.1f, 0.0f);
//    }

//    for (int i = 0; i < mNumOfVertices; i++)
//    {
//        //qDebug() << i << " " << mVertices[i].get_xyz().x << " " << mVertices[i].get_xyz().y << " " << mVertices[i].get_xyz().z;
//    }

//    mNumOfIndices = 14*3;
//    GLushort tempIndices[] =
//    {
//      0,4,1,
//      1,4,6,
//      6,4,9,
//      6,9,10,
//      10,5,6,
//      5,1,6,
//      3,1,5,
//      5,10,8,
//      8,10,11,
//      11,7,8,
//      8,7,5,
//      7,3,5,
//      7,2,3,
//      3,2,1
//    };

//    mIndices = new GLushort[mNumOfIndices];
//    for (int i = 0; i < mNumOfIndices; i++)
//    {
//        mIndices[i]=tempIndices[i];
//    }

//    initializeOpenGLFunctions();

//    // Transfer vertex data to VBO 0
//    glGenBuffers(1, &mVertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, mNumOfVertices*sizeof(Vertex), mVertices, GL_STATIC_DRAW);

//    // Transfer index data to VBO 1
//    glGenBuffers(1, &mIndexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNumOfIndices*sizeof(GLushort), mIndices, GL_STATIC_DRAW);

//    return 0;
//}

//void TriangleSurface::drawGeometry()
//{
//    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
//    mMaterial->useMaterial();

//    //refresh modelMatrix:
//    getMatrix();

//    mMVPMatrix = mProjectionMatrix*mViewMatrix*mModelMatrix;
//    mMaterial->setMVPMatrix(mMVPMatrix);

//    int offset = 0;
//    // Tell OpenGL programmable pipeline how to locate vertex position data
//    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getPositionAttribute()), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offset));

//    // Offset for vertex coordinates
//    // before normals
//    offset += sizeof(Vec3);

//    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getNormalAttribute()), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offset));

//    // Offset for normal coordinates
//    // before UVs
//    offset += sizeof(Vec3);

//    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//    glVertexAttribPointer(static_cast<GLuint>(mMaterial->getTextureAttribute()), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offset));

//    glDrawElements(GL_TRIANGLES, mNumOfIndices, GL_UNSIGNED_SHORT, 0);

//    //Unbind buffers:
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//    //Unbind shader
//    glUseProgram(0);
//}

//void TriangleSurface::setCurrentTriangle(Vec2 objectPos)
//{
//    if (currentTriangle == -1)
//    {
//        for(int i{0}; i < mNumOfIndices; i++)
//        {
//            if (i == mNumOfIndices)
//            {
//                qDebug() << "Item is outside the surface";
//                currentTriangle = -1;
//                break;
//            }
//            Vec3 tempPoint;
//            tempPoint.x = mIndices[i];
//            i++;
//            tempPoint.y = mIndices[i];
//            i++;
//            tempPoint.z = mIndices[i];

//            Vec2 tempP1 = mVertices[int(tempPoint.x)].get_xz();

//            Vec2 tempP2 = mVertices[int(tempPoint.y)].get_xz();

//            Vec2 tempP3 = mVertices[int(tempPoint.z)].get_xz();

//            Vec3 baryCoor = objectPos.barysentricCalculation(tempP1, tempP2, tempP3);

//            if(baryCoor.x > 0 && baryCoor.x < 1 && baryCoor.y > 0 && baryCoor.y < 1 && baryCoor.z > 0 && baryCoor.z < 1)
//            {
//                currentTriangle = (i-2)/3;
//            }
//        }
//    }
//    else
//    {
//        Vec3 tempTriangle;

//        tempTriangle.x = mIndices[currentTriangle*3];
//        tempTriangle.y = mIndices[currentTriangle*3+1];
//        tempTriangle.z = mIndices[currentTriangle*3+2];

//        Vec2 p1 = mVertices[int(tempTriangle.x)].get_xz();
//        Vec2 p2 = mVertices[int(tempTriangle.y)].get_xz();
//        Vec2 p3 = mVertices[int(tempTriangle.z)].get_xz();

//        Vec3 baryCoor = objectPos.barysentricCalculation(p1, p2, p3);

//        if (baryCoor.x < 0)
//        {
//            currentTriangle = getS1Neighbour(currentTriangle);
//        }
//        else if (baryCoor.y < 0)
//        {
//            currentTriangle = getS2Neighbour(currentTriangle);
//        }
//        else if (baryCoor.z < 0)
//        {
//            currentTriangle = getS3Neighbour(currentTriangle);
//        }
//    }

//}

//void TriangleSurface::setRendermode(int mode)
//{
//    if (mode == 1)
//        mWireFrame = true;
//    else if (mode == 0)
//        mWireFrame = false;
//}

//void TriangleSurface::setMaterial(Material *materialIn)
//{
//    mMaterial = materialIn;
//}

//int TriangleSurface::initGeometry()
//{
//    return 0;
//}

//Vec3 TriangleSurface::normalOfTriangle()
//{
//    Vec3 tempTriangle;
//    tempTriangle.x = mIndices[currentTriangle*3];
//    tempTriangle.y = mIndices[currentTriangle*3+1];
//    tempTriangle.z = mIndices[currentTriangle*3+2];
//    Vec3 p1 = mVertices[int(tempTriangle.x)].get_xyz();
//    Vec3 p2 = mVertices[int(tempTriangle.y)].get_xyz();
//    Vec3 p3 = mVertices[int(tempTriangle.z)].get_xyz();

//    Vec3 p1p2 = p2 - p1;
//    Vec3 p1p3 = p3 - p1;

//    Vec3 normal = p1p2 ^ p1p3;
//    return (normal.normalized());
//}

//void TriangleSurface::colorTriangle(GravitationBall *collisionObject)
//{
//    int tempTriangle = collisionObject->getCurrentTriangle();

//    Vec3 tempPoints;
//    tempPoints.x = mIndices[tempTriangle*3];
//    tempPoints.y = mIndices[tempTriangle*3+1];
//    tempPoints.z = mIndices[tempTriangle*3+2];

//    mVertices[int(tempPoints.x)].set_normal(collisionObject->getPreviousColor(0));
//    mVertices[int(tempPoints.y)].set_normal(collisionObject->getPreviousColor(1));
//    mVertices[int(tempPoints.z)].set_normal(collisionObject->getPreviousColor(2));

//    tempPoints.x = mIndices[currentTriangle*3];
//    tempPoints.y = mIndices[currentTriangle*3+1];
//    tempPoints.z = mIndices[currentTriangle*3+2];

//    collisionObject->setPreviousColor(mVertices[int(tempPoints.x)].get_rgb(), 0);
//    collisionObject->setPreviousColor(mVertices[int(tempPoints.y)].get_rgb(), 1);
//    collisionObject->setPreviousColor(mVertices[int(tempPoints.z)].get_rgb(), 2);

//    mVertices[int(tempPoints.x)].set_normal(Vec3(0.0f, 0.0f, 1.0f));
//    mVertices[int(tempPoints.y)].set_normal(Vec3(0.0f, 0.0f, 1.0f));
//    mVertices[int(tempPoints.z)].set_normal(Vec3(0.0f, 0.0f, 1.0f));

//}

////Code from SteinarBranch VSIM,
//void TriangleSurface::checkCollision(GravitationBall *collisionObject)
//{
//    Vec2 tempPosition = Vec2 (collisionObject->mTransform->getPosition().x, collisionObject->mTransform->getPosition().z);
//    currentTriangle = collisionObject->getCurrentTriangle();
//    setCurrentTriangle(tempPosition);
//    //colorTriangle(collisionObject);
//    collisionObject->setCurrentTriangle(currentTriangle);
//    qDebug() << currentTriangle;

//    if(currentTriangle != -1)
//    {
//        int randomPoint = mIndices[currentTriangle*3];
//        Vec3 ballToPoint = mVertices[randomPoint].get_xyz() - collisionObject->mTransform->getPosition();

//        Vec3 normal = normalOfTriangle();

//        float dotProduct = normal * ballToPoint;

//        if (dotProduct < 0)
//        {
//            dotProduct = -dotProduct;
//        }

//        if (collisionObject->mTransform->getScale().x <= dotProduct)
//        {
//           // qDebug() << "collision";
//            Vec3 velOntoNorm = normal * (collisionObject->getVelocity() * normal);

//            collisionObject->addForce(normal * velOntoNorm.length());
//        }
//    }
//}

//int TriangleSurface::getS1Neighbour(int currTriangle)
//{
//    int i{-1};

//    switch(currTriangle)
//    {
//    case 0:
//        i = 1;
//        break;
//    case 1:
//        i = 2;
//        break;
//    case 2:
//        i = -1;
//        break;
//    case 3:
//        i = -1;
//        break;
//    case 4:
//        i = 5;
//        break;
//    case 5:
//        i = 1;
//        break;
//    case 6:
//        i = 5;
//        break;
//    case 7:
//        i = 8;
//        break;
//    case 8:
//        i = -1;
//        break;
//    case 9:
//        i = 10;
//        break;
//    case 10:
//        i = 11;
//        break;
//    case 11:
//        i = 6;
//        break;
//    case 12:
//        i = 13;
//        break;
//    case 13:
//        i = -1;
//        break;
//    default:
//        break;
//    }

//    return i;
//}

//int TriangleSurface::getS2Neighbour(int currTriangle)
//{
//    int i{-1};

//    switch(currTriangle)
//    {
//    case 0:
//        i = -1;
//        break;
//    case 1:
//        i = 5;
//        break;
//    case 2:
//        i = 3;
//        break;
//    case 3:
//        i = 4;
//        break;
//    case 4:
//        i = 3;
//        break;
//    case 5:
//        i = 4;
//        break;
//    case 6:
//        i = 11;
//        break;
//    case 7:
//        i = 10;
//        break;
//    case 8:
//        i = 9;
//        break;
//    case 9:
//        i = 8;
//        break;
//    case 10:
//        i = 7;
//        break;
//    case 11:
//        i = 10;
//        break;
//    case 12:
//        i = 11;
//        break;
//    case 13:
//        i = 6;
//        break;
//    default:
//        break;
//    }

//    return i;
//}

//int TriangleSurface::getS3Neighbour(int currTriangle)
//{
//    int i{-1};

//    switch(currTriangle)
//    {
//    case 0:
//        i = -1;
//        break;
//    case 1:
//        i = 0;
//        break;
//    case 2:
//        i = 1;
//        break;
//    case 3:
//        i = 2;
//        break;
//    case 4:
//        i = 7;
//        break;
//    case 5:
//        i = 6;
//        break;
//    case 6:
//        i = 13;
//        break;
//    case 7:
//        i = 4;
//        break;
//    case 8:
//        i = 8;
//        break;
//    case 9:
//        i = -1;
//        break;
//    case 10:
//        i = 9;
//        break;
//    case 11:
//        i = 12;
//        break;
//    case 12:
//        i = -1;
//        break;
//    case 13:
//        i = 12;
//        break;
//    default:
//        break;
//    }

//    return i;
//}
