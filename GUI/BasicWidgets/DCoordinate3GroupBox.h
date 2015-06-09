#pragma once

#include <QWidget>
#include "ui_DCoordinate3GroupBox.h"

#include "Core/DCoordinates3.h"

using namespace std;
using namespace cagd;

class DCoordinate3GroupBox: public QWidget, protected Ui::DCoordinate3GroupBox
{
    Q_OBJECT

public:
    // special and default constructor
    DCoordinate3GroupBox(QWidget *parent = 0);
    const DCoordinate3 value() const;
    void setValue(const DCoordinate3& dcoordinate3);
    void setLabels(const string& xLabel, const string& yLabel, const string& zLabel);
    void setTitle(const string& title);
    void setSettings(const DCoordinate3& settings);
    void setSettings(const DCoordinate3& settings, unsigned int spinBoxNumber);

private:
    void editingFinished();

signals:
    void xCoordinateChanged(double x);
    void yCoordinateChanged(double y);
    void zCoordinateChanged(double z);
    void CoordinatesChanged(const DCoordinate3& dcoordinate3);

private slots:
    void on_zDoubleSpinBox_valueChanged(double );
    void on_yDoubleSpinBox_valueChanged(double );
    void on_xDoubleSpinBox_valueChanged(double );
    void on_zDoubleSpinBox_editingFinished();
    void on_yDoubleSpinBox_editingFinished();
    void on_xDoubleSpinBox_editingFinished();
};
