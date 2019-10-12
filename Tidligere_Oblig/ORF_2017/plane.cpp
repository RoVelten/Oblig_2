//#include "plane.h"
//#include "vertex.h"
//#include <QImage>
//#include "cmath"
//#include "QDebug"

//Plane::Plane(float xPos, float yPos, float zPos, int mSize, float mSpacing, QString name) : GameObject(xPos, yPos, zPos, name)
//{
//    // Initializes map geometry and transfers it to VBOs
//    mapSize = mSize;
//    mapFactor = mSpacing;
//    previousTriangle = Vec3(1, 0, mapSize);
//    initGeometry();
//    mTransform->translate(xPos, yPos, zPos);

//}

//int Plane::initGeometry()
//{
//    //For height maps:
//    //QImage *height = new QImage("Orf::assetFilePath + height.jpg");
//    //    for (int i = 0; i< mapSize*2; i++)
//    //    {
//    //        qDebug() << i << " " << qBlue(height->pixel(i, 0));
//    //    }

//    //Make the array for all the vertecies:
//    Vertex *vertices = new Vertex[mapSize*mapSize];


//    //Double for-loop to make the vertecies by row and coloumn
//    for(int row = 0; row < mapSize; row++)
//    {
//        for(int col = 0; col < mapSize; col++)
//        {
//            vertices[col + (row * mapSize)] = {

//                    //This is what I use when reading height from heightmap:
//                    //              x,                 y (-128 for height +-128),                            z
//                    //Vec3(col*mapFactor, (float(qBlue(height->pixel(col, row)))-128.0f)/heightFactor,  row*mapFactor),


//                    //The height (y-value) here is just an arbertrary formula to get some variation:
//                    Vec3(col*mapFactor, cos(col+row),  row*mapFactor),
//                    Vec3(float(col)/mapSize, float(row)/mapSize,  float(col)/8),  //normal - not real normal calculation...
//                    Vec2(0.0f, 0.0f)} ;        //texture coordinates
//        }
//    }

//    // Calculate how may indicies the map needs:
//    // each row = mapsize * 2
//    // number of rows = mapSize -1
//    // between rows we need 2 extra indicies for empty triangles
//    indexCount = mapSize * 2 * (mapSize-1) + (mapSize-2) * 2;

//    GLushort *indices = new GLushort[indexCount];
//    int indexIndicies = 0;

//    for(int row = 0; row < mapSize; row++)
//    {
//        //make coloumns
//        for(int col = 0; col < (mapSize); col++)
//        {
//            indices[indexIndicies] = row * mapSize + col;
//            indexIndicies++;
//            indices[indexIndicies] = row * mapSize + col + mapSize;
//            //         0, 4, 1, 5, 2, 6, 3, 7,       // 0, 0+size, 1, 1+size, etc.
//            //         7, 4,   //degenerated, empty    // last of previous, first of comming
//            //         4, 8, 5, 9, 6, 10, 7, 11,       // row*size+col, size*2+1, row*size+col, size*2+2, etc.
//            //         11, 8,  //degenerated, empty    // last of previous, first of comming
//            //         8, 12, 9, 13, 10, 14, 11, 15    // size*2, size*3+1, size*2+1, size*3+2, etc.
//            indexIndicies++;
//        }
//        //make empty triangles before next row
//        if (row < (mapSize-2))
//        {
//            indices[indexIndicies] = indices[indexIndicies-1];
//            indexIndicies++;
//            indices[indexIndicies] = (row+1) * mapSize;
//            indexIndicies++;
//        }
//        if (indexIndicies == indexCount )
//            break;

//    }

//    // Transfer vertex data to VBO 0
//    glGenBuffers(1, &mVertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, mapSize*mapSize*sizeof(Vertex), vertices, GL_STATIC_DRAW);

//    // Transfer index data to VBO 1
//    glGenBuffers(1, &mIndexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount*sizeof(GLushort), indices, GL_STATIC_DRAW);



//    delete[] vertices;

//    return 0;
//}

//void Plane::drawGeometry()
//{
//    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
//    mMaterial->useMaterial();

//    //refresh modelMatrix:
//    getMatrix();

//    mMVPMatrix = mProjectionMatrix*mViewMatrix*mModelMatrix;
//    mMaterial->setMVPMatrix(mMVPMatrix);

//    // Offset for position
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

//    // Draw cube geometry using indices from VBO 1
//    if (!mWireFrame)
//        glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_SHORT, 0);
//    else
//        glDrawElements(GL_LINE_STRIP, indexCount, GL_UNSIGNED_SHORT, 0);

//    //Write errors if any:
////    GLenum err = GL_NO_ERROR;
////    while((err = glGetError()) != GL_NO_ERROR)
////    {
////        qDebug() << "glGetError returns " << err;
////    }

//    //Unbind buffers:
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//    //Unbind shader
//    glUseProgram(0);
//}

//void Plane::setRendermode(int mode)
//{
//    if (mode == 1)
//        mWireFrame = true;
//    else if (mode == 0)
//        mWireFrame = false;
//}

//void Plane::setMaterial(Material *materialIn)
//{
//    mMaterial = materialIn;
//}

////Go through this code in detail later.
////Has to do with Barycentric coordinates and testen location on plane.
////Something in the following code makes the project crash.
////Seems to be colorTriangle.

//Vec3 Plane::findTriangle(Vec2 objectPos)
//{

//    //Write errors if any:
//    GLenum err = GL_NO_ERROR;
//    while((err = glGetError()) != GL_NO_ERROR)
//    {
//        qDebug() << "glGetError returns " << err;
//    }
//    // Start at row 1. Set vertices for first triangle. These will always be the same
//    int row = 1;
//    int tempP1 = 1;
//    int tempP2 = 0;
//    int tempP3 = mapSize;

//    for(int triangle = 0; triangle < (mapSize-1)*(mapSize-1)*2; triangle++)
//    {
//        //Calculating barycentric coordinates
//        Vec3 baryCoor = objectPos.barysentricCalculation(vertices[tempP1].get_xz(), vertices[tempP2].get_xz(), vertices[tempP3].get_xz());

//        //Checking if the barycentric coordinates confirm that the object is within the triangle
//        if(baryCoor.x > 0 && baryCoor.x < 1 && baryCoor.y > 0 && baryCoor.y < 1 && baryCoor.z > 0 && baryCoor.z < 1)
//        {
//            //Return a vec3 holding the indices of the 3 vertices making a triangle
//            return Vec3 (tempP1, tempP2, tempP3);
//        }

//        //If the object is not within the triangle, set values for next triangle
//        if (tempP3 == ((row + 1)*mapSize - 1))
//        {
//            tempP1 = row * mapSize + 1;
//            tempP2 = row * mapSize;
//            tempP3 = (row + 1)*mapSize;
//            row++;
//        }
//        else
//        {
//            if (triangle % 2 == 0)
//            {
//                tempP2 += mapSize;
//                tempP3 ++;
//            }
//            else if (triangle % 2 == 1)
//            {
//                tempP1++;
//                tempP2 -= (mapSize-1);
//            }
//        }

//        //If the object is outside the plane
//        if (triangle == (mapSize-1)*(mapSize-1)*2)
//            qDebug() << "Object is not within the plane";
//    }

//}

////Something in this function causes a crash when the program starts.
////Removed the call from GameEngine, so this isn't called, and the plane isn't drawn.
//void Plane::colorTriangle(Vec2 objectPos)
//{
//    Vec3 currentTriangle = findTriangle(objectPos);

//    if (previousTriangle.x < 1)
//    {
//        //If the object first enters the plane, save the color for reseting later, and setting new color of triangle to red
//        previousTriangle = currentTriangle;
//        prevColorP1 = vertices[int(currentTriangle.x)].get_rgb();
//        prevColorP2 = vertices[int(currentTriangle.y)].get_rgb();
//        prevColorP3 = vertices[int(currentTriangle.z)].get_rgb();

//        vertices[int(currentTriangle.x)].set_rgb(1.0f, 0.0f, 0.0f);
//        vertices[int(currentTriangle.y)].set_rgb(1.0f, 0.0f, 0.0f);
//        vertices[int(currentTriangle.z)].set_rgb(1.0f, 0.0f, 0.0f);

//        refreshVertices(); // Send new vertex data to buffer
//    }
//    else if (currentTriangle.x != previousTriangle.x || currentTriangle.y != previousTriangle.y || currentTriangle.z != previousTriangle.z)
//    {
//        //If object is entering new triangle, reset color of old triangle, save color of new triangle, and color new triangle red
//        vertices[int(previousTriangle.x)].set_rgb(prevColorP1.x, prevColorP1.y, prevColorP1.z);
//        vertices[int(previousTriangle.y)].set_rgb(prevColorP2.x, prevColorP2.y, prevColorP2.z);
//        vertices[int(previousTriangle.z)].set_rgb(prevColorP3.x, prevColorP3.y, prevColorP3.z);

//        prevColorP1 = vertices[int(currentTriangle.x)].get_rgb();
//        prevColorP2 = vertices[int(currentTriangle.y)].get_rgb();
//        prevColorP3 = vertices[int(currentTriangle.z)].get_rgb();

//        vertices[int(currentTriangle.x)].set_rgb(1.0f, 0.0f, 0.0f);
//        vertices[int(currentTriangle.y)].set_rgb(1.0f, 0.0f, 0.0f);
//        vertices[int(currentTriangle.z)].set_rgb(1.0f, 0.0f, 0.0f);

//        previousTriangle = currentTriangle;
//        refreshVertices();//Send new vertex data to buffer
//    }
//}

//Vec3 Plane::normalOfCurrentTriangle()
//{
//    Vec3 p1 = vertices[int(previousTriangle.x)].get_xyz();
//    Vec3 p2 = vertices[int(previousTriangle.y)].get_xyz();
//    Vec3 p3 = vertices[int(previousTriangle.z)].get_xyz();

//    Vec3 p1p2 = p2 - p1;
//    Vec3 p1p3 = p3 - p1;

//    Vec3 normal = p1p2 ^ p1p3;
//    return (normal.normalized());
//}

//float Plane::angleOfCurrentTriangle()
//{
//    Vec3 normal = normalOfCurrentTriangle();
//    return acos(normal.y);
//}

//Vec3 Plane::currTriangleHighY()
//{
//    Vec3 y = vertices[int(previousTriangle.x)].get_xyz();

//    if (vertices[int(previousTriangle.y)].get_xyz().y > y.y)
//        y =vertices[int(previousTriangle.y)].get_xyz();

//    if (vertices[int(previousTriangle.z)].get_xyz().y > y.y)
//        y =vertices[int(previousTriangle.z)].get_xyz();

//    return y;
//}

//Vec3 Plane::currTriangleLowY()
//{
//    Vec3 y = vertices[int(previousTriangle.x)].get_xyz();

//    if (vertices[int(previousTriangle.y)].get_xyz().y < y.y)
//        y =vertices[int(previousTriangle.y)].get_xyz();

//    if (vertices[int(previousTriangle.z)].get_xyz().y < y.y)
//        y =vertices[int(previousTriangle.z)].get_xyz();

//    return y;
//}

//void Plane::refreshVertices()
//{
//    glGenBuffers(1, &mVertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, mapSize*mapSize*sizeof(Vertex), vertices, GL_STATIC_DRAW);
//}

