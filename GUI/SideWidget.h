#pragma once

#include <QWidget>
#include "ui_SideWidget.h"

class SideWidget: public QWidget, public Ui::SideWidget
{
    Q_OBJECT
public:
    // special and default constructor
    SideWidget(QWidget *parent = 0);

public slots:
    void set_zoom_factor(double value);
    void set_trans_x(double value);
    void set_trans_y(double value);
    void set_trans_z(double value);
};
