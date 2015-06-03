#include "EditJoint.h"


#include "Cor3dApplication.h"


using namespace std;

EditJoint::EditJoint(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);

    parent_joint->setLabel("Parent");
    type->setLabel("Type");
    parent_relative_position->setTitle("Relative coordinates to parent");
    absolute_position->setTitle("Absolute coordinates");
    joint_scale->setTitle("Joint scale");

    vector<BaseEntity> joint_types = cor3d::Joint::get_joint_types();
    type->populate(joint_types);

    coordinate_settings = DCoordinate3(-100, 0.1, 100);
    angle_settings = DCoordinate3(-180, 1, 180);

    parent_relative_position->setSettings(coordinate_settings);
    absolute_position->setSettings(coordinate_settings);
    joint_scale->setSettings(DCoordinate3(0.1, 0.1, 2));

    connect(absolute_position, SIGNAL(coordinates_changed(DCoordinate3)), this, SLOT(handle_joint_absolute_coordinates_changed(DCoordinate3)));
    connect(parent_relative_position, SIGNAL(coordinates_changed(DCoordinate3)), this, SLOT(handle_joint_relative_coordinates_changed(DCoordinate3)));
    connect(joint_scale, SIGNAL(coordinates_changed(DCoordinate3)), this, SLOT(handle_joint_scale_changed(DCoordinate3)));
}

void EditJoint::updateContent(BaseEntity* baseEntity)
{
    Joint* joint = (Joint*) baseEntity;
    _entityName = joint->get_name();
    type->setIndex(joint->get_type());
    absolute_position->setValue(joint->get_coordinates());
    joint_scale->setValue(joint->get_scale());

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton* skeleton = cor3dApp->cor3d->get_skeleton();
    Joint* parent = skeleton->get_joint(joint->get_parent());
    parent_relative_position->setValue(joint->get_coordinates() - parent->get_coordinates());
}

void EditJoint::update_content()
{
    /*
    blockSignals(true);
    joint->setEnabled(false);
    editable_properties->setEnabled(false);

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton* skeleton = cor3dApp->cor3d->get_skeleton();
    if (skeleton)
    {
        if (skeleton->get_joint_count() > 0)
        {
            joint->setEnabled(true);

            joint->populate(skeleton->get_joint_list());
            int joint_id = skeleton->get_selected_joint_id();
            joint->setIndex(joint_id);
            if (skeleton->is_joint_selected())
            {
                editable_properties->setEnabled(true);

                parent_joint->populate(skeleton->get_possible_parents(joint_id));
                parent_joint->setIndex(skeleton->get_joint_parent(joint_id));

                type->setIndex(skeleton->get_joint_type(joint_id));

                rotation_axis->setValue(skeleton->get_joint_axis(joint_id));

                position_vector->setValue(skeleton->get_joint_orientation(joint_id));

                if (skeleton->get_joint_type(joint_id) == ROTATIONAL)
                {
                    configuration->setSettings(angle_settings);
                }
                else
                {
                    configuration->setSettings(coordinate_settings);
                }
                configuration->setValue(skeleton->get_joint_configuration(joint_id));
            }
        }
    }
    blockSignals(false);
    */
}

void EditJoint::handle_joint_absolute_coordinates_changed(const DCoordinate3& coordinates)
{
    emit (view_joint_coordinates_changed(_entityName, coordinates));
}

void EditJoint::handle_joint_relative_coordinates_changed(const DCoordinate3& coordinates)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton* skeleton = cor3dApp->cor3d->get_skeleton();
    Joint* joint = skeleton->get_joint(skeleton->getJointIdByName(_entityName));
    Joint* parentJoint = skeleton->get_joint(joint->get_parent());
    DCoordinate3 absoluteCoordinates = parentJoint->get_coordinates() + coordinates;
    emit (view_joint_coordinates_changed(_entityName, absoluteCoordinates));
}

void EditJoint::handle_joint_scale_changed(const DCoordinate3& scale)
{
    emit (view_joint_scale_changed(_entityName, scale));
}
