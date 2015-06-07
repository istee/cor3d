#include "EditJoint.h"


#include "Cor3dApplication.h"


using namespace std;

EditJoint::EditJoint(Skeleton* skeleton, Joint* joint, QWidget *parent): BaseEditWidget(parent)
{
    setupUi(this);

    parent_joint->setLabel("Parent");
    //type->setLabel("Type");
    parent_relative_position->setTitle("Relative coordinates to parent");
    absolute_position->setTitle("Absolute coordinates");
    joint_scale->setTitle("Joint scale");

    //vector<BaseEntity> joint_types = cor3d::Joint::get_joint_types();
    //type->populate(joint_types);

    coordinate_settings = DCoordinate3(-100, 0.1, 100);
    angle_settings = DCoordinate3(-180, 1, 180);

    parent_relative_position->setSettings(coordinate_settings);
    absolute_position->setSettings(coordinate_settings);
    joint_scale->setSettings(DCoordinate3(0.1, 0.1, 2));


    if (joint)
    {
        updateContent(joint);
        connect(this, SIGNAL(viewJointAbsoluteCoordinatesChanged(string,DCoordinate3)), skeleton, SLOT(handleViewJointAbsoluteCoordinatesChanged(string,DCoordinate3)));
        connect(this, SIGNAL(viewJointRelativeCoordinatesChanged(string,DCoordinate3)), skeleton, SLOT(handleViewJointRelativeCoordinatesChanged(string,DCoordinate3)));
        connect(this, SIGNAL(viewJointScaleChanged(string,DCoordinate3)), skeleton, SLOT(handleViewJointScaleChanged(string,DCoordinate3)));
    }

    connect(absolute_position, SIGNAL(coordinates_changed(DCoordinate3)), this, SLOT(handleJointAbsoluteCoordinatesChanged(DCoordinate3)));
    connect(parent_relative_position, SIGNAL(coordinates_changed(DCoordinate3)), this, SLOT(handleJointRelativeCoordinatesChanged(DCoordinate3)));
    connect(joint_scale, SIGNAL(coordinates_changed(DCoordinate3)), this, SLOT(handleJointScaleChanged(DCoordinate3)));
}

void EditJoint::updateContent(BaseEntity* baseEntity)
{
    Joint* joint = (Joint*) baseEntity;
    _entityName = joint->get_name();
    //type->setIndex(joint->get_type());
    absolute_position->setValue(joint->get_coordinates());
    joint_scale->setValue(joint->get_scale());
    parent_relative_position->setValue(joint->get_orientation());
}

void EditJoint::handleJointAbsoluteCoordinatesChanged(const DCoordinate3& absoluteCoordinates)
{
    emit viewJointAbsoluteCoordinatesChanged(_entityName, absoluteCoordinates);
}

void EditJoint::handleJointRelativeCoordinatesChanged(const DCoordinate3& relativeCoordinates)
{
    emit viewJointRelativeCoordinatesChanged(_entityName, relativeCoordinates);
}

void EditJoint::handleJointScaleChanged(const DCoordinate3& scale)
{
    emit viewJointScaleChanged(_entityName, scale);
}
