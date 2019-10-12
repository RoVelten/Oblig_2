#include <string>
#include <QDebug>
#include "shaderprogram.h"

ShaderProgram::ShaderProgram() : QOpenGLFunctions(), m_shaderProgramObjekt(0)
{
    //qDebug() << "ShaderProgram() - constructor";
}

ShaderProgram::~ShaderProgram()
{
    qDebug() << "~ShaderProgram()";
    int status;
    glGetProgramiv(m_shaderProgramObjekt, GL_DELETE_STATUS, &status);
    glDeleteProgram(m_shaderProgramObjekt);
    qDebug() << " delete status = " << status;
}

GLuint ShaderProgram::shader(GLenum shaderType, const QString& shaderCode)
{
    /// - calls glCreateShader()
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0)
    {
        qDebug() << "glCreateShader() failed.";
        return 0;
    }
    std::string s = shaderCode.toStdString();
    const char* cShaderCode = s.c_str();
    /// - calls glShaderSource()
    glShaderSource(shader, 1, &cShaderCode, 0);
    /// - calls glCompileShader()
    glCompileShader(shader);

    /// - checks compile status
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            char* infoLog = new char[infoLen];
            glGetShaderInfoLog(shader, infoLen, 0, infoLog);
            qDebug() << "compile shader error" << infoLog;
            delete [] infoLog;
        }
        glDeleteShader(shader);
        return 0;
    }
    /// - get shader source from shader and outputs with qDebug()
    char src[2000]; // Økt fra 500
    int bufLen;
    glGetShaderSource(shader, 2000, &bufLen, src);
    //qDebug() << src;
    return shader;
}

void ShaderProgram::initShader(const QString& vertexCode, const QString &fragmentCode)
{
    //qDebug() << "initShader()";

    initializeOpenGLFunctions();

    /// - glCreateProgram()
    m_shaderProgramObjekt = glCreateProgram();
    //qDebug() << "mShaderProgramObjekt" << mShaderProgramObjekt;

    /// - shader() returns a compiled shader with source which is attached to
    ///   shaderProgram by glAttachShader() for both vertexShader and fragmentShader

    GLuint vertexShader = shader(GL_VERTEX_SHADER, vertexCode);
    glAttachShader(m_shaderProgramObjekt, vertexShader);

    GLuint fragmentShader = shader(GL_FRAGMENT_SHADER, fragmentCode);
    glAttachShader(m_shaderProgramObjekt, fragmentShader);

    // if we use glBindAttribLocation, this must happen before the linking.
    // trying to use glGetAttribLocation for now
//    glBindAttribLocation(mShaderProgramObjekt, 0, "aVertexPosition");
//    glBindAttribLocation(mShaderProgramObjekt, 1, "aNormal");
//    glBindAttribLocation(mShaderProgramObjekt, 2, "aTexcoord");


    /// - glLinkProgram()
    glLinkProgram(m_shaderProgramObjekt);

    GLint linked=-1;
    glGetProgramiv(m_shaderProgramObjekt, GL_LINK_STATUS, &linked);

    if (linked==GL_FALSE) //!linked)
    {
        qDebug() << "compile shader error";
        GLint infoLen = 0;
        glGetProgramiv(m_shaderProgramObjekt, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            char* infoLog = new char[infoLen];
            glGetShaderInfoLog(m_shaderProgramObjekt, infoLen, 0, infoLog);
            qDebug() << "compile shader error" << infoLog;
            delete [] infoLog;
        }
        glDeleteProgram(m_shaderProgramObjekt);
        m_shaderProgramObjekt = 0;
    }
    /// - now the shaderprogram is ready for use
}


GLint ShaderProgram::getAttribLocation(const GLchar* name)
{
    GLint i = glGetAttribLocation(m_shaderProgramObjekt, name);
    if(i < 0)
       qDebug() << name << " not found ...";
    //qDebug() << "shaderprogram "  << "attributt" << i << " for " << name;
    glGetProgramiv(m_shaderProgramObjekt, GL_ACTIVE_ATTRIBUTES, &i);
    //qDebug() << "shaderprogram" << "antall attributter = " << i;

    return glGetAttribLocation(m_shaderProgramObjekt, name);
}

GLint ShaderProgram::getUniformLocation(const GLchar* name)
{
    GLint i = glGetUniformLocation(m_shaderProgramObjekt, name);
    if(i < 0)
       qDebug() << name << " not found ...";
    //qDebug() << "shaderprogram" << " uniform" << i << " for " << name;
    glGetProgramiv(m_shaderProgramObjekt, GL_ACTIVE_UNIFORMS, &i);
    //qDebug() << "shaderprogram" << "antall uniforms = " << i;

    return glGetUniformLocation(m_shaderProgramObjekt, name);
}
void ShaderProgram::setUniformMatrix(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    glUniformMatrix4fv(location, count, transpose, value);
}
void ShaderProgram::setUniformVec3(GLint location, float x, float y, float z)
{
    glUniform3f(location, x, y, z);
    /* tested, ok
    float v[3];
    glGetUniformfv(m_shaderProgram, location, v);
    qDebug() << "Uniform vec3 " << v[0] << ", " << v[1] << ", " << v[2];
    */
}

void ShaderProgram::useProgram()
{
    glUseProgram(m_shaderProgramObjekt);
}

void ShaderProgram::deleteProgram()
{
    GLint i;
    glDeleteProgram(m_shaderProgramObjekt);
    glGetProgramiv(m_shaderProgramObjekt, GL_DELETE_STATUS, &i);
    if (i == GL_FALSE)
        qDebug() << "shaderprogram delete status = GL_FALSE";
    else
        qDebug() << "shaderprogram delete status = GL_TRUE";
}
