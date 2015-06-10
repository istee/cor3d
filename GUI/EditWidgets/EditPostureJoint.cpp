#include "EditPostureJoint.h"
#include "ui_EditPostureJoint.h"

EditPostureJoint::EditPostureJoint(Skeleton* skeleton, Joint* joint, QWidget *parent) :
    BaseEditWidget(parent),
    ui(new Ui::EditPostureJoint)
{
    ui->setupUi(this);
    _jointId = joint->getId();
    _jointName = joint->getName();
    ui->absoluteCoordinates->setTitle("Absolute coordinates");
    DCoordinate3 settings = DCoordinate3(-100, 0.1, 100);
    ui->absoluteCoordinates->setSettings(settings);
    ui->rotationAngles->setTitle("Rotation around parent");

    connect(ui->absoluteCoordinates, SIGNAL(CoordinatesChanged(DCoordinate3)), this, SLOT(handleAbsoluteCoordinatesChanged(DCoordinate3)));
    connect(this, SIGNAL(viewPostureJointAbsoluteCoordinatesChanged(string,DCoordinate3)), skeleton, SLOT(handleViewPostureJointAbsoluteCoordinatesChanged(string,DCoordinate3)));
}

EditPostureJoint::~EditPostureJoint()
{
    delete ui;
}

void EditPostureJoint::updateContent(BaseEntity* baseEntity)
{
    Posture* posture = (Posture*) baseEntity;
    ui->absoluteCoordinates->setValue(posture->getAbsolutePostureCoordinate(_jointId));
}

void EditPostureJoint::handleAbsoluteCoordinatesChanged(const DCoordinate3& absoluteCoordinates)
{
    emit viewPostureJointAbsoluteCoordinatesChanged(_jointName, absoluteCoordinates);
}
