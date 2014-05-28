#include "SideWidget.h"
#include <iostream>

using namespace std;

SideWidget::SideWidget(QWidget *parent):
        QWidget(parent)
{
    setupUi(this);
}

void SideWidget::on_comboBox_currentIndexChanged(QString text)
{
    cout << text.toInt() << endl;
}

void SideWidget::on_comboBox_currentIndexChanged(int index)
{
    cout << "hello" << endl;
    cout << comboBox->itemText(index).toAscii().data() << endl;
}

void SideWidget::set_zoom_factor(double value)
{
    zoom_factor_spin_box->setValue(value);
}
