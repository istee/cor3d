#include "EditJoint.h"

#include "Cor3dApplication.h"

using namespace std;

EditJoint::EditJoint(QWidget *parent): QWidget(parent)
{
    setupUi(this);
    type_comboBox->addItem(QString::fromStdString("ROTATIONAL"), QVariant(0));
    type_comboBox->addItem(QString::fromStdString("TRANSLATIONAL"), QVariant(1));
}

void EditJoint::update_content()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    if (cor3dApp->cor3d.is_skeleton_selected())
    {
        name_comboBox->setEnabled(true);
        name_comboBox->clear();
        name_comboBox->addItem(QString::fromStdString("---"), QVariant(-1));
        Skeleton skeleton = cor3dApp->cor3d.get_selected_skeleton();
        vector<BaseEntity> joint_list = skeleton.get_joint_list();
        for (vector<BaseEntity>::iterator it = joint_list.begin(); it != joint_list.end(); it++)
        {
            const QString name = QString::fromStdString(((BaseEntity) *it).get_name());
            const int id = ((BaseEntity) *it).get_id();
            name_comboBox->addItem(name, QVariant(id));
        }

        if (cor3dApp->cor3d.get_selected_skeleton().is_joint_selected())
        {
            parent_comboBox->setEnabled(true);
            type_comboBox->setEnabled(true);
            axis_x_doubleSpinBox->setEnabled(true);
            axis_y_doubleSpinBox->setEnabled(true);
            axis_z_doubleSpinBox->setEnabled(true);
            length_doubleSpinBox->setEnabled(true);
            initial_doubleSpinBox->setEnabled(true);
            upper_doubleSpinBox->setEnabled(true);
            lower_doubleSpinBox->setEnabled(true);

            Joint joint = skeleton.get_selected_joint();

            name_comboBox->setCurrentIndex(joint.get_id() + 1);
            parent_comboBox->clear();
            vector<BaseEntity> possible_parents = skeleton.get_possible_parents(joint.get_id());
            for (vector<BaseEntity>::iterator it = possible_parents.begin(); it != possible_parents.end(); it++)
            {
                const QString name = QString::fromStdString(((BaseEntity) *it).get_name());
                const int id = (*it).get_id();
                parent_comboBox->addItem(name, QVariant(id));
            }
            parent_comboBox->setCurrentIndex(parent_comboBox->findData(joint.get_parent()));
            type_comboBox->setCurrentIndex(type_comboBox->findData(joint.get_type()));

            axis_x_doubleSpinBox->setValue(joint.get_axis_x());
            axis_y_doubleSpinBox->setValue(joint.get_axis_y());
            axis_z_doubleSpinBox->setValue(joint.get_axis_z());
            length_doubleSpinBox->setValue(joint.get_length());
            initial_doubleSpinBox->setValue(joint.get_initial_value());
            upper_doubleSpinBox->setValue(joint.get_upper_limit());
            lower_doubleSpinBox->setValue(joint.get_lower_limit());
        }
        else
        {
            name_comboBox->setEnabled(true);
            parent_comboBox->setEnabled(false);
            type_comboBox->setEnabled(false);
            axis_x_doubleSpinBox->setEnabled(false);
            axis_y_doubleSpinBox->setEnabled(false);
            axis_z_doubleSpinBox->setEnabled(false);
            length_doubleSpinBox->setEnabled(false);
            initial_doubleSpinBox->setEnabled(false);
            upper_doubleSpinBox->setEnabled(false);
            lower_doubleSpinBox->setEnabled(false);
        }
    }
    else
    {
        name_comboBox->setEnabled(false);
        parent_comboBox->setEnabled(false);
        type_comboBox->setEnabled(false);
        axis_x_doubleSpinBox->setEnabled(false);
        axis_y_doubleSpinBox->setEnabled(false);
        axis_z_doubleSpinBox->setEnabled(false);
        length_doubleSpinBox->setEnabled(false);
        initial_doubleSpinBox->setEnabled(false);
        upper_doubleSpinBox->setEnabled(false);
        lower_doubleSpinBox->setEnabled(false);
    }
}

void EditJoint::data_changed()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton skeleton = cor3dApp->cor3d.get_selected_skeleton();
    Joint joint = skeleton.get_selected_joint();
    joint.set_parent((parent_comboBox->itemData(parent_comboBox->currentIndex())).toInt(0));
    joint.set_type((Type) (type_comboBox->itemData(type_comboBox->currentIndex())).toInt(0));
    DCoordinate3 axis = DCoordinate3(axis_x_doubleSpinBox->value(), axis_y_doubleSpinBox->value(), axis_z_doubleSpinBox->value());
    joint.set_axis(axis);
    joint.set_length(length_doubleSpinBox->value());
    joint.set_initial_value(initial_doubleSpinBox->value());
    joint.set_lower_limit(lower_doubleSpinBox->value());
    joint.set_upper_limit(upper_doubleSpinBox->value());
    emit joint_edited(joint);
}

void EditJoint::on_name_comboBox_activated(int index)
{
    emit joint_selected((name_comboBox->itemData(index)).toInt(0));
}

void EditJoint::on_axis_x_doubleSpinBox_editingFinished()
{
    data_changed();
}

void EditJoint::on_axis_y_doubleSpinBox_editingFinished()
{
    data_changed();
}

void EditJoint::on_axis_z_doubleSpinBox_editingFinished()
{
    data_changed();
}

void EditJoint::on_length_doubleSpinBox_editingFinished()
{
    data_changed();
}

void EditJoint::on_initial_doubleSpinBox_editingFinished()
{
    data_changed();
}

void EditJoint::on_upper_doubleSpinBox_editingFinished()
{
    data_changed();
}

void EditJoint::on_lower_doubleSpinBox_editingFinished()
{
    data_changed();
}

void EditJoint::on_parent_comboBox_activated(QString )
{
    data_changed();
}

void EditJoint::on_type_comboBox_activated(QString )
{
    data_changed();
}
