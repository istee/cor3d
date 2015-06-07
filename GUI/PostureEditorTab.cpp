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

    connect(cor3dApp->cor3d, SIGNAL(modelSkeletonAdded(Skeleton*)), this, SLOT(handleModelSkeletonAdded(Skeleton*)));
    connect(cor3dApp->cor3d, SIGNAL(modelSkeletonDeleted(string)), this, SLOT(handleModelSkeletonDeleted(string)));
    connect(cor3dApp->cor3d, SIGNAL(modelSkeletonRenamed(string,string)), this, SLOT(handleModelSkeletonRenamed(string,string)));
    //connect(cor3dApp->cor3d, SIGNAL(model_skeleton_selection_changed(string,string)), this, SLOT(handle_model_skeleton_selection_changed(string,string)));

    //connect(managePostures, SIGNAL(viewSkeletonSelected(string)), cor3dApp->cor3d, SLOT(handle_view_skeleton_selected(string)));
}

void PostureEditorTab::handleModelSkeletonAdded(Skeleton* skeleton)
{
    managePostures->addSkeleton(skeleton->get_name());
    connect(skeleton, SIGNAL(modelPostureRenamed(string,string,string)), this, SLOT(handleModelPostureRenamed(string,string,string)));
    connect(skeleton, SIGNAL(modelPostureDeleted(string,string)), this, SLOT(handleModelPostureDeleted(string,string)));
}

void PostureEditorTab::handleModelSkeletonDeleted(const string& name)
{
    managePostures->deleteSkeleton(name);
}

void PostureEditorTab::handleModelSkeletonRenamed(const string& oldName, const string& newName)
{
    managePostures->renameSkeleton(oldName, newName);
}

void PostureEditorTab::handle_model_skeleton_selection_changed(const string& oldSelectionName, const string& newSelectionName)
{
    managePostures->selectSkeleton(newSelectionName);

    Skeleton* oldSelection = cor3dApp->cor3d->getSkeletonByName(oldSelectionName);
    if (oldSelection)
    {
        disconnect(glwidget, SIGNAL(view_joint_selection_changed(int)), oldSelection, SLOT(handle_view_joint_selection_changed(int)));
        disconnect(glwidget, SIGNAL(view_joint_absolute_position_changed(DCoordinate3)), oldSelection, SLOT(handle_view_joint_fabrik_moved(DCoordinate3)));

        disconnect(managePostures, SIGNAL(viewPostureAdded(string)), oldSelection, SLOT(handle_view_posture_added(string)));

        disconnect(oldSelection, SIGNAL(modelPostureAdded(Skeleton*, Posture*)), this, SLOT(handleModelPostureAdded(Skeleton*, Posture*)));
    }

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton* skeleton = cor3dApp->cor3d->getSkeletonByName(newSelectionName);
    connect(glwidget, SIGNAL(view_joint_selection_changed(int)), skeleton, SLOT(handle_view_joint_selection_changed(int)));
    connect(glwidget, SIGNAL(view_joint_absolute_position_changed(DCoordinate3)), skeleton, SLOT(handle_view_joint_fabrik_moved(DCoordinate3)));

    connect(managePostures, SIGNAL(viewPostureAdded(string)), skeleton, SLOT(handle_view_posture_added(string)));

    connect(skeleton, SIGNAL(modelPostureAdded(Skeleton*, Posture*)), this, SLOT(handleModelPostureAdded(Skeleton*, Posture*)));

    glwidget->updateGL();
}

void PostureEditorTab::handleModelPostureAdded(Skeleton* skeleton, Posture* posture)
{
    managePostures->addPosture(skeleton, posture);
}

void PostureEditorTab::handleModelPostureDeleted(const string& skeletonName, const string& postureName)
{
    managePostures->deletePosture(skeletonName, postureName);
}

void PostureEditorTab::handleModelPostureRenamed(const string& skeletonName, const string& oldPostureName, const string& newPostureName)
{
    managePostures->renamePosture(skeletonName, oldPostureName, newPostureName);
}
