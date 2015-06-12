#include "SkeletonEditWidget.h"

#include <QFileDialog>

#include "Model/Cor3d.h"
#include "Cor3dApplication.h"

using namespace std;
using namespace cor3d;

SkeletonEditWidget::SkeletonEditWidget(Skeleton* skeleton, QWidget *parent): BaseEditWidget(parent)
{
    setupUi(this);
    meshFile->setLabel("Model file");
    meshFile->setCaption("Open OFF model file");
    meshFile->setFilter("OFF Files (*.off)");
    meshScale->setTitle("Model scale");
    meshOffset->setTitle("Model offset");

    meshScale->setSettings(DCoordinate3(0.1, 0.1, 10));
    meshOffset->setSettings(DCoordinate3(-100, 0.1, 100));

    connect(meshFile, SIGNAL(fileChanged(string)), skeleton, SLOT(handleViewSkeletonModelChanged(string)));
    connect(meshScale, SIGNAL(CoordinatesChanged(DCoordinate3)), skeleton, SLOT(handleViewSkeletonModelScaleChanged(DCoordinate3)));
    connect(meshOffset, SIGNAL(CoordinatesChanged(DCoordinate3)), skeleton, SLOT(handleViewSkeletonModelOffsetChanged(DCoordinate3)));
}

void SkeletonEditWidget::updateContent(BaseEntity* baseEntity)
{
    Skeleton* skeleton = (Skeleton*) baseEntity;
    _entityName = skeleton->getName();
    meshFile->setValue(skeleton->getMeshFile());
    meshScale->setValue(skeleton->getMeshScale());
    meshOffset->setValue(skeleton->getMeshOffset());
}
