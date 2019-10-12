QT       += core gui widgets opengl

TARGET = ORF_2017
TEMPLATE = app

#If Qt 5.3 and 5.4 use this
equals(QT_MINOR_VERSION, 3): QMAKE_CXXFLAGS += -std=c++11
equals(QT_MINOR_VERSION, 4): QMAKE_CXXFLAGS += -std=c++11
#If Qt 5.5 use this:
greaterThan(QT_MINOR_VERSION, 4): CONFIG += c++11

SOURCES += main.cpp \
    camera.cpp \
    gameobject.cpp\
    gameengine.cpp \
    axesgizmo.cpp \
    shaderprogram.cpp \
    editorwindow.cpp \
    material.cpp \
    transform.cpp \
    vertex.cpp \
    plane.cpp \
    sosimap.cpp \
    beziercurve.cpp \
    beziercurve.cpp \
    trianglesurface.cpp

HEADERS += \
    transform.h \
    camera.h \
    gameobject.h \
    gameengine.h \
    axesgizmo.h \
    shaderprogram.h \
    editorwindow.h \
    material.h \
    constants.h \
    vec3.h \
    vertex.h \
    vec2.h \
    plane.h \
    sosimap.h \
    beziercurve.h \
    beziercurve.h \
    trianglesurface.h

FORMS += \
    EditorWindow.ui

DISTFILES += \
    Shaders/FlatColorF.glsl \
    Shaders/FlatColorV.glsl \
    Shaders/FlatTextureF.glsl \
    Shaders/FlatTextureV.glsl \
    Shaders/LightF.glsl \
    Shaders/LightV.glsl
