#include "EditSkeleton.h"

<<<<<<< HEAD
#include <QFileDialog>

#include "Model/Cor3d.h"
#include "Cor3dApplication.h"
=======
#include <iostream>

#include "Model/Cor3d.h"
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa

using namespace std;
using namespace cor3d;

EditSkeleton::EditSkeleton(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

void EditSkeleton::enable_edits()
{
    name_lineEdit->setEnabled(true);
<<<<<<< HEAD
    model_button->setEnabled(true);
    model_scale_x_doubleSpinbox->setEnabled(true);
    model_scale_y_doubleSpinbox->setEnabled(true);
    model_scale_z_doubleSpinbox->setEnabled(true);
    model_x_doubleSpinBox->setEnabled(true);
    model_y_doubleSpinBox->setEnabled(true);
    model_z_doubleSpinBox->setEnabled(true);
=======
    model_lineEdit->setEnabled(true);
    model_x_spinBox->setEnabled(true);
    model_y_spinBox->setEnabled(true);
    model_z_spinBox->setEnabled(true);
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
}

void EditSkeleton::disable_edits()
{
    name_lineEdit->setEnabled(false);
<<<<<<< HEAD
    model_button->setEnabled(false);
    model_scale_x_doubleSpinbox->setEnabled(false);
    model_scale_y_doubleSpinbox->setEnabled(false);
    model_scale_z_doubleSpinbox->setEnabled(false);
    model_x_doubleSpinBox->setEnabled(false);
    model_y_doubleSpinBox->setEnabled(false);
    model_z_doubleSpinBox->setEnabled(false);
}

void EditSkeleton::update_content()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    if (cor3dApp->cor3d.is_skeleton_selected())
    {
        enable_edits();
        Skeleton skeleton = cor3dApp->cor3d.get_selected_skeleton();
        name_lineEdit->setText(QString::fromStdString(skeleton.get_name()));
        if (skeleton.get_model_file().empty())
        {
            model_file_label->setText("-");
        }
        else
        {
            model_file_label->setText(QString::fromStdString(skeleton.get_model_file()));
        }

        DCoordinate3 model_scale = skeleton.get_model_scale();
        model_scale_x_doubleSpinbox->setValue(model_scale.x());
        model_scale_y_doubleSpinbox->setValue(model_scale.y());
        model_scale_z_doubleSpinbox->setValue(model_scale.z());

        DCoordinate3 model_offset = skeleton.get_model_offset();
        model_x_doubleSpinBox->setValue(model_offset.x());
        model_y_doubleSpinBox->setValue(model_offset.y());
        model_z_doubleSpinBox->setValue(model_offset.z());
=======
    model_lineEdit->setEnabled(false);
    model_x_spinBox->setEnabled(false);
    model_y_spinBox->setEnabled(false);
    model_z_spinBox->setEnabled(false);
}

void EditSkeleton::update()
{
    int selected = Cor3d::getInstance().get_selected_skeleton();
    if (selected >= 0)
    {
        enable_edits();
        name_lineEdit->setText(QString::fromStdString(Cor3d::getInstance().get_skeleton_name_by_id(selected)));
        model_lineEdit->setText(QString::fromStdString(Cor3d::getInstance().get_skeleton_model_file(selected)));
        model_x_spinBox->setValue(Cor3d::getInstance().get_skeleton_model_x(selected));
        model_y_spinBox->setValue(Cor3d::getInstance().get_skeleton_model_y(selected));
        model_z_spinBox->setValue(Cor3d::getInstance().get_skeleton_model_z(selected));
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
    }
    else
    {
        disable_edits();
    }
}
<<<<<<< HEAD

void EditSkeleton::data_changed()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton skeleton = cor3dApp->cor3d.get_selected_skeleton();
    skeleton.set_name(name_lineEdit->text().toStdString());
    DCoordinate3 offset = DCoordinate3(model_x_doubleSpinBox->value(), model_y_doubleSpinBox->value(), model_z_doubleSpinBox->value());
    skeleton.set_model_offset(offset);
    DCoordinate3 scale = DCoordinate3(model_scale_x_doubleSpinbox->value(), model_scale_y_doubleSpinbox->value(), model_scale_z_doubleSpinbox->value());
    skeleton.set_model_scale(scale);
    emit skeleton_edited(skeleton);
}

void EditSkeleton::on_name_lineEdit_editingFinished()
{
    data_changed();
}

void EditSkeleton::on_model_scale_x_doubleSpinbox_valueChanged(double )
{
    data_changed();
}

void EditSkeleton::on_model_scale_y_doubleSpinbox_valueChanged(double )
{
    data_changed();
}


void EditSkeleton::on_model_scale_z_doubleSpinbox_valueChanged(double )
{
    data_changed();
}

void EditSkeleton::on_model_x_doubleSpinBox_valueChanged(double )
{
    data_changed();
}

void EditSkeleton::on_model_y_doubleSpinBox_valueChanged(double )
{
    data_changed();
}

void EditSkeleton::on_model_z_doubleSpinBox_valueChanged(double )
{
    data_changed();
}

void EditSkeleton::on_model_button_released()
{
    string file_name = QFileDialog::getOpenFileName(this,tr("Open OFF model file"), "", tr("OFF Files (*.off)")).toStdString();
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton skeleton = cor3dApp->cor3d.get_selected_skeleton();
    skeleton.set_model_file(file_name);
    emit skeleton_edited(skeleton);
}
=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
