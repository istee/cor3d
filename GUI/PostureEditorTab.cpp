#include "PostureEditorTab.h"

#include "Cor3dApplication.h"
#include "GUI/SideWidgetComponents/BaseSideWidget.h"
#include "GUI/SideWidgetComponents/SideWidgetGroupBox.h"
#include "GUI/PostureGLWidget.h"

PostureEditorTab::PostureEditorTab(QWidget *parent): IMainWindowTab(parent)
{
    setupUi(this);
    QList<int> sizes = QList<int>();
    sizes.append(1000);
    sizes.append(1);
    splitter->setSizes(sizes);

    glwidget = new PostureGLWidget();
    glwidget->updateGL();
    glwidgetHolderLayout->layout()->addWidget(glwidget);

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    connect(glwidget, SIGNAL(glwidgetTranslationChanged(DCoordinate3)), cor3dApp->cor3d, SLOT(handle_view_translation_changed(DCoordinate3)));
    connect(glwidget, SIGNAL(glwidgetRotationChanged(DCoordinate3)), cor3dApp->cor3d, SLOT(handle_view_rotation_changed(DCoordinate3)));
    connect(glwidget, SIGNAL(glwidgetZoomChanged(double)), cor3dApp->cor3d, SLOT(handle_view_zoom_changed(double)));

    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_added(string)), this, SLOT(handle_model_skeleton_added(string)));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_deleted(string)), this, SLOT(handle_model_skeleton_deleted(string)));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_renamed(string,string)), this, SLOT(handle_model_skeleton_renamed(string,string)));
    connect(cor3dApp->cor3d, SIGNAL(model_skeleton_selection_changed(string,string)), this, SLOT(handle_model_skeleton_selection_changed(string,string)));

    connect(managePostures, SIGNAL(viewSkeletonSelected(string)), cor3dApp->cor3d, SLOT(handle_view_skeleton_selected(string)));
}

void PostureEditorTab::initialize()
{
    QList<SideWidgetGroupBox*> groupbox_list = this->sideWidget->findChildren<SideWidgetGroupBox*>();
    for (QList<SideWidgetGroupBox*>::iterator it = groupbox_list.begin(); it != groupbox_list.end(); it++)
    {
        //(*it)->toggled();
    }

    QList<BaseSideWidget*> sidewidget_list = this->sideWidget->findChildren<BaseSideWidget*>();
    for (QList<BaseSideWidget*>::iterator it = sidewidget_list.begin(); it != sidewidget_list.end(); it++)
    {
        //(*it)->update_content();
    }
}

void PostureEditorTab::handle_model_skeleton_added(const string& name)
{
    managePostures->addSkeleton(name);
}

void PostureEditorTab::handle_model_skeleton_deleted(const string& name)
{
    managePostures->deleteSkeleton(name);
}

void PostureEditorTab::handle_model_skeleton_selection_changed(const string& oldSelectionName, const string& newSelectionName)
{
    managePostures->selectSkeleton(newSelectionName);

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton* skeleton = cor3dApp->cor3d->getSkeletonByName(newSelectionName);
    connect(glwidget, SIGNAL(view_joint_selection_changed(int)), skeleton, SLOT(handle_view_joint_selection_changed(int)));
    connect(glwidget, SIGNAL(view_joint_absolute_position_changed(DCoordinate3)), skeleton, SLOT(handle_view_joint_fabrik_moved(DCoordinate3)));
}

void PostureEditorTab::handle_model_skeleton_renamed(const string& oldName, const string& newName)
{
    managePostures->renameSkeleton(oldName, newName);
}

