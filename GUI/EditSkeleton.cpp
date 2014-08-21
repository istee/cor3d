#include "EditSkeleton.h"

#include <iostream>

#include "Model/Cor3d.h"

using namespace std;
using namespace cor3d;

EditSkeleton::EditSkeleton(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

void EditSkeleton::enable_edits()
{
    name_lineEdit->setEnabled(true);
    model_lineEdit->setEnabled(true);
    model_x_spinBox->setEnabled(true);
    model_y_spinBox->setEnabled(true);
    model_z_spinBox->setEnabled(true);
}

void EditSkeleton::disable_edits()
{
    name_lineEdit->setEnabled(false);
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
    }
    else
    {
        disable_edits();
    }
}
