#include "MainWindow.h"

#include <QListWidgetItem>

#include "SceneView.h"
#include "PostureGLWidget.h"
#include "SkeletonGLWidget.h"
#include "Render.h"
#include "EditJoint.h"

#include "Model/Cor3d.h"

using namespace std;
using namespace cor3d;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUi(this);

/*

  the structure of the main window's central widget

 *------------------------------------------------------*
 |                    central widget                    |
 |                                                      |
 |  *--*---------------------------*-----------------*  |
 |  |  |     rendering context     |   scroll area   |  |
 |  |  |       OpenGL widget       | *-------------* |  |
 |  |  |                           | | side widget | |  |
 |  |  |                           | |             | |  |
 |  |  |                           | |             | |  |
 |  |  |                           | *-------------* |  |
 |  *--*---------------------------*-----------------*  |
 |                                                      |
 *------------------------------------------------------*

 */
    //_scroll_area = new QScrollArea(skeleton_editor);

//    _skeleton_list_skeleton = new SkeletonList(_scroll_area);
//    _add_new_skeleton = new AddNewSkeleton(_scroll_area);
//    _edit_skeleton = new EditSkeleton(_scroll_area);
//    _render_skeleton = new Render(_scroll_area);
//    _edit_joint_skeleton = new EditJoint(_scroll_area);

    //_scroll_area->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //_scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    _skeleton_side_widget = new SkeletonSideWidget(this);

    //QVBoxLayout *_scroll_area_layout = new QVBoxLayout();
//    _scroll_area_layout->addWidget(_skeleton_list_skeleton);
//    _scroll_area_layout->addWidget(_add_new_skeleton);
//    _scroll_area_layout->addWidget(_edit_skeleton);
//    _scroll_area_layout->addWidget(_render_skeleton);
//    _scroll_area_layout->addWidget(_edit_joint_skeleton);
    //_scroll_area_layout->addWidget(_skeleton_side_widget);
    //_scroll_area->setLayout(_scroll_area_layout);

    _skeleton_gl_widget = new SkeletonGLWidget(skeleton_editor);
    //skeleton_editor->setLayout(new QHBoxLayout());
    skeleton_editor->layout()->addWidget(_skeleton_gl_widget);
    skeleton_editor->layout()->addWidget(_skeleton_side_widget);

    //Skeleton Editor: connecting signals and slots
    connect(_skeleton_side_widget->add_new_skeleton->add_new_skeleton_button, SIGNAL(released()), this, SLOT(add_new_skeleton_handle()));
    connect(_skeleton_side_widget->skeleton_list->skeleton_listview, SIGNAL(clicked(QModelIndex)), this, SLOT(skeleton_selection_changed_handle(QModelIndex)));
}

//--------------------------------
// implementation of private slots
//--------------------------------
void MainWindow::on_action_Quit_triggered()
{
    qApp->exit(0);
}

void MainWindow::add_new_skeleton_handle()
{
    string name = _skeleton_side_widget->add_new_skeleton->name_input->displayText().toStdString();
    Cor3d::getInstance().create_skeleton(name);
    _skeleton_side_widget->skeleton_list->update_list();
    _skeleton_side_widget->add_new_skeleton->name_input->clear();
}

void MainWindow::skeleton_selection_changed_handle(QModelIndex qmind)
{
    string name = qmind.data().toString().toStdString();
    int id = Cor3d::getInstance().get_skeleton_id_by_name(name);
    Cor3d::getInstance().select_skeleton(id);
    _skeleton_side_widget->edit_skeleton->update();
}
