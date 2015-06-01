#include "EditJoint.h"


#include "Cor3dApplication.h"


using namespace std;

EditJoint::EditJoint(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);

    joint->setLabel("Joint");
    joint->setEditable(true);
    parent_joint->setLabel("Parent");
    type->setLabel("Type");
    rotation_axis->setTitle("Axis");
    position_vector->setTitle("Local position vector");
    configuration->setTitle("Joint value");
    configuration->setLabels("min", "initial", "max");

    vector<BaseEntity> joint_types = cor3d::Joint::get_joint_types();
    type->populate(joint_types);

    coordinate_settings = DCoordinate3(-100, 0.1, 100);
    angle_settings = DCoordinate3(-180, 1, 180);

    rotation_axis->setSettings(coordinate_settings);
    position_vector->setSettings(coordinate_settings);

    connect(joint, SIGNAL(selection_changed(int)), this, SIGNAL(view_joint_selection_changed(int)));
    connect(parent_joint, SIGNAL(selection_changed(int)), this, SIGNAL(view_joint_parent_changed(int)));
    connect(type, SIGNAL(selection_changed(int)), this, SIGNAL(view_joint_type_changed(int)));
    connect(rotation_axis, SIGNAL(coordinates_changed(DCoordinate3)), this, SIGNAL(view_joint_axis_changed(DCoordinate3)));
    connect(position_vector, SIGNAL(coordinates_changed(DCoordinate3)), this, SIGNAL(view_joint_orientation_changed(DCoordinate3)));
    connect(configuration, SIGNAL(coordinates_changed(DCoordinate3)), this, SIGNAL(view_joint_configuration_changed(DCoordinate3)));
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
