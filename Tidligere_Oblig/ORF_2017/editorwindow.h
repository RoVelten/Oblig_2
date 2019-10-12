#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <gameobject.h>

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = 0);
    ~EditorWindow();

    void setColor();

private slots:

    void on_actionQuit_triggered();

    void on_actionLoad_Mesh_triggered();

    void on_ColorButton_released();

    void on_HierarchyList_itemClicked(QListWidgetItem *item);

public slots:
    void hierarchyInit(std::vector<class GameObject*> &mGeometry);

private:
    GameObject* selectedGameObject{nullptr};
    Ui::EditorWindow *ui;

};

#endif // EDITORWINDOW_H
