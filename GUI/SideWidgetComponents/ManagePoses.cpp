#include "ManagePoses.h"

#include "Cor3dApplication.h"
#include "Model/Cor3d.h"

using namespace std;
using namespace cor3d;

ManagePoses::ManagePoses(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
}

void ManagePoses::update_content()
{
//    this->setEnabled(false);

//    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
//    Skeleton* selected_skeleton = cor3dApp->cor3d->get_skeleton();

//    if (selected_skeleton)
//    {
//        this->setEnabled(true);

//        name->setValue(selected_skeleton->next_joint_name());
//        const vector<BaseEntity> joints = selected_skeleton->get_joint_list();
//        parent_joint->populate(joints);
//        parent_joint->setIndex(joints.size() - 1);
//    }
}

