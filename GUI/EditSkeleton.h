#pragma once

#include <QWidget>
<<<<<<< HEAD

#include "ui_EditSkeleton.h"

#include "Model/Skeleton.h"

using namespace cor3d;

=======
#include "ui_EditSkeleton.h"

>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
class EditSkeleton: public QWidget, public Ui::EditSkeleton
{
    Q_OBJECT

    void enable_edits();
    void disable_edits();
public:
    // special and default constructor
    EditSkeleton(QWidget *parent = 0);
<<<<<<< HEAD
    void update_content();
    void data_changed();
=======
    void update();
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa

public slots:

signals:
<<<<<<< HEAD
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
=======

private slots:

>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
};
