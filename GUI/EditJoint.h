#pragma once

#include <QWidget>
<<<<<<< HEAD

#include "ui_EditJoint.h"

#include "Model/Joint.h"

using namespace cor3d;

=======
#include "ui_EditJoint.h"

>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
class EditJoint: public QWidget, public Ui::EditJoint
{
    Q_OBJECT
public:
    // special and default constructor
    EditJoint(QWidget *parent = 0);
<<<<<<< HEAD
    void update_content();
    void data_changed();

public slots:

signals:
    void joint_selected(int id);
    void joint_edited(const Joint& joint);

private slots:
    void on_type_comboBox_activated(QString );
    void on_parent_comboBox_activated(QString );
    void on_lower_doubleSpinBox_editingFinished();
    void on_upper_doubleSpinBox_editingFinished();
    void on_initial_doubleSpinBox_editingFinished();
    void on_length_doubleSpinBox_editingFinished();
    void on_axis_z_doubleSpinBox_editingFinished();
    void on_axis_y_doubleSpinBox_editingFinished();
    void on_axis_x_doubleSpinBox_editingFinished();
    void on_name_comboBox_activated(int index);
=======

public slots:
    //void set_zoom_factor(double value);
    //void set_trans_x(double value);
    //void set_trans_y(double value);
    //void set_trans_z(double value);
    //void selected_joint(double x, double y, double z);

signals:
    //void checkBox_render_mesh_toggled(int skeleton_id, bool value);
    //void checkBox_render_links_toggled(int skeleton_id, bool value);
    //void checkBox_render_joints_toggled(int skeleton_id, bool value);

private slots:
    //void on_checkBox_render_mesh_toggled(bool checked);
    //void on_checkBox_render_links_toggled(bool checked);
    //void on_checkBox_render_joints_toggled(bool checked);
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
};
