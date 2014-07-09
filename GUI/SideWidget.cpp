#include "SideWidget.h"
#include <iostream>

using namespace std;

SideWidget::SideWidget(QWidget *parent):
        QWidget(parent)
{
    setupUi(this);
}

void SideWidget::set_zoom_factor(double value)
{
    zoom_factor_spin_box->setValue(value);
}

void SideWidget::set_trans_x(double value)
{
    trans_x_spin_box->setValue(value);
}

void SideWidget::set_trans_y(double value)
{
    trans_y_spin_box->setValue(value);
}

void SideWidget::set_trans_z(double value)
{
    trans_z_spin_box->setValue(value);
}

void SideWidget::selected_joint(double x, double y, double z)
{
    selected_x->setValue(x);
    selected_y->setValue(y);
    selected_z->setValue(z);
}

void SideWidget::on_checkBox_render_mesh_toggled(bool checked)
{
    emit checkBox_render_mesh_toggled(-1, checked);
}

void SideWidget::on_checkBox_render_links_toggled(bool checked)
{
    emit checkBox_render_links_toggled(-1, checked);
}

void SideWidget::on_checkBox_render_joints_toggled(bool checked)
{
    emit checkBox_render_joints_toggled(-1, checked);
}
