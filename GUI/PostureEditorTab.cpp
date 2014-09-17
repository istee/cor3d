#include "PostureEditorTab.h"

#include "Cor3dApplication.h"
#include "GUI/SideWidgetComponents/BaseSideWidget.h"
#include "GUI/SideWidgetComponents/SideWidgetGroupBox.h"

PostureEditorTab::PostureEditorTab(QWidget *parent): IMainWindowTab(parent)
{
    setupUi(this);

    glwidget->updateGL();

    //transformations_widget->setGLWidget(glwidget);

//    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
//    connect(cor3dApp->cor3d, SIGNAL(skeleton_list_changed()), this, SLOT(skeleton_list_changed()));
//    connect(cor3dApp->cor3d, SIGNAL(skeleton_selected()), this, SLOT(skeleton_selected()));
//    connect(cor3dApp->cor3d, SIGNAL(selected_skeleton_name_changed()), this, SLOT(selected_skeleton_name_changed()));
//    connect(cor3dApp->cor3d, SIGNAL(selected_skeleton_data_changed()), this, SLOT(selected_skeleton_data_changed()));
//    connect(cor3dApp->cor3d, SIGNAL(selected_skeleton_joint_list_changed()), this, SLOT(selected_skeleton_joint_list_changed()));
//    connect(cor3dApp->cor3d, SIGNAL(selected_skeleton_joint_selection_changed()), this, SLOT(selected_skeleton_joint_selection_changed()));
//    connect(cor3dApp->cor3d, SIGNAL(selected_skeleton_joint_data_changed()), this, SLOT(selected_skeleton_joint_data_changed()));
//    connect(glwidget, SIGNAL(transformations_changed()), this, SLOT(transformations_changed()));
//    connect(cor3dApp->cor3d, SIGNAL(rendering_options_changed()), this, SLOT(rendering_options_changed()));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_selection_changed()), this, SLOT(handle_model_skeleton_selection_changed()));

//    connect(add_new_skeleton, SIGNAL(skeleton_added(string)), this, SLOT(skeleton_added(string)));
//    connect(add_new_skeleton, SIGNAL(skeleton_imported(string)), cor3dApp->cor3d, SLOT(skeleton_import(string)));
//    connect(skeleton_list, SIGNAL(skeleton_selected(int)), this, SLOT(skeleton_selected(int)));
//    connect(skeleton_list, SIGNAL(skeleton_deleted(int)), this, SLOT(skeleton_deleted(int)));
//    connect(skeleton_list, SIGNAL(skeleton_exported(uint,string)), cor3dApp->cor3d, SLOT(skeleton_export(uint,string)));
//    connect(edit_skeleton, SIGNAL(skeleton_name_edited(int,string)), this, SLOT(skeleton_name_edited(int,string)));
//    connect(edit_skeleton, SIGNAL(skeleton_model_edited(int,string)), this, SLOT(skeleton_model_file_edited(int,string)));
//    connect(edit_skeleton, SIGNAL(skeleton_model_scale_edited(int,DCoordinate3)), this, SLOT(skeleton_model_scale_edited(int,DCoordinate3)));
//    connect(edit_skeleton, SIGNAL(skeleton_model_offset_edited(int,DCoordinate3)), this, SLOT(skeleton_model_offset_edited(int,DCoordinate3)));
//    connect(add_new_joint, SIGNAL(joint_added(int,string,int)), this, SLOT(joint_added(int,string,int)));
//    connect(edit_joint, SIGNAL(joint_selected(int, int)), this, SLOT(joint_selected(int, int)));
//    connect(edit_joint, SIGNAL(joint_parent_edited(int,int,int)), this, SLOT(joint_parent_edited(int,int,int)));
//    connect(edit_joint, SIGNAL(joint_type_edited(int,int,Type)), this, SLOT(joint_type_edited(int,int,Type)));
//    connect(edit_joint, SIGNAL(joint_axis_edited(int,int,DCoordinate3)), this, SLOT(joint_axis_edited(int,int,DCoordinate3)));
//    connect(edit_joint, SIGNAL(joint_orientation_edited(int,int,DCoordinate3)), this, SLOT(joint_orientation_edited(int,int,DCoordinate3)));
//    connect(edit_joint, SIGNAL(joint_configuration_edited(int,int,DCoordinate3)), this, SLOT(joint_configuration_edited(int,int,DCoordinate3)));
//    connect(transformations_widget, SIGNAL(translation_edited(DCoordinate3)), glwidget, SLOT(set_translation(DCoordinate3)));
//    connect(transformations_widget, SIGNAL(rotation_edited(DCoordinate3)), glwidget, SLOT(set_rotation(DCoordinate3)));
//    connect(transformations_widget, SIGNAL(zoom_factor_edited(double)), glwidget, SLOT(set_zoom_factor(double)));
//    connect(rendering_options_widget, SIGNAL(rendering_options_edited(RenderingOptions*)), this, SLOT(rendering_options_edited(RenderingOptions*)));
}

void PostureEditorTab::initialize()
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

void PostureEditorTab::handle_model_skeleton_selection_changed()
{
    glwidget->updateGL();
    connect(glwidget, SIGNAL(view_joint_selection_changed(int)), cor3dApp->cor3d->get_skeleton(), SLOT(handle_view_joint_selection_changed(int)));
    connect(glwidget, SIGNAL(view_joint_fabrik_moved(DCoordinate3)), cor3dApp->cor3d->get_skeleton(), SLOT(handle_view_joint_fabrik_moved(DCoordinate3)));
}

void PostureEditorTab::skeleton_list_changed()
{
//    skeleton_list->update_content();
//    add_new_skeleton->update_content();
}

void PostureEditorTab::skeleton_selected()
{
//    skeleton_list->update_content();
//    edit_skeleton->update_content();
//    add_new_joint->update_content();
//    edit_joint->update_content();
//    glwidget->updateGL();
}

void PostureEditorTab::selected_skeleton_name_changed()
{
//    skeleton_list->update_content();
//    add_new_skeleton->update_content();
//    edit_skeleton->update_content();
}

void PostureEditorTab::selected_skeleton_data_changed()
{
//    edit_skeleton->update_content();
//    glwidget->updateGL();
}

void PostureEditorTab::selected_skeleton_joint_list_changed()
{
//    add_new_joint->update_content();
//    edit_joint->update_content();
//    glwidget->updateGL();
}

void PostureEditorTab::selected_skeleton_joint_selection_changed()
{
//    edit_joint->update_content();
//    glwidget->updateGL();
}

void PostureEditorTab::selected_skeleton_joint_name_changed()
{

}

void PostureEditorTab::selected_skeleton_joint_data_changed()
{
//    edit_joint->update_content();
//    glwidget->updateGL();
}

void PostureEditorTab::transformations_changed()
{
//    transformations_widget->update_content();
//    glwidget->updateGL();
}

void PostureEditorTab::rendering_options_changed()
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

