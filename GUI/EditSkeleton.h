#pragma once

#include <QWidget>

#include "ui_EditSkeleton.h"

#include "Model/Skeleton.h"

using namespace cor3d;

class EditSkeleton: public QWidget, public Ui::EditSkeleton
{
    Q_OBJECT

    void enable_edits();
    void disable_edits();
public:
    // special and default constructor
    EditSkeleton(QWidget *parent = 0);
    void update_content();
    void data_changed();

public slots:

signals:
    void skeleton_edited(const Skeleton& skeleton);

private slots:
    void on_model_button_released();
    void on_name_lineEdit_editingFinished();
    void on_model_z_doubleSpinBox_valueChanged(double );
    void on_model_y_doubleSpinBox_valueChanged(double );
    void on_model_x_doubleSpinBox_valueChanged(double );
    void on_model_scale_z_doubleSpinbox_valueChanged(double );
    void on_model_scale_y_doubleSpinbox_valueChanged(double );
    void on_model_scale_x_doubleSpinbox_valueChanged(double );
};
