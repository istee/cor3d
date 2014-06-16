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
