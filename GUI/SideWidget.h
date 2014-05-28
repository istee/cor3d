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
private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_currentIndexChanged(QString );
};
