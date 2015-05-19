#include "SceneEditorTab.h"

#include "Cor3dApplication.h"
#include "GUI/SideWidgetComponents/BaseSideWidget.h"
#include "GUI/SideWidgetComponents/SideWidgetGroupBox.h"

SceneEditorTab::SceneEditorTab(QWidget *parent): IMainWindowTab(parent)
{
    setupUi(this);

    play_button->setIcon(QIcon("Resources/pause.png"));
    play_button->setIconSize(QSize(50, 50));
    horizontalSlider->setMaximum(0);
}

void SceneEditorTab::initialize()
{
    QList<SideWidgetGroupBox*> groupbox_list = this->scrollAreaWidgetContents->findChildren<SideWidgetGroupBox*>();
    for (QList<SideWidgetGroupBox*>::iterator it = groupbox_list.begin(); it != groupbox_list.end(); it++)
    {
        (*it)->toggled();
    }

    QList<BaseSideWidget*> sidewidget_list = this->scrollAreaWidgetContents->findChildren<BaseSideWidget*>();
    for (QList<BaseSideWidget*>::iterator it = sidewidget_list.begin(); it != sidewidget_list.end(); it++)
    {
        //(*it)->update_content();

    }
}

// inherited slots - accessed by the model

void SceneEditorTab::skeleton_list_changed()
{
//    skeleton_list->update_content();
//    add_new_skeleton->update_content();
}

void SceneEditorTab::skeleton_selected()
{
//    skeleton_list->update_content();
//    edit_skeleton->update_content();
//    add_new_joint->update_content();
//    edit_joint->update_content();
//    glwidget->updateGL();
}

void SceneEditorTab::selected_skeleton_name_changed()
{
//    skeleton_list->update_content();
//    add_new_skeleton->update_content();
//    edit_skeleton->update_content();
}

void SceneEditorTab::selected_skeleton_data_changed()
{
//    edit_skeleton->update_content();
//    glwidget->updateGL();
}

void SceneEditorTab::selected_skeleton_joint_list_changed()
{
//    add_new_joint->update_content();
//    edit_joint->update_content();
//    glwidget->updateGL();
}

void SceneEditorTab::selected_skeleton_joint_selection_changed()
{
//    edit_joint->update_content();
//    glwidget->updateGL();
}

void SceneEditorTab::selected_skeleton_joint_name_changed()
{

}

void SceneEditorTab::selected_skeleton_joint_data_changed()
{
//    edit_joint->update_content();
//    glwidget->updateGL();
}

void SceneEditorTab::transformations_changed()
{
//    transformations_widget->update_content();
//    glwidget->updateGL();
}

void SceneEditorTab::rendering_options_changed()
{
    /*rendering_options_widget->update_content();
    glwidget->updateGL()*/;
}

// accessed by the view

//void SkeletonEditorTab::skeleton_added(const string &name)
//{
//    cor3dApp->cor3d->create_skeleton(name);
//}

//void SkeletonEditorTab::skeleton_selected(int id)
//{
//    cor3dApp->cor3d->select_skeleton(id);
//}

//void SkeletonEditorTab::skeleton_deleted(int id)
//{
//    cor3dApp->cor3d->remove_skeleton(id);
//}

//void SkeletonEditorTab::skeleton_name_edited(int skeleton_id, const string& name)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->set_name(name);
//}

//void SkeletonEditorTab::skeleton_model_file_edited(int skeleton_id, const string& file)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->set_model_file(file);
//}

//void SkeletonEditorTab::skeleton_model_scale_edited(int skeleton_id, const DCoordinate3& model_scale)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->set_model_scale(model_scale);
//}

//void SkeletonEditorTab::skeleton_model_offset_edited(int skeleton_id, const DCoordinate3& model_offset)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->set_model_offset(model_offset);
//}

//void  SkeletonEditorTab::joint_added(int skeleton_id, const string& name, int parent_id)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->add_joint(name, parent_id);
//}

//void SkeletonEditorTab::joint_selected(int skeleton_id, int joint_id)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->select_joint(joint_id);
//}

//void SkeletonEditorTab::selected_skeleton_joint_name_changed() { }

//void SkeletonEditorTab::joint_parent_edited(int skeleton_id, int joint_id, int parent_id)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->set_joint_parent(joint_id, parent_id);
//}

//void SkeletonEditorTab::joint_type_edited(int skeleton_id, int joint_id, Type type)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->set_joint_type(joint_id, type);
//}

//void SkeletonEditorTab::joint_axis_edited(int skeleton_id, int joint_id, const DCoordinate3& axis)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->set_joint_axis(joint_id, axis);
//}

//void SkeletonEditorTab::joint_orientation_edited(int skeleton_id, int joint_id, const DCoordinate3& orientation)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->set_joint_orientation(joint_id, orientation);
//}

//void SkeletonEditorTab::joint_configuration_edited(int skeleton_id, int joint_id, const DCoordinate3& configuration)
//{
//    cor3dApp->cor3d->get_skeleton(skeleton_id)->set_joint_configuration_value(joint_id, configuration);
//}

//void SkeletonEditorTab::rendering_options_edited(RenderingOptions* rendering_options)
//{
//    cor3dApp->cor3d->set_rendering_options(rendering_options);
//}

