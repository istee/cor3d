#include "AddNewJoint.h"

#include "Cor3dApplication.h"
#include "Model/Cor3d.h"
#include "StdExtension.h"

using namespace std;
using namespace cor3d;

AddNewJoint::AddNewJoint(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    name->setLabel("Name");
    parent_joint->setLabel("Parent joint");
}

void AddNewJoint::update_content()
{
    this->setEnabled(false);

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton* selected_skeleton = cor3dApp->cor3d->get_skeleton();

    if (selected_skeleton)
    {
        const vector<BaseEntity*> skeleton_list = cor3dApp->cor3d->get_skeleton_list();
        for (vector<BaseEntity*>::const_iterator it = skeleton_list.begin(); it != skeleton_list.end(); it++)
        {
            cout << (*it)->get_name() << endl;
        }

        this->setEnabled(true);

        name->setValue(selected_skeleton->next_joint_name());
        const vector<BaseEntity> joints = selected_skeleton->get_joint_list();
        parent_joint->populate(joints);
        parent_joint->setIndex(joints.size() - 1);
    }
}

void AddNewJoint::on_add_new_joint_button_released()
{
    emit view_joint_added(name->value(), parent_joint->key());
}
