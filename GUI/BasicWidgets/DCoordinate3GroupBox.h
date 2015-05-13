#pragma once

#include <QWidget>
#include "ui_DCoordinate3GroupBox.h"

#include "Core/DCoordinates3.h"

using namespace std;
using namespace cagd;

class DCoordinate3GroupBox: public QWidget, public Ui::DCoordinate3GroupBox
{
    Q_OBJECT
    void on_editingFinished();

public:
    // special and default constructor
    DCoordinate3GroupBox(QWidget *parent = 0);
    const DCoordinate3 value() const;
    void setValue(const DCoordinate3& dcoordinate3);
    void setLabels(const string& x_label, const string& y_label, const string& z_label);
    void setTitle(const string& title);
    void setSettings(const DCoordinate3& settings);
    void setSettings(const DCoordinate3& settings, unsigned int spin_box_number);

signals:
    void x_coordinate_changed(double x);
    void y_coordinate_changed(double y);
    void z_coordinate_changed(double z);
    void coordinates_changed(const DCoordinate3& dcoordinate3);

private slots:
    void on_z_doubleSpinBox_valueChanged(double );
    void on_y_doubleSpinBox_valueChanged(double );
    void on_x_doubleSpinBox_valueChanged(double );
    void on_z_doubleSpinBox_editingFinished();
    void on_y_doubleSpinBox_editingFinished();
    void on_x_doubleSpinBox_editingFinished();
};
