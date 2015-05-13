#include "DCoordinate3GroupBox.h"

DCoordinate3GroupBox::DCoordinate3GroupBox(QWidget *parent): QWidget(parent)
{
    setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QApplication::palette().color(QPalette::Disabled, QPalette::WindowText));
    groupBox->setPalette(palette);
}

void DCoordinate3GroupBox::on_editingFinished()
{
    emit coordinates_changed(value());
}

const DCoordinate3 DCoordinate3GroupBox::value() const
{
    return DCoordinate3(x_doubleSpinBox->value(), y_doubleSpinBox->value(), z_doubleSpinBox->value());
}

void DCoordinate3GroupBox::setValue(const DCoordinate3& dcoordinate3)
{
    blockSignals(true);
    x_doubleSpinBox->setValue(dcoordinate3.x());
    y_doubleSpinBox->setValue(dcoordinate3.y());
    z_doubleSpinBox->setValue(dcoordinate3.z());
    blockSignals(false);
}

void DCoordinate3GroupBox::setLabels(const string& x_label_string, const string& y_label_string, const string& z_label_string)
{
    x_label->setText(QString::fromStdString(x_label_string));
    y_label->setText(QString::fromStdString(y_label_string));
    z_label->setText(QString::fromStdString(z_label_string));
}

void DCoordinate3GroupBox::setTitle(const string& title)
{
    groupBox->setTitle(QString::fromStdString(title));
}

void DCoordinate3GroupBox::setSettings(const DCoordinate3& settings)
{
    setSettings(settings, 0);
    setSettings(settings, 1);
    setSettings(settings, 2);
}

void DCoordinate3GroupBox::setSettings(const DCoordinate3& settings, unsigned int spin_box_number)
{
    switch(spin_box_number)
    {
    case 0:
        {
            x_doubleSpinBox->setMaximum(settings[0]);
            x_doubleSpinBox->setSingleStep(settings[1]);
            x_doubleSpinBox->setMaximum(settings[2]);
            break;
        }
    case 1:
        {
            y_doubleSpinBox->setMaximum(settings[0]);
            y_doubleSpinBox->setSingleStep(settings[1]);
            y_doubleSpinBox->setMaximum(settings[2]);
            break;
        }
    case 2:
        {
            z_doubleSpinBox->setMaximum(settings[0]);
            z_doubleSpinBox->setSingleStep(settings[1]);
            z_doubleSpinBox->setMaximum(settings[2]);
            break;
        }
    default: {}
    }
}

void DCoordinate3GroupBox::on_x_doubleSpinBox_editingFinished()
{
    emit x_coordinate_changed(x_doubleSpinBox->value());
    on_editingFinished();
}

void DCoordinate3GroupBox::on_y_doubleSpinBox_editingFinished()
{
    emit y_coordinate_changed(y_doubleSpinBox->value());
    on_editingFinished();
}

void DCoordinate3GroupBox::on_z_doubleSpinBox_editingFinished()
{
    emit z_coordinate_changed(z_doubleSpinBox->value());
    on_editingFinished();
}

void DCoordinate3GroupBox::on_x_doubleSpinBox_valueChanged(double value)
{
    emit x_coordinate_changed(value);
    on_editingFinished();
}

void DCoordinate3GroupBox::on_y_doubleSpinBox_valueChanged(double value)
{
    emit y_coordinate_changed(value);
    on_editingFinished();
}

void DCoordinate3GroupBox::on_z_doubleSpinBox_valueChanged(double value)
{
    emit z_coordinate_changed(value);
    on_editingFinished();
}
