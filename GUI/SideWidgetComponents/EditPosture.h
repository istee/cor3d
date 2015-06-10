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

private:
    Ui::EditPosture *ui;
    Posture* currentPosture;
    void populatePostureJoints(Skeleton* skeleton, Joint* joint);

public:
    explicit EditPosture(QWidget *parent = 0);
    void populatePostureJoints(Skeleton* skeleton, Posture* posture);
    ~EditPosture();

signals:
    void viewJointSelected(string name);
    void viewPostureAlgorithmTypeSelected(string name);

public slots:
    void handleModelPostureIsEdited(Posture*, bool);
    void selectJoint(const string& jointName);

private slots:
    void on_fabrikRadioButton_toggled(bool checked);
    void on_rigidRadioButton_toggled(bool checked);
    void handleViewPostureJointEdited(const string& jointName);
    void on_postureJointTreeWidget_itemSelectionChanged();
};
