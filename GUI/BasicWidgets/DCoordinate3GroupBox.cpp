#include "DCoordinate3GroupBox.h"

DCoordinate3GroupBox::DCoordinate3GroupBox(QWidget *parent): QWidget(parent)
{
    setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QApplication::palette().color(QPalette::Disabled, QPalette::WindowText));
    groupBox->setPalette(palette);
}

void DCoordinate3GroupBox::editingFinished()
{
    emit CoordinatesChanged(getValue());
}

const DCoordinate3 DCoordinate3GroupBox::getValue() const
{
    return DCoordinate3(xDoubleSpinBox->value(), yDoubleSpinBox->value(), zDoubleSpinBox->value());
}

void DCoordinate3GroupBox::setValue(const DCoordinate3& dcoordinate3)
{
    blockSignals(true);
    if (fabs(xDoubleSpinBox->value() - dcoordinate3.x()) > 0.0001)
    {
        xDoubleSpinBox->setValue(dcoordinate3.x());
    }
    if (fabs(yDoubleSpinBox->value() - dcoordinate3.y()) > 0.0001)
    {
        yDoubleSpinBox->setValue(dcoordinate3.y());
    }
    if (fabs(zDoubleSpinBox->value() - dcoordinate3.z()) > 0.0001)
    {
        zDoubleSpinBox->setValue(dcoordinate3.z());
    }
    blockSignals(false);
}

void DCoordinate3GroupBox::setLabels(const string& xLabel_string, const string& yLabel_string, const string& zLabel_string)
{
    xLabel->setText(QString::fromStdString(xLabel_string));
    yLabel->setText(QString::fromStdString(yLabel_string));
    zLabel->setText(QString::fromStdString(zLabel_string));
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
            xDoubleSpinBox->setMaximum(settings[0]);
            xDoubleSpinBox->setSingleStep(settings[1]);
            xDoubleSpinBox->setMaximum(settings[2]);
            break;
        }
    case 1:
        {
            yDoubleSpinBox->setMaximum(settings[0]);
            yDoubleSpinBox->setSingleStep(settings[1]);
            yDoubleSpinBox->setMaximum(settings[2]);
            break;
        }
    case 2:
        {
            zDoubleSpinBox->setMaximum(settings[0]);
            zDoubleSpinBox->setSingleStep(settings[1]);
            zDoubleSpinBox->setMaximum(settings[2]);
            break;
        }
    default: {}
    }
}

void DCoordinate3GroupBox::on_xDoubleSpinBox_editingFinished()
{
    emit xCoordinateChanged(xDoubleSpinBox->value());
    editingFinished();
}

void DCoordinate3GroupBox::on_yDoubleSpinBox_editingFinished()
{
    emit yCoordinateChanged(yDoubleSpinBox->value());
    editingFinished();
}

void DCoordinate3GroupBox::on_zDoubleSpinBox_editingFinished()
{
    emit zCoordinateChanged(zDoubleSpinBox->value());
    editingFinished();
}

void DCoordinate3GroupBox::on_xDoubleSpinBox_valueChanged(double value)
{
    emit xCoordinateChanged(value);
    editingFinished();
}

void DCoordinate3GroupBox::on_yDoubleSpinBox_valueChanged(double value)
{
    emit yCoordinateChanged(value);
    editingFinished();
}

void DCoordinate3GroupBox::on_zDoubleSpinBox_valueChanged(double value)
{
    emit zCoordinateChanged(value);
    editingFinished();
}
