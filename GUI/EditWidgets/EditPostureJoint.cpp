#include "EditPostureJoint.h"
#include "ui_EditPostureJoint.h"

EditPostureJoint::EditPostureJoint(QWidget *parent) :
    BaseEditWidget(parent),
    ui(new Ui::EditPostureJoint)
{
    ui->setupUi(this);

    ui->absoluteCoordinates->setTitle("Absolute coordinates");
    ui->rotationAngles->setTitle("Rotation around parent");
}

EditPostureJoint::~EditPostureJoint()
{
    delete ui;
}

void EditPostureJoint::updateContent(BaseEntity*)
{

}
