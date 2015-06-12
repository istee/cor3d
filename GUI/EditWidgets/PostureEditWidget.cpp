#include "PostureEditWidget.h"

PostureEditWidget::PostureEditWidget(Skeleton* skeleton, Joint* joint, QWidget *parent) : BaseEditWidget(parent)
{
    setupUi(this);
    _jointId = joint->getId();
    _jointName = joint->getName();
    absoluteCoordinates->setTitle("Absolute coordinates");
    DCoordinate3 settings = DCoordinate3(-100, 0.1, 100);
    absoluteCoordinates->setSettings(settings);
    rotationAngles->setTitle("Rotation around parent");

    connect(absoluteCoordinates, SIGNAL(CoordinatesChanged(DCoordinate3)), this, SLOT(handleAbsoluteCoordinatesChanged(DCoordinate3)));
    connect(this, SIGNAL(viewPostureJointAbsoluteCoordinatesChanged(string,DCoordinate3)), skeleton, SLOT(handleViewPostureJointAbsoluteCoordinatesChanged(string,DCoordinate3)));
}

void PostureEditWidget::updateContent(BaseEntity* baseEntity)
{
    Posture* posture = (Posture*) baseEntity;
    absoluteCoordinates->setValue(posture->getAbsolutePostureCoordinate(_jointId));
}

void PostureEditWidget::handleAbsoluteCoordinatesChanged(const DCoordinate3& absoluteCoordinates)
{
    emit viewPostureJointAbsoluteCoordinatesChanged(_jointName, absoluteCoordinates);
}
