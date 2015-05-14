#include "SkeletonEditorTab.h"

#include "Cor3dApplication.h"
#include "GUI/SideWidgetComponents/BaseSideWidget.h"
#include "GUI/SideWidgetComponents/SideWidgetGroupBox.h"

SkeletonEditorTab::SkeletonEditorTab(QWidget *parent): IMainWindowTab(parent)
{
    setupUi(this);

    glwidget->updateGL();

    //transformations_widget->setGLWidget(glwidget);

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_list_changed()), this, SLOT(handle_model_skeleton_list_changed()));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_selection_changed()), this, SLOT(handle_model_skeleton_selection_changed()));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_name_changed()), this, SLOT(handle_model_skeleton_name_changed()));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_data_changed()), this, SLOT(handle_model_skeleton_data_changed()));
    connect(cor3dApp->cor3d, SIGNAL(model_rendering_options_changed()), this, SLOT(handle_model_rendering_options_changed()));

    //connect(glwidget, SIGNAL(transformations_changed()), this, SLOT(transformations_changed()));


    connect(add_new_skeleton, SIGNAL(view_skeleton_added(string)), cor3dApp->cor3d, SLOT(handle_view_skeleton_added(string)));
    connect(add_new_skeleton, SIGNAL(view_skeleton_imported(string)), cor3dApp->cor3d, SLOT(handle_view_skeleton_imported(string)));
    connect(skeleton_list, SIGNAL(view_skeleton_selected(int)), cor3dApp->cor3d, SLOT(handle_view_skeleton_selected(int)));
    connect(skeleton_list, SIGNAL(view_skeleton_deleted()), cor3dApp->cor3d, SLOT(handle_view_skeleton_deleted()));
    connect(skeleton_list, SIGNAL(view_skeleton_exported(string)), cor3dApp->cor3d, SLOT(handle_view_skeleton_exported(string)));
    connect(edit_skeleton, SIGNAL(view_skeleton_name_changed(string)), cor3dApp->cor3d, SLOT(handle_view_skeleton_name_changed(string)));
    connect(edit_skeleton, SIGNAL(view_skeleton_model_changed(string)), cor3dApp->cor3d, SLOT(handle_view_skeleton_model_changed(string)));
    connect(edit_skeleton, SIGNAL(view_skeleton_model_scale_changed(DCoordinate3)), cor3dApp->cor3d, SLOT(handle_view_skeleton_model_scale_changed(DCoordinate3)));
    connect(edit_skeleton, SIGNAL(view_skeleton_model_offset_changed(DCoordinate3)), cor3dApp->cor3d, SLOT(handle_view_skeleton_model_offset_changed(DCoordinate3)));

    /*
    connect(rendering_options_widget, SIGNAL(view_skeleton_render_toggled(bool)), cor3dApp->cor3d, SLOT(handle_view_skeleton_render_toggled(bool)));
    connect(rendering_options_widget, SIGNAL(view_skeleton_material_changed(int)), cor3dApp->cor3d, SLOT(handle_view_skeleton_material_changed(int)));
    connect(rendering_options_widget, SIGNAL(view_joint_render_toggled(bool)), cor3dApp->cor3d, SLOT(handle_view_joint_render_toggled(bool)));
    connect(rendering_options_widget, SIGNAL(view_joint_model_file_changed(string)), cor3dApp->cor3d, SLOT(handle_view_joint_model_file_changed(const string&)));
    connect(rendering_options_widget, SIGNAL(view_joint_material_changed(int)), cor3dApp->cor3d, SLOT(handle_view_joint_material_changed(int)));
    connect(rendering_options_widget, SIGNAL(view_selected_joint_material_changed(int)), cor3dApp->cor3d, SLOT(handle_view_selected_joint_material_changed(int)));
    connect(rendering_options_widget, SIGNAL(view_link_render_toggled(bool)), cor3dApp->cor3d, SLOT(handle_view_link_render_toggled(bool)));
    connect(rendering_options_widget, SIGNAL(view_link_model_file_changed(string)), cor3dApp->cor3d, SLOT(handle_view_link_model_file_changed(const string&)));
    connect(rendering_options_widget, SIGNAL(view_link_material_changed(int)), cor3dApp->cor3d, SLOT(handle_view_link_material_changed(int)));
    */

    //connect(rendering_options_widget, SIGNAL(view_rendering_options_changed(RenderingOptions*)), cor3dApp->cor3d, SLOT(rendering_options_edited(RenderingOptions*)));

    //connect(transformations_widget, SIGNAL(view_rotation_changed(DCoordinate3)), glwidget, SLOT(handle_view_rotation_changed(DCoordinate3)));
    //connect(transformations_widget, SIGNAL(view_translation_changed(DCoordinate3)), glwidget, SLOT(handle_view_translation_changed(DCoordinate3)));
    //connect(transformations_widget, SIGNAL(view_zoom_factor_changed(double)), glwidget, SLOT(handle_view_zoom_factor_changed(double)));

}

void SkeletonEditorTab::initialize()
{
    QList<SideWidgetGroupBox*> groupbox_list = this->scrollAreaWidgetContents->findChildren<SideWidgetGroupBox*>();
    for (QList<SideWidgetGroupBox*>::iterator it = groupbox_list.begin(); it != groupbox_list.end(); it++)
    {
        (*it)->toggled();
    }

    QList<BaseSideWidget*> sidewidget_list = this->scrollAreaWidgetContents->findChildren<BaseSideWidget*>();
    for (QList<BaseSideWidget*>::iterator it = sidewidget_list.begin(); it != sidewidget_list.end(); it++)
    {
        (*it)->update_content();

    }
}

void SkeletonEditorTab::handle_model_skeleton_list_changed()
{
    skeleton_list->update_content();
    add_new_skeleton->update_content();
}

void SkeletonEditorTab::handle_model_skeleton_selection_changed()
{
    skeleton_list->update_content();
    edit_skeleton->update_content();
    add_new_joint->update_content();
    edit_joint->update_content();
    glwidget->updateGL();

    Skeleton* skeleton = cor3dApp->cor3d->get_skeleton();
    connect(skeleton, SIGNAL(model_joint_list_changed()), this, SLOT(handle_model_joint_list_changed()));
    connect(skeleton, SIGNAL(model_joint_selection_changed()), this, SLOT(handle_model_joint_selection_changed()));
    connect(skeleton, SIGNAL(model_joint_data_changed()), this, SLOT(handle_model_joint_data_changed()));

    connect(add_new_joint, SIGNAL(view_joint_added(string,int)), skeleton, SLOT(handle_view_joint_added(string,int)));
    connect(edit_joint, SIGNAL(view_joint_selection_changed(int)), skeleton, SLOT(handle_view_joint_selection_changed(int)));
    connect(edit_joint, SIGNAL(view_joint_parent_changed(int)), skeleton, SLOT(handle_view_joint_parent_changed(int)));
    connect(edit_joint, SIGNAL(view_joint_type_changed(int)), skeleton, SLOT(handle_view_joint_type_changed(int)));
    connect(edit_joint, SIGNAL(view_joint_orientation_changed(DCoordinate3)), skeleton, SLOT(handle_view_joint_orientation_changed(DCoordinate3)));
    connect(edit_joint, SIGNAL(view_joint_axis_changed(DCoordinate3)), skeleton, SLOT(handle_view_joint_axis_changed(DCoordinate3)));
    connect(edit_joint, SIGNAL(view_joint_configuration_changed(DCoordinate3)), skeleton, SLOT(handle_view_joint_configuration_changed(DCoordinate3)));
    connect(glwidget, SIGNAL(view_joint_selection_changed(int)), skeleton, SLOT(handle_view_joint_selection_changed(int)));
    connect(glwidget, SIGNAL(view_joint_absolute_position_changed(DCoordinate3)), skeleton, SLOT(handle_view_joint_absolute_position_changed(DCoordinate3)));
}

void SkeletonEditorTab::handle_model_skeleton_name_changed()
{
    skeleton_list->update_content();
    add_new_skeleton->update_content();
    edit_skeleton->update_content();
}

void SkeletonEditorTab::handle_model_skeleton_data_changed()
{
    edit_skeleton->update_content();
    glwidget->updateGL();
}

void SkeletonEditorTab::handle_model_joint_list_changed()
{
    add_new_joint->update_content();
    edit_joint->update_content();
    glwidget->updateGL();
}

void SkeletonEditorTab::handle_model_joint_selection_changed()
{
    add_new_joint->update_content();
    edit_joint->update_content();
    glwidget->updateGL();
}

void SkeletonEditorTab::handle_model_joint_data_changed()
{
    edit_joint->update_content();
    glwidget->updateGL();
}

//void SkeletonEditorTab::transformations_changed()
//{
//    transformations_widget->update_content();
//    glwidget->updateGL();
//}

void SkeletonEditorTab::handle_model_rendering_options_changed()
{
    //rendering_options_widget->update_content();
    //glwidget->updateGL();
}