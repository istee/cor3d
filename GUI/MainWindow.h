#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "SideWidget.h"
#include "GLWidget.h"
#include "SceneView.h"
#include "Render.h"
#include "EditJoint.h"
#include "SkeletonList.h"
#include "AddNewSkeleton.h"
#include "EditSkeleton.h"
#include "SkeletonSideWidget.h"

#include "Model/ISkeleton.h"
#include <QScrollArea>

#include "Model/Skeleton.h"

using namespace cor3d;

class MainWindow: public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

private:
    SideWidget  *_side_widget;      // pointer to our side widget
    SceneView   *_scene_view;        // pointer to our rendering OpenGL widget
    GLWidget    *_posture_gl_widget;        // pointer to our rendering OpenGL widget
    GLWidget    *_skeleton_gl_widget;        // pointer to our rendering OpenGL widget
    Render      *_render;

    SkeletonList    *_skeleton_list_skeleton;
    AddNewSkeleton  *_add_new_skeleton;
    EditSkeleton    *_edit_skeleton;
    Render          *_render_skeleton;
    EditJoint       *_edit_joint_skeleton;

    GLWidget    *_section_x;
    GLWidget    *_section_y;
    GLWidget    *_section_z;

    QScrollArea *_scroll_area;      // provides a scrolling view onto our side widget

    SkeletonSideWidget *_skeleton_side_widget;

    //data
    //std::vector<cagd::ISkeleton>   skeletons;



public:
    // special and default constructor
    MainWindow(QWidget *parent = 0);

private slots:
    // private event handling methods/slots
    void on_action_Quit_triggered();
    void skeleton_added(const string& name);
    void skeleton_selected(const string& name);
    void skeleton_deleted();
    void skeleton_edited(const Skeleton& skeleton);
    void joint_added(const string& name, int parent_id);
    void joint_selected(int id);
    void joint_edited(const Joint& joint);
//    void skeleton_name_edit();
//    void skeleton_model_edit();
//    void skeleton_model_x_edit(double value);
//    void skeleton_model_y_edit(double value);
//    void skeleton_model_z_edit(double value);

    void menu_window_update_content();
};
