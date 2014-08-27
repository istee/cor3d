#include "AddNewJoint.h"

#include "Cor3dApplication.h"
#include "Model/Cor3d.h"
#include "StdExtension.h"

using namespace std;
using namespace cor3d;

AddNewJoint::AddNewJoint(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

void AddNewJoint::update_content()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    if (cor3dApp->cor3d.is_skeleton_selected())
    {
        new_joint_name->setEnabled(true);
        parent_comboBox->setEnabled(true);

        Skeleton current_skeleton = cor3dApp->cor3d.get_selected_skeleton();
        unsigned int joint_count = current_skeleton.get_joint_count();
        string name = "Joint " + std::to_string(joint_count);
        if (current_skeleton.is_joint_name_reserved(name))
        {
            unsigned int nr = 2;
            do
            {
                name = "Joint " + std::to_string(joint_count);
                name += "_";
                name += std::to_string(nr);
            } while (current_skeleton.is_joint_name_reserved(name));
        }
        new_joint_name->setText(QString::fromStdString(name));

        parent_comboBox->clear();
        vector<BaseEntity> joint_list = cor3dApp->cor3d.get_selected_skeleton().get_joint_list();
        for (vector<BaseEntity>::iterator it = joint_list.begin(); it != joint_list.end(); it++)
        {
            parent_comboBox->addItem(QString::fromStdString(((BaseEntity) *it).get_name()), QVariant(((BaseEntity) *it).get_id()));
        }
        parent_comboBox->setCurrentIndex(joint_list.size() - 1);
    }
    else
    {
        new_joint_name->setEnabled(false);
        parent_comboBox->setEnabled(false);
    }
}

void AddNewJoint::on_add_new_joint_button_released()
{
    string name = new_joint_name->text().toStdString();
    int parent_id = -1;
    if (parent_comboBox->currentIndex() >= 0)
    {
        parent_id = parent_comboBox->itemData(parent_comboBox->currentIndex()).toInt(0);
    }
    emit joint_added(name, parent_id);
}
