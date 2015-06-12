#pragma once

#include <QWidget>
#include <QHash>

#include <string>

#include "ui_JointSideWidget.h"
#include "BaseSideWidget.h"
#include "GUI/WidgetExtensions/TreeWidgetExtension.h"

using namespace std;

class JointSideWidget: public BaseSideWidget, public Ui::JointSideWidget
{
    Q_OBJECT
public:
    // special and default constructor
    JointSideWidget(QWidget *parent = 0);
    void populateJoints(Skeleton* skeleton, Skeleton* previous);
    void selectJoint(const string& name);
    void addJoint(Skeleton* skeleton, Joint* joint, const string& parentName);
    void deleteJoint(const string& name);
    void renameJoint(const string& oldName, const string& newName);
    void updateJointData(Joint* joint);

private:
    void populateTreeViewJoints(Skeleton* skeleton, Joint* joint);
signals:
    void viewJointAdded(const string& name, const string& parentName);
    void viewJointSelected(string name);

private slots:
    void on_treeViewJoints_itemSelectionChanged();
    void handleViewJointAdded(const string& name);
    void handleViewJointEditWidgetToggled(const string& name);
};
