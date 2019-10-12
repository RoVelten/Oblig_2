#include "editorwindow.h"
#include "ui_EditorWindow.h"
#include "gameobject.h"
#include "gameengine.h"

#include <QFileDialog>

EditorWindow::EditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);
    connect(ui->RenderWindow, SIGNAL(initHierarchy(std::vector<GameObject*>&)), this, SLOT(hierarchyInit(std::vector<GameObject*>&)));
}

EditorWindow::~EditorWindow()
{
    //ui->RenderWindow->cleanup();
    delete ui;
}

void EditorWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void EditorWindow::on_actionLoad_Mesh_triggered()
{
    qDebug() << "Open Mesh says EditorWindow!";
}

void EditorWindow::on_ColorButton_released()
{
    qDebug() << "Test pressed";
    ui->RenderWindow->setCameraColor();
}

void EditorWindow::hierarchyInit(std::vector<GameObject*> &mGeometry)
{
    foreach (auto &tempGameObject, mGeometry) {
        ui->HierarchyList->addItem(tempGameObject->getName());
    }
}


void EditorWindow::on_HierarchyList_itemClicked(QListWidgetItem *item)
{
    if (selectedGameObject)
        selectedGameObject->mSelectedInEditor = false;

    selectedGameObject = ui->RenderWindow->getGameObject(ui->HierarchyList->row(item));
    //Position
}
