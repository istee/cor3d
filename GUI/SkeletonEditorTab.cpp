#include "SkeletonEditorTab.h"
#include "glwidget.h"

#include "Cor3dApplication.h"
#include "GUI/SideWidgetComponents/BaseSideWidget.h"
#include "GUI/SideWidgetComponents/SideWidgetGroupBox.h"

SkeletonEditorTab::SkeletonEditorTab(QWidget *parent):IMainWindowTab(parent)
{
    setupUi(this);
    QList<int> sizes = QList<int>();
    sizes.append(1000);
    sizes.append(1);
    splitter->setSizes(sizes);

    glwidget = new SkeletonGLWidget();
    glwidget->updateGL();
    glwidgetHolderLayout->layout()->addWidget(glwidget);

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    connect(glwidget, SIGNAL(glwidgetTranslationChanged(DCoordinate3)), cor3dApp->cor3d, SLOT(handle_view_translation_changed(DCoordinate3)));
    connect(glwidget, SIGNAL(glwidgetRotationChanged(DCoordinate3)), cor3dApp->cor3d, SLOT(handle_view_rotation_changed(DCoordinate3)));
    connect(glwidget, SIGNAL(glwidgetZoomChanged(double)), cor3dApp->cor3d, SLOT(handle_view_zoom_changed(double)));

    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_added(string)), this, SLOT(handle_model_skeleton_added(string)));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_deleted(string)), this, SLOT(handle_model_skeleton_deleted(string)));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_renamed(string,string)), this, SLOT(handle_model_skeleton_renamed(string,string)));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_selection_changed(string,string)), this, SLOT(handle_model_skeleton_selection_changed(string, string)));
    connect(cor3dApp->cor3d, SIGNAL(model_rendering_options_changed()), this, SLOT(handle_model_rendering_options_changed()));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_model_data_changed(string)), this, SLOT(handle_model_skeleton_model_data_changed(string)));

    connect(skeleton_list, SIGNAL(view_skeleton_added(string)), cor3dApp->cor3d, SLOT(handle_view_skeleton_added(string)));
    connect(skeleton_list, SIGNAL(view_skeleton_selected(int)), cor3dApp->cor3d, SLOT(handle_view_skeleton_selected(int)));
    connect(skeleton_list, SIGNAL(view_skeleton_deleted(const string&)), cor3dApp->cor3d, SLOT(handle_view_skeleton_deleted(const string&)));
    connect(skeleton_list, SIGNAL(view_skeleton_renamed(string,string)), cor3dApp->cor3d, SLOT(handle_view_skeleton_renamed(string, string)));
    connect(skeleton_list, SIGNAL(view_skeleton_model_changed(string,string)), cor3dApp->cor3d, SLOT(handle_view_skeleton_model_changed(string,string)));
    connect(skeleton_list, SIGNAL(view_skeleton_model_offset_changed(string,DCoordinate3)), cor3dApp->cor3d, SLOT(handle_view_skeleton_model_offset_changed(string,DCoordinate3)));
    connect(skeleton_list, SIGNAL(view_skeleton_model_scale_changed(string,DCoordinate3)), cor3dApp->cor3d, SLOT(handle_view_skeleton_model_scale_changed(string,DCoordinate3)));
}

void SkeletonEditorTab::initialize()
{
    QList<SideWidgetGroupBox*> groupbox_list = this->sideWidget->findChildren<SideWidgetGroupBox*>();
    for (QList<SideWidgetGroupBox*>::iterator it = groupbox_list.begin(); it != groupbox_list.end(); it++)
    {
        (*it)->toggled();
    }

    QList<BaseSideWidget*> sidewidget_list = this->sideWidget->findChildren<BaseSideWidget*>();
    for (QList<BaseSideWidget*>::iterator it = sidewidget_list.begin(); it != sidewidget_list.end(); it++)
    {
        (*it)->update_content();

    }
}

void SkeletonEditorTab::handle_model_skeleton_added(const string& name)
{
    skeleton_list->addSkeleton(name);
}

void SkeletonEditorTab::handle_model_skeleton_deleted(const string& name)
{
    skeleton_list->deleteSkeleton(name);
}

void SkeletonEditorTab::handle_model_skeleton_selection_changed(const string& oldSelectionName, const string& newSelectionName)
{
    Skeleton* oldSelection = cor3dApp->cor3d->getSkeletonByName(oldSelectionName);
    if (oldSelection)
    {
        disconnect(oldSelection, SIGNAL(model_joint_added(string)), this, SLOT(handle_model_joint_added(string)));
        disconnect(oldSelection, SIGNAL(model_joint_deleted(string)), this, SLOT(handle_model_joint_deleted(string)));
        disconnect(oldSelection, SIGNAL(model_joint_renamed(string,string)), this, SLOT(handle_model_joint_renamed(string,string)));
        disconnect(oldSelection, SIGNAL(model_joint_selection_changed(string)), this, SLOT(handle_model_joint_selection_changed(string)));
        disconnect(oldSelection, SIGNAL(model_joint_data_changed(string)), this, SLOT(handle_model_joint_data_changed(string)));

        disconnect(add_new_joint, SIGNAL(view_joint_selected(string)), oldSelection, SLOT(handle_view_joint_selection_changed(string)));
        disconnect(add_new_joint, SIGNAL(view_joint_renamed(string,string)), oldSelection, SLOT(handle_view_joint_renamed(string, string)));
        disconnect(add_new_joint, SIGNAL(view_joint_deleted(string)), oldSelection, SLOT(handle_view_joint_deleted(string)));
        disconnect(add_new_joint, SIGNAL(view_joint_coordinates_changed(string,DCoordinate3)), oldSelection, SLOT(handle_view_joint_coordinates_changed(string, DCoordinate3)));
        disconnect(add_new_joint, SIGNAL(view_joint_scale_changed(string,DCoordinate3)), oldSelection, SLOT(handle_view_joint_scale_changed(string,DCoordinate3)));

        connect(glwidget, SIGNAL(view_joint_selection_changed(int)), oldSelection, SLOT(handle_view_joint_selection_changed(int)));
        connect(glwidget, SIGNAL(view_joint_absolute_position_changed(DCoordinate3)), oldSelection, SLOT(handle_view_joint_absolute_position_changed(DCoordinate3)));
    }

    skeleton_list->selectSkeleton(newSelectionName);
    add_new_joint->update_content();
    glwidget->updateGL();

    Skeleton* skeleton = cor3dApp->cor3d->getSkeletonByName(newSelectionName);
    connect(skeleton, SIGNAL(model_joint_added(string)), this, SLOT(handle_model_joint_added(string)));
    connect(skeleton, SIGNAL(model_joint_deleted(string)), this, SLOT(handle_model_joint_deleted(string)));
    connect(skeleton, SIGNAL(model_joint_renamed(string,string)), this, SLOT(handle_model_joint_renamed(string,string)));
    connect(skeleton, SIGNAL(model_joint_selection_changed(string)), this, SLOT(handle_model_joint_selection_changed(string)));
    connect(skeleton, SIGNAL(model_joint_data_changed(string)), this, SLOT(handle_model_joint_data_changed(string)));

    connect(add_new_joint, SIGNAL(view_joint_selected(string)), skeleton, SLOT(handle_view_joint_selection_changed(string)));
    connect(add_new_joint, SIGNAL(view_joint_renamed(string,string)), skeleton, SLOT(handle_view_joint_renamed(string, string)));
    connect(add_new_joint, SIGNAL(view_joint_deleted(string)), skeleton, SLOT(handle_view_joint_deleted(string)));
    connect(add_new_joint, SIGNAL(view_joint_coordinates_changed(string,DCoordinate3)), skeleton, SLOT(handle_view_joint_coordinates_changed(string, DCoordinate3)));
    connect(add_new_joint, SIGNAL(view_joint_scale_changed(string,DCoordinate3)), skeleton, SLOT(handle_view_joint_scale_changed(string,DCoordinate3)));

    connect(glwidget, SIGNAL(view_joint_selection_changed(int)), skeleton, SLOT(handle_view_joint_selection_changed(int)));
    connect(glwidget, SIGNAL(view_joint_absolute_position_changed(DCoordinate3)), skeleton, SLOT(handle_view_joint_absolute_position_changed(DCoordinate3)));
}

void SkeletonEditorTab::handle_model_skeleton_renamed(const string& oldName, const string& newName)
{
    skeleton_list->renameSkeleton(oldName, newName);
}

void SkeletonEditorTab::handle_model_joint_added(const string& name)
{
    add_new_joint->addJoint(name);
    glwidget->updateGL();
}

void SkeletonEditorTab::handle_model_joint_deleted(const string& name)
{
    add_new_joint->deleteJoint(name);
    glwidget->updateGL();
}

void SkeletonEditorTab::handle_model_joint_renamed(const string& oldName, const string& newName)
{
    add_new_joint->renameJoint(oldName, newName);
    glwidget->updateGL();
}

void SkeletonEditorTab::handle_model_joint_selection_changed(const string& name)
{
    add_new_joint->selectJoint(name);
    glwidget->updateGL();
}

void SkeletonEditorTab::handle_model_joint_data_changed(const string& name)
{
    add_new_joint->updateJointData(name);
    glwidget->updateGL();
}

void SkeletonEditorTab::handle_model_rendering_options_changed()
{
    //rendering_options_widget->update_content();
    //glwidget->updateGL();
}

void SkeletonEditorTab::handle_model_skeleton_model_data_changed(const string& skeletonName)
{
    skeleton_list->updateSkeletonModel(skeletonName);
    glwidget->updateGL();
}
