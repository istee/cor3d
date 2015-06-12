#pragma once

#include <QWidget>

#include "ui_PostureJointSideWidget.h"

#include "Model/Skeleton.h"
#include "Model/Joint.h"

class PostureJointSideWidget : public QWidget, public Ui::PostureJointSideWidget
{
    Q_OBJECT

private:
    Posture* currentPosture;
    void populatePostureJoints(Skeleton* skeleton, Joint* joint);
    void updateEditWidgets(QTreeWidgetItem* parent, Posture* posture);

public:
    explicit PostureJointSideWidget(QWidget *parent = 0);
    void populatePostureJoints(Skeleton* skeleton, Posture* posture);

signals:
    void viewJointSelected(string name);
    void viewPostureAlgorithmTypeSelected(string name);

public slots:
    void handleModelPostureIsEdited(Posture*, bool);
    void handleModelPostureDataChanged(Posture*, const string&);
    void selectJoint(const string& jointName);

private slots:
    void on_fabrikRadioButton_toggled(bool checked);
    void on_rigidRadioButton_toggled(bool checked);
    void handleViewPostureJointEditWidgeted(const string& jointName);
    void on_postureJointTreeWidget_itemSelectionChanged();
};
