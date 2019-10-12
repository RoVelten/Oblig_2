#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QBasicTimer>

#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <vector>

#include "camera.h"
#include "axesgizmo.h"
#include "shaderprogram.h"


class GameEngine : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GameEngine(QWidget *parent = 0);
    ~GameEngine();

    void init();
    void initMaterials();
    //void initTextures();
    void cleanup();

    bool running() { return mRunning; }
    void quit() { mRunning = false; }

        GameObject* getGameObject(int numberInList);

signals:
    void initHierarchy(std::vector<GameObject*> &mGeometry);

public slots:
    void axisOnOff();
    void wireFrameOnOff();
    void setCameraColor();
    void orthographicOnOff();

protected:
    //This is the "handleEvents" part:
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

    void handleKeys();

    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

private:
    QBasicTimer mTimer;

    Material *mMaterials[4];

    Camera *mCamera;

    QMatrix4x4 viewMatrix;
    QMatrix4x4 projectionMatrix;

    std::vector<GameObject*> mGeometry;

    GameObject *axes;
    GameObject *skybox;
    GameObject *mPlane;
    GameObject *mSosi;
    GameObject *Bezzie;

    QString* fragmentShaderFileName;
    QString* vertexShaderFileName;

    float move = 1;

    bool mRunning;

    bool plane = true;
    bool axisOn = true;
    bool wireFrame = false;
    bool ortho = false;

    int mouseXlast{};
    int mouseYlast{};
    float cameraSpeed = 0.2f;
    float mPathNumber{0};

    //This really! should be made anoter way!
    //Quick hack ahead:
    bool mW = false;
    bool mA = false;
    bool mS = false;
    bool mD = false;
    bool mUp = false;
    bool mDown = false;
    bool mLeft = false;
    bool mRight = false;
    bool mQ = false;
    bool mE = false;

    Vec2 test;

};

#endif // GAMEENGINE_H
