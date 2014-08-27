#include "MainWindow.h"

#include <QListWidgetItem>
<<<<<<< HEAD
#include <QFileDialog>
=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa

#include "SceneView.h"
#include "PostureGLWidget.h"
#include "SkeletonGLWidget.h"
#include "Render.h"
#include "EditJoint.h"

<<<<<<< HEAD
#include "Cor3dApplication.h"
=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
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
<<<<<<< HEAD
    connect(_skeleton_side_widget->add_new_skeleton, SIGNAL(skeleton_added(const string&)), this, SLOT(skeleton_added(const string&)));
    connect(_skeleton_side_widget->skeleton_list, SIGNAL(skeleton_selected(const string&)), this, SLOT(skeleton_selected(const string&)));
    connect(_skeleton_side_widget->skeleton_list, SIGNAL(skeleton_deleted()), this, SLOT(skeleton_deleted()));
    connect(_skeleton_side_widget->edit_skeleton, SIGNAL(skeleton_edited(const Skeleton&)), this, SLOT(skeleton_edited(const Skeleton&)));
    connect(_skeleton_side_widget->add_new_joint, SIGNAL(joint_added(const string&, int)), this, SLOT(joint_added(const string&, int)));
    connect(_skeleton_side_widget->edit_joint, SIGNAL(joint_selected(int)), this, SLOT(joint_selected(int)));
    connect(_skeleton_side_widget->edit_joint, SIGNAL(joint_edited(const Joint&)), this, SLOT(joint_edited(const Joint&)));

    //connect(_skeleton_side_widget->skeleton_list->skeleton_listview, SIGNAL(clicked(QModelIndex)), this, SLOT(skeleton_selection_changed_handle(QModelIndex)));
    //connect(_skeleton_side_widget->edit_skeleton->name_lineEdit, SIGNAL(editingFinished()), this, SLOT(skeleton_name_edit()));
    //connect(_skeleton_side_widget->edit_skeleton->model_button, SIGNAL(clicked()), this, SLOT(skeleton_model_edit()));
    //connect(_skeleton_side_widget->edit_skeleton->model_x_doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(skeleton_model_x_edit(double)));
    //connect(_skeleton_side_widget->edit_skeleton->model_y_doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(skeleton_model_y_edit(double)));
    //connect(_skeleton_side_widget->edit_skeleton->model_z_doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(skeleton_model_z_edit(double)));


    menu_window_update_content();
    _skeleton_side_widget->skeleton_list->update_content();
    _skeleton_side_widget->add_new_skeleton->update_content();
    _skeleton_side_widget->edit_skeleton->update_content();
    _skeleton_side_widget->add_new_joint->update_content();
    _skeleton_side_widget->edit_joint->update_content();

=======
    connect(_skeleton_side_widget->add_new_skeleton->add_new_skeleton_button, SIGNAL(released()), this, SLOT(add_new_skeleton_handle()));
    connect(_skeleton_side_widget->skeleton_list->skeleton_listview, SIGNAL(clicked(QModelIndex)), this, SLOT(skeleton_selection_changed_handle(QModelIndex)));
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
}

//--------------------------------
// implementation of private slots
//--------------------------------
void MainWindow::on_action_Quit_triggered()
{
    qApp->exit(0);
}

<<<<<<< HEAD
void MainWindow::skeleton_added(const string& name)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    cor3dApp->cor3d.create_skeleton(name);

    _skeleton_side_widget->skeleton_list->update_content();
    _skeleton_side_widget->add_new_skeleton->update_content();
}

void MainWindow::skeleton_selected(const string& name)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    int id = cor3dApp->cor3d.get_skeleton_id_by_name(name);
    cor3dApp->cor3d.select_skeleton(id);

    _skeleton_side_widget->skeleton_list->update_content();
    _skeleton_side_widget->edit_skeleton->update_content();
    _skeleton_side_widget->add_new_joint->update_content();
    _skeleton_side_widget->edit_joint->update_content();
    _skeleton_gl_widget->updateGL();
}

void MainWindow::skeleton_deleted()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    if (cor3dApp->cor3d.is_skeleton_selected())
    {
        cor3dApp->cor3d.remove_selected_skeleton();

        _skeleton_side_widget->skeleton_list->update_content();
        _skeleton_side_widget->add_new_skeleton->update_content();
        _skeleton_gl_widget->updateGL();
    }
}

void MainWindow::skeleton_edited(const Skeleton& skeleton)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    cor3dApp->cor3d.set_skeleton(skeleton);

    _skeleton_side_widget->skeleton_list->update_content();
    _skeleton_side_widget->add_new_skeleton->update_content();
    _skeleton_side_widget->edit_skeleton->update_content();
    _skeleton_gl_widget->updateGL();
}

void MainWindow::joint_added(const string& name, int joint_id)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton skeleton = cor3dApp->cor3d.get_selected_skeleton();
    skeleton.add_joint(name, joint_id);
    cor3dApp->cor3d.set_skeleton(skeleton);

    _skeleton_side_widget->add_new_joint->update_content();
    _skeleton_side_widget->edit_joint->update_content();
}

void MainWindow::joint_selected(int id)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton skeleton = cor3dApp->cor3d.get_selected_skeleton();
    skeleton.select_joint(id);
    cor3dApp->cor3d.set_skeleton(skeleton);

    _skeleton_side_widget->add_new_joint->update_content();
    _skeleton_side_widget->edit_joint->update_content();
}

void MainWindow::joint_edited(const Joint& joint)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton skeleton = cor3dApp->cor3d.get_selected_skeleton();
    skeleton.set_joint(joint);
    cor3dApp->cor3d.set_skeleton(skeleton);

    _skeleton_side_widget->add_new_joint->update_content();
    _skeleton_side_widget->edit_joint->update_content();
}

//void MainWindow::skeleton_name_edit()
//{
////    string name = _skeleton_side_widget->edit_skeleton->name_lineEdit->text().toStdString();
////    int selected = Cor3d::getInstance().get_selected_skeleton();
////    if (Cor3d::getInstance().set_skeleton_name(selected, name))
////    {
////        _skeleton_side_widget->skeleton_list->update_list();
////    }
//}

//void MainWindow::skeleton_model_edit()
//{
////    string file_name = QFileDialog::getOpenFileName(this,tr("Open OFF model file"), "", tr("OFF Files (*.off)")).toStdString();
////    int selected = Cor3d::getInstance().get_selected_skeleton();
////    Cor3d::getInstance().set_skeleton_model_file(selected, file_name);
////    _skeleton_side_widget->edit_skeleton->update();
//}

//void MainWindow::skeleton_model_x_edit(double value)
//{
////    int selected = Cor3d::getInstance().get_selected_skeleton();
////    Cor3d::getInstance().set_skeleton_model_x(selected, value);
//}

//void MainWindow::skeleton_model_y_edit(double value)
//{
////    int selected = Cor3d::getInstance().get_selected_skeleton();
////    Cor3d::getInstance().set_skeleton_model_y(selected, value);
//}

//void MainWindow::skeleton_model_z_edit(double value)
//{
////    int selected = Cor3d::getInstance().get_selected_skeleton();
////    Cor3d::getInstance().set_skeleton_model_z(selected, value);
//}

void MainWindow::menu_window_update_content()
{
    menu_Window->clear();
    QList<QObject*> widgets = _skeleton_side_widget->scrollAreaLayout->children();
    for (QList<QObject*>::iterator it = widgets.begin(); it != widgets.end(); it++)
    {
        QWidget const *qWidget = qobject_cast<QWidget*>(*it);
        if (qWidget) {
            QAction *qAction = new QAction(qWidget->windowTitle(), menu_Window);
            qAction->setCheckable(true);
            qAction->setChecked(!qWidget->isHidden());
            connect(qAction, SIGNAL(toggled(bool)), qWidget, SLOT(setVisible(bool)));
            menu_Window->addAction(qAction);
        }
    }
=======
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
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
}
