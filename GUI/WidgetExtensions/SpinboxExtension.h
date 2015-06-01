#pragma once

#include <QDoubleSpinBox>
#include <QLineEdit>

#include <iostream>

using namespace std;

class SpinboxExtension : public QDoubleSpinBox
{
    Q_OBJECT
public:
    SpinboxExtension(QWidget* parent = 0) : QDoubleSpinBox(parent)
    {
        connect(this, SIGNAL(valueChanged(double)), this, SLOT(onSpinBoxValueChanged()), Qt::QueuedConnection);
    }

private slots:
    void onSpinBoxValueChanged()
    {
        this->findChild<QLineEdit*>()->deselect();
    }
};
