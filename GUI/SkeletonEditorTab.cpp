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

    connect(cor3dApp->cor3d, SIGNAL(modelSkeletonAdded(Skeleton*)), this, SLOT(handleModelSkeletonAdded(Skeleton*)));
    connect(cor3dApp->cor3d, SIGNAL(modelSkeletonDeleted(string)), this, SLOT(handleModelSkeletonDeleted(string)));
    connect(cor3dApp->cor3d, SIGNAL(modelSkeletonRenamed(string,string)), this, SLOT(handleModelSkeletonRenamed(string,string)));
    connect(cor3dApp->cor3d, SIGNAL(modelSkeletonSelected(Skeleton*,Skeleton*)), this, SLOT(handleModelSelected(Skeleton*,Skeleton*)));

    connect(skeleton_list, SIGNAL(viewSkeletonAdded(string)), cor3dApp->cor3d, SLOT(handleViewSkeletonAdded(string)));
    connect(skeleton_list, SIGNAL(viewSkeletonSelected(string)), cor3dApp->cor3d, SLOT(handleViewSkeletonSelected(string)));
    connect(skeleton_list, SIGNAL(viewSkeletonDeleted(const string&)), cor3dApp->cor3d, SLOT(handleViewSkeletonDeleted(const string&)));
    connect(skeleton_list, SIGNAL(viewSkeletonRenamed(string,string)), cor3dApp->cor3d, SLOT(handleViewSkeletonRenamed(string, string)));
}

void SkeletonEditorTab::handleModelSkeletonAdded(Skeleton* skeleton)
{
    skeleton_list->addSkeleton(skeleton);
    connect(skeleton, SIGNAL(modelSkeletonDataChanged(Skeleton*)), this, SLOT(handleModelSkeletonDataChanged(Skeleton*)));
}

void SkeletonEditorTab::handleModelSkeletonDeleted(const string& name)
{
    skeleton_list->deleteSkeleton(name);
}

void SkeletonEditorTab::handleModelSkeletonRenamed(const string& oldName, const string& newName)
{
    skeleton_list->renameSkeleton(oldName, newName);
}

void SkeletonEditorTab::handleModelSelected(Skeleton* selected, Skeleton* previous)
{
    if (previous)
    {
        disconnect(previous, SIGNAL(modelJointAdded(Skeleton*,Joint*,string)), this, SLOT(handleModelJointAdded(Skeleton*,Joint*,string)));
        disconnect(previous, SIGNAL(modelJointDeleted(string)), this, SLOT(handleModelJointDeleted(string)));
        disconnect(previous, SIGNAL(modelJointRenamed(string,string)), this, SLOT(handleModelJointRenamed(string,string)));
    }

    add_new_joint->populateJoints(selected, previous);
    glwidget->setSkeleton(selected);
    cout << "select van " << endl;
    updateGLWidget();

    if (selected)
    {
        skeleton_list->selectSkeleton(selected->get_name());

        connect(selected, SIGNAL(modelJointAdded(Skeleton*,Joint*,string)), this, SLOT(handleModelJointAdded(Skeleton*,Joint*,string)));
        connect(selected, SIGNAL(modelJointDeleted(string)), this, SLOT(handleModelJointDeleted(string)));
        connect(selected, SIGNAL(modelJointRenamed(string,string)), this, SLOT(handleModelJointRenamed(string,string)));

        connect(selected, SIGNAL(modelJointDataChanged(Joint*)), this, SLOT(handleModelJointDataChanged(Joint*)));

        connect(glwidget, SIGNAL(view_joint_selection_changed(int)), selected, SLOT(handle_view_joint_selection_changed(int)));
        connect(glwidget, SIGNAL(view_joint_absolute_position_changed(DCoordinate3)), selected, SLOT(handle_view_joint_absolute_position_changed(DCoordinate3)));
    }
}

void SkeletonEditorTab::handleModelJointAdded(Skeleton* skeleton, Joint* joint, const string& parentName)
{
    cout << "joint add " << endl;
    add_new_joint->addJoint(skeleton, joint, parentName);
    updateGLWidget();
}

void SkeletonEditorTab::handleModelJointDeleted(const string& name)
{
    add_new_joint->deleteJoint(name);
    updateGLWidget();
}

void SkeletonEditorTab::handleModelJointRenamed(const string& oldName, const string& newName)
{
    add_new_joint->renameJoint(oldName, newName);
}

void SkeletonEditorTab::handleModelJointSelected(const string& name)
{
    cout << "handleModelJointSelected " << name << endl;
    add_new_joint->selectJoint(name);
    updateGLWidget();
}

void SkeletonEditorTab::handleModelJointDataChanged(Joint* joint)
{
    add_new_joint->updateJointData(joint);
    glwidget->updateGL();
}

void SkeletonEditorTab::handle_model_rendering_options_changed()
{
    //rendering_options_widget->update_content();
    //glwidget->updateGL();
}

void SkeletonEditorTab::handleModelSkeletonDataChanged(Skeleton* skeleton)
{
    skeleton_list->updateSkeletonModel(skeleton);
    glwidget->updateGL();
}
