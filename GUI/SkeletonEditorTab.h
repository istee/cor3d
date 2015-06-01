#pragma once

#include "IMainWindowTab.h"

#include "ui_SkeletonEditorTab.h"

#include "SkeletonGLWidget.h"

using namespace std;

class SkeletonEditorTab: public IMainWindowTab, public Ui::SkeletonEditorTab
{
    Q_OBJECT
public:
    SkeletonEditorTab(QWidget* parent = 0);
    void initialize();

public slots:

    void handle_model_skeleton_list_changed();
    void handle_model_skeleton_selection_changed();
    void handle_model_skeleton_name_changed();
    void handle_model_skeleton_model_data_changed(const string& skeletonName);
    void handle_model_skeleton_data_changed();

    void handle_model_joint_list_changed();
    void handle_model_joint_added(const string& name);
    void handle_model_joint_deleted(const string& name);
    void handle_model_joint_renamed(const string& oldName, const string& newName);
    void handle_model_joint_selection_changed(const string& name);
    void handle_model_joint_data_changed();
    void handle_model_rendering_options_changed();

private slots:
//    void skeleton_added(const string& name);
//    void skeleton_selected(int);
//    void skeleton_deleted();

//    void skeleton_name_edited(const string& name);
//    void skeleton_model_file_edited(const string& file);
//    void skeleton_model_scale_edited(const DCoordinate3& model_scale);
//    void skeleton_model_offset_edited(const DCoordinate3& model_offset);

//    void joint_added(const string& name, int parent_id);
//    void joint_selected(int joint_id);

//    void joint_parent_edited(int joint_id, int parent_id);
//    void joint_type_edited(int joint_id, Type type);
//    void joint_axis_edited(int joint_id, const DCoordinate3& axis);
//    void joint_orientation_edited(int joint_id, const DCoordinate3& orientation);
//    void joint_configuration_edited(int joint_id, const DCoordinate3& configuration);

//    void rendering_options_edited(RenderingOptions* rendering_options);
};
