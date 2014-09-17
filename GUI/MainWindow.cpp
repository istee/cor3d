#include "MainWindow.h"

#include <QListWidgetItem>
#include <QFileDialog>

#include "PostureGLWidget.h"
#include "SkeletonGLWidget.h"
#include "SkeletonEditorTab.h"

using namespace std;
using namespace cor3d;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUi(this);
}

void MainWindow::initialize()
{
    skeleton_editor->initialize();
    posture_editor->initialize();
    scene_editor->initialize();
}

//--------------------------------
// implementation of private slots
//--------------------------------
void MainWindow::on_action_Quit_triggered()
{
    qApp->exit(0);
}

