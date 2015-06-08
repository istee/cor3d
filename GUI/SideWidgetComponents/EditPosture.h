#pragma once

#include <QWidget>

#include "Model/Skeleton.h"
#include "Model/Joint.h"

namespace Ui {
    class EditPosture;
}

class EditPosture : public QWidget
{
    Q_OBJECT

public:
    explicit EditPosture(QWidget *parent = 0);
    void populatePostureJoints(Skeleton* skeleton, Posture* posture);
    ~EditPosture();

private:
    Ui::EditPosture *ui;
    void populatePostureJoints(Skeleton* skeleton, Joint* joint);

private slots:
    void on_postureJointTreeWidget_itemSelectionChanged();
};
