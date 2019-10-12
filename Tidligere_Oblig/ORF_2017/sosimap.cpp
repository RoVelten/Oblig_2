//#include "sosimap.h"
//#include "vec3.h"

//#include <QtDebug>

////Keep in mind that SosiMap has it's own initGeometry, and it's own draw.
////Should these be handled in GameEngine or elsewhere?

//SosiMap::SosiMap(QString path, float scale)
//{
//    initGeometry(path.toStdString());
//    mScale = scale;
//}

//int SosiMap::initGeometry()
//{
//    // Transfer vertex data to VBO 0
//    glGenBuffers(1, &mVertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, numOfVertices*sizeof(Vertex), mVertices, GL_STATIC_DRAW);

//    // Transfer index data to VBO 1
//    glGenBuffers(1, &mIndexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfVertices*sizeof(GLushort), mIndices, GL_STATIC_DRAW);

//    return 0;
//}

//int SosiMap::initGeometry(std::string filePath)
//{
//    const char* path = filePath.c_str();

//    //Open File
//    FILE * file = fopen(path, "r");

//    if(file == nullptr)
//    {
//        qDebug() << "Could not open file at: " << path;
//    }

//    char oneWord[256] = "";
//    int remaining;

//    while(true)
//    {
//        remaining = fscanf(file, "%s", &oneWord);

//        std::vector<Vec3> pointPos;
//        float currentHeight{0};

//        if(strcmp(oneWord, ".KURVE") == 0)
//        {
//            while(true)
//            {
//                remaining = fscanf(file, "%s", &oneWord);

//                if(strcmp(oneWord, "..HØYDE") == 0)
//                {
//                    remaining = fscanf(file, "%s", &oneWord);
//                    currentHeight = std::stof(oneWord);
//                }
//                else if (strcmp(oneWord, "..NØ") == 0)
//                {
//                    while(true)
//                    {
//                        Vec3 tempVec(0.0f, 0.0f, 0.0f); //Vec3 tempVec(0.0f, currentHeight, 0.0f)
//                        remaining = fscanf(file, "%s", &oneWord);

//                        if (strcmp(oneWord, "...KP") == 0)
//                        {
//                            remaining = fscanf(file, "%s", &oneWord);
//                            remaining = fscanf(file, "%s", &oneWord);
//                        }

//                        if ((strcmp(oneWord, ".KURVE") == 0)||(strcmp(oneWord, ".SLUTT") == 0))
//                            break;

//                        if (strcmp(oneWord, "..NØ") == 0)
//                            remaining = fscanf(file, "%s", &oneWord);

//                        tempVec.z = std::stof(oneWord);
//                        remaining = fscanf(file, "%s", &oneWord);
//                        tempVec.x = std::stof(oneWord);
//                        tempVec = tempVec*mScale;
//                        pointPos.push_back(tempVec);
//                       // qDebug() << tempVec.x << " " << tempVec.y << " " << tempVec.z << " " << pointPos.size();
//                    }
//                }

//                if (strcmp(oneWord, ".SLUTT") == 0)
//                    break;
//            }
//        }

//        numOfVertices = pointPos.size();

//        mVertices = new Vertex[numOfVertices];
//        mIndices = new GLushort[numOfVertices];

//        for (int i = 0; i < numOfVertices; i++)
//        {
//            mVertices[i] = {pointPos[i], Vec3(1.0f, 0.0f, 0.0f), Vec2(0.0f, 0.0f)};
//            mIndices[i] = i;
//        }

//        if(remaining == EOF)
//        {
//            break;
//        }
//    }

//    fclose(file);

//    initGeometry();
//}

//void SosiMap::drawGeometry()
//{
//    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
//    mMaterial->useMaterial();

//    //refresh modelMatrix:
//    getMatrix();

//    mMVPMatrix = mProjectionMatrix*mViewMatrix*mModelMatrix;
//    mMaterial->setMVPMatrix(mMVPMatrix);

//    // Offset for position
//    // Positions are the first data, therefor offset is 0
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
//     glDrawElements(GL_LINE_STRIP, numOfVertices, GL_UNSIGNED_SHORT, 0);

//    //Unbind buffers:
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

//    //Unbind shader
//    glUseProgram(0);
//}

//void SosiMap::setRendermode(int mode)
//{
//    if (mode == 1)
//        mWireFrame = true;
//    else if (mode == 0)
//        mWireFrame = false;
//}

//void SosiMap::setMaterial(Material *materialIn)
//{
//    mMaterial = materialIn;
//}
