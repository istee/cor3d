#pragma once

#include "IMainWindowTab.h"

#include "ui_SceneEditorTab.h"

class SceneEditorTab: public IMainWindowTab, public Ui::SceneEditorTab
{
    Q_OBJECT
public:
    SceneEditorTab(QWidget* parent = 0);
    void initialize();

    //inherited slots
    void skeleton_list_changed();
    void skeleton_selected();
    void selected_skeleton_nameChanged();
    void selected_skeleton_data_changed();
    void selected_skeleton_joint_list_changed();
    void selected_skeleton_joint_selected_changed();
    void selected_skeleton_joint_nameChanged();
    void selected_skeleton_joint_data_changed();
    void selected_skeleton_joint_selectionChanged();
    void transformations_changed();
    void rendering_options_changed();

private slots:
//    void skeleton_added(const string& name);
//    void skeleton_selected(int);
//    void skeleton_deleted(int id);

//    void skeleton_name_edited(int skeleton_id, const string& name);
//    void skeleton_meshFile_edited(int skeleton_id, const string& file);
//    void skeleton_meshScale_edited(int skeleton_id, const DCoordinate3& model_scale);
//    void skeleton_meshOffset_edited(int skeleton_id, const DCoordinate3& model_offset);

//    void joint_added(int skeleton_id, const string& name, int parent_id);
//    void joint_selected(int skeleton_id, int joint_id);

//    void joint_parent_edited(int skeleton_id, int joint_id, int parent_id);
//    void joint_type_edited(int skeleton_id, int joint_id, Type type);
//    void joint_axis_edited(int skeleton_id, int joint_id, const DCoordinate3& axis);
//    void joint_orientation_edited(int skeleton_id, int joint_id, const DCoordinate3& orientation);
//    void joint_configuration_edited(int skeleton_id, int joint_id, const DCoordinate3& configuration);

//    void rendering_options_edited(RenderingOptions* rendering_options);
};
