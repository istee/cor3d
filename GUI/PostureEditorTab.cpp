#include "PostureEditorTab.h"

#include "Cor3dApplication.h"
#include "GUI/SideWidgets/BaseSideWidget.h"
#include "GUI/WidgetExtensions/GroupBoxExtension.h"
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

    connect(glwidget, SIGNAL(glwidgetTranslationChanged(DCoordinate3)), cor3dApp->cor3d, SLOT(handleViewTranslationChanged(DCoordinate3)));
    connect(glwidget, SIGNAL(glwidgetRotationChanged(DCoordinate3)), cor3dApp->cor3d, SLOT(handleViewRotationChanged(DCoordinate3)));
    connect(glwidget, SIGNAL(glwidgetZoomChanged(double)), cor3dApp->cor3d, SLOT(handleViewZoomChanged(double)));

    connect(cor3dApp->cor3d, SIGNAL(modelSkeletonSelected(Skeleton*,Skeleton*)), this, SLOT(handleModelSkeletonSelected(Skeleton*,Skeleton*)));
    //connect(cor3dApp->cor3d, SIGNAL(modelPostureSelected(Skeleton*,Posture*,Skeleton*,Posture*)), this, SLOT(handleModelPostureSelected(Skeleton*,Posture*,Skeleton*,Posture*)));
}

void PostureEditorTab::handleModelSkeletonSelected(Skeleton* selectedSkeleton, Skeleton* previousSkeleton)
{
    if (previousSkeleton)
    {
        disconnect(glwidget, SIGNAL(viewJointSelected(int)), previousSkeleton, SLOT(handleViewJointSelected(int)));

        disconnect(managePostures, SIGNAL(viewPostureAdded(string)), previousSkeleton, SLOT(handleViewPostureAdded(string)));
        disconnect(managePostures, SIGNAL(viewPostureDeleted(string)), previousSkeleton, SLOT(handleViewPostureDeleted(string)));
        disconnect(managePostures, SIGNAL(viewPostureRenamed(string, string)), previousSkeleton, SLOT(handleViewPostureRenamed(string, string)));
        disconnect(managePostures, SIGNAL(viewPostureSelected(string)), previousSkeleton, SLOT(handleViewPostureSelected(string)));

        disconnect(previousSkeleton, SIGNAL(modelPostureAdded(Skeleton*, Posture*)), this, SLOT(handleModelPostureAdded(Skeleton*, Posture*)));
        disconnect(previousSkeleton, SIGNAL(modelPostureSelected(Skeleton*, Posture*)), this, SLOT(handleModelPostureSelected(Skeleton*, Posture*)));
    }

    if (selectedSkeleton)
    {
        managePostures->populatePostureList(selectedSkeleton);
        editPosture->populatePostureJoints(selectedSkeleton, selectedSkeleton->getSelectedPosture());

        connect(glwidget, SIGNAL(viewJointSelected(int)), selectedSkeleton, SLOT(handleViewJointSelected(int)));
        connect(glwidget, SIGNAL(viewPostureJointAbsoluteCoordinatesChanged(DCoordinate3)), selectedSkeleton, SLOT(handleViewPostureJointAbsoluteCoordinatesChanged(DCoordinate3)));

        connect(managePostures, SIGNAL(viewPostureAdded(string)), selectedSkeleton, SLOT(handleViewPostureAdded(string)));
        connect(managePostures, SIGNAL(viewPostureDeleted(string)), selectedSkeleton, SLOT(handleViewPostureDeleted(string)));
        connect(managePostures, SIGNAL(viewPostureRenamed(string, string)), selectedSkeleton, SLOT(handleViewPostureRenamed(string, string)));
        connect(managePostures, SIGNAL(viewPostureSelected(string)), selectedSkeleton, SLOT(handleViewPostureSelected(string)));

        connect(selectedSkeleton, SIGNAL(modelPostureAdded(Skeleton*, Posture*)), this, SLOT(handleModelPostureAdded(Skeleton*, Posture*)));
        connect(selectedSkeleton, SIGNAL(modelPostureDeleted(Skeleton*, string)), this, SLOT(handleModelPostureDeleted(Skeleton*, string)));
        connect(selectedSkeleton, SIGNAL(modelPostureRenamed(string, string)), this, SLOT(handleModelPostureRenamed(string, string)));
        connect(selectedSkeleton, SIGNAL(modelPostureSelected(Skeleton*, Posture*, Posture*)), this, SLOT(handleModelPostureSelected(Skeleton*, Posture*, Posture*)));
        connect(selectedSkeleton, SIGNAL(modelPostureDataChanged(Posture*)), this, SLOT(handleModelPostureDataChanged(Posture*)));

        connect(selectedSkeleton, SIGNAL(modelJointSelected(string)), this, SLOT(handleModelJointSelected(string)));
    }

    glwidget->setSkeleton(selectedSkeleton);
    updateGLWidget();
}

void PostureEditorTab::handleModelPostureAdded(Skeleton* skeleton, Posture* posture)
{
    managePostures->addPosture(skeleton, posture);
}

void PostureEditorTab::handleModelPostureDeleted(Skeleton* skeleton, const string& postureName)
{
    managePostures->deletePosture(skeleton, postureName);
}

void PostureEditorTab::handleModelPostureRenamed(const string& oldPostureName, const string& newPostureName)
{
    managePostures->renamePosture(oldPostureName, newPostureName);
}

void PostureEditorTab::handleModelPostureSelected(Skeleton* selectedSkeleton, Posture* selectedPosture, Posture* previousPosture)
{
    if (previousPosture)
    {
        disconnect(previousPosture, SIGNAL(modelPostureDataChanged(Posture*)), this, SLOT(handleModelPostureDataChanged(Posture*)));
    }
    else
    {
        connect(selectedPosture, SIGNAL(modelPostureDataChanged(Posture*)), this, SLOT(handleModelPostureDataChanged(Posture*)));
    }
    managePostures->selectPosture(selectedSkeleton, selectedPosture);
    editPosture->populatePostureJoints(selectedSkeleton, selectedPosture);
    updateGLWidget();
}

void PostureEditorTab::handleModelPostureDataChanged(Posture* posture)
{
    updateGLWidget();
}

void PostureEditorTab::handleModelJointSelected(const string& jointName)
{
    editPosture->selectJoint(jointName);
    updateGLWidget();
}
