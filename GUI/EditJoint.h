#pragma once

#include <QWidget>

#include "ui_EditJoint.h"

#include "Model/Joint.h"

using namespace cor3d;

class EditJoint: public QWidget, public Ui::EditJoint
{
    Q_OBJECT
public:
    // special and default constructor
    EditJoint(QWidget *parent = 0);
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
};
