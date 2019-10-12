#include "mesh.h"

Mesh::Mesh(GameObject *owner, GLenum mType, int LODlevels) : Component(owner, "Mesh")
{
    meshType = mType;
    LODlvl = LODlevels;
    activeLOD = 0;
    for(int i = 0; i < 3; i++)
    {
        mVertexBuffer[i] = 0;
        mIndexBuffer[i] = 0;
    }
}

void Mesh::setRendermode(int mode)
{
    if (mode == 1)
        mWireFrame = true;
    else if (mode == 0)
        mWireFrame = false;
}

void Mesh::setMaterial(Material *materialIn)
{
    mMaterial = materialIn;
}

unsigned int Mesh::drawGeometry()
{
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer[activeLOD]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer[activeLOD]);
    mMaterial->useMaterial();

    //refresh modelMatrix:
    getMatrix();

    mMVPMatrix = mProjectionMatrix*mViewMatrix*mModelMatrix;
    mMaterial->setMVPMatrix(mMVPMatrix);

    // Offset for position
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
    //glVertexAttribPointer(static_cast<GLuint>(mMaterial->getTextureAttribute()), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offset));

    // Draw cube geometry using indices from VBO 1
    if (!mWireFrame)
        glDrawElements(meshType, numOfIndices[activeLOD], GL_UNSIGNED_SHORT, 0);
    else
        glDrawElements(GL_LINE_STRIP, numOfIndices[activeLOD], GL_UNSIGNED_SHORT, 0);

    //Unbind buffers:
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Unbind shader
    glUseProgram(0);

    return numOfVertices[activeLOD];
}

void Mesh::setViewMatrix(QMatrix4x4 viewMatrix)
{
    mViewMatrix = viewMatrix;
}

void Mesh::setprojectionMatrix(QMatrix4x4 projectionMatrix)
{
    mProjectionMatrix = projectionMatrix;
}

QMatrix4x4 Mesh::getMatrix()
{
    mModelMatrix.setToIdentity();
    mModelMatrix.translate(mOwner->mTransform->getPosition().x, mOwner->mTransform->getPosition().y, mOwner->mTransform->getPosition().z );
    mModelMatrix.rotate(mOwner->mTransform->getRotation().x, 1.0, 0.0, 0.0);
    mModelMatrix.rotate(mOwner->mTransform->getRotation().y, 0.0, 1.0, 0.0);
    mModelMatrix.rotate(mOwner->mTransform->getRotation().z, 0.0, 0.0, 1.0);
    mModelMatrix.scale(mOwner->mTransform->getScale().x, mOwner->mTransform->getScale().y, mOwner->mTransform->getScale().z);
    //mModelMatrix.translate(mTransform.mPosition);

    return mModelMatrix;
}

void Mesh::distanceFromCameraLOD(Vec3 camPos)
{
    Vec3 distance = camPos - mOwner->mTransform->getPosition();
    if (distance.length() <= 20)
        activeLOD = 0;
    if (distance.length() > 20 && LODlvl >= 1)
        activeLOD = 1;
    if (distance.length() > 30 && LODlvl >= 2)
        activeLOD = 2;
}
