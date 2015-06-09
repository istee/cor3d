#pragma once

#include <QWidget>
#include <QHash>

#include <string>

#include "ui_AddNewJoint.h"
#include "BaseSideWidget.h"
#include "GUI/WidgetExtensions/TreeWidgetExtension.h"

using namespace std;

class AddNewJoint: public BaseSideWidget, public Ui::AddNewJoint
{
    Q_OBJECT
public:
    // special and default constructor
    AddNewJoint(QWidget *parent = 0);
    void populateJoints(Skeleton* skeleton, Skeleton* previous);
    void selectJoint(const string& name);
    void addJoint(Skeleton* skeleton, Joint* joint, const string& parentName);
    void deleteJoint(const string& name);
    void renameJoint(const string& oldName, const string& newName);
    void updateJointData(Joint* joint);

private:
    void populateJointTreeView(Skeleton* skeleton, Joint* parent, QTreeWidgetItem* item);
    void addWidgetToTreeWidgetItems(QTreeWidgetItem* item);
    void populateTreeViewJoints(Skeleton* skeleton, Joint* joint);
signals:
    void viewJointAdded(const string& name, const string& parentName);
    void viewJointSelected(string name);


    void view_joint_CoordinatesChanged(const string& name, const DCoordinate3& coordinates);
    void view_joint_scale_changed(const string& name, const DCoordinate3& scale);

private slots:
    void on_treeViewJoints_itemSelectionChanged();
    void handleViewJointAdded(const string& name);
    void handleViewJointEdited(const string& name);
};
