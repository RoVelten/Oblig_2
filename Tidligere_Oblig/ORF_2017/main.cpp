#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "editorwindow.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("ORF 2017");
    app.setApplicationVersion("0.1");

#ifndef QT_NO_OPENGL
	EditorWindow editorWindow;
    editorWindow.resize(1280, 720);
    editorWindow.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
