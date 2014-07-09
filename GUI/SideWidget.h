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
    void selected_joint(double x, double y, double z);

signals:
    void checkBox_render_mesh_toggled(int skeleton_id, bool value);
    void checkBox_render_links_toggled(int skeleton_id, bool value);
    void checkBox_render_joints_toggled(int skeleton_id, bool value);

private slots:
    void on_checkBox_render_mesh_toggled(bool checked);
    void on_checkBox_render_links_toggled(bool checked);
    void on_checkBox_render_joints_toggled(bool checked);
};
