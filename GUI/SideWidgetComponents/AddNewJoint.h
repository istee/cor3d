#pragma once

#include <QWidget>
#include <QHash>

#include <string>

#include "ui_AddNewJoint.h"
#include "BaseSideWidget.h"
#include "GUI/WidgetExtensions/BaseEntityDisplayProperties.h"
#include "GUI/WidgetExtensions/TreeWidgetExtension.h"

using namespace std;

class AddNewJoint: public BaseSideWidget, public Ui::AddNewJoint
{
    Q_OBJECT
public:
    // special and default constructor
    AddNewJoint(QWidget *parent = 0);
    void update_content();
    void selectJoint(const string& name);
    void addJoint(const string& name);
    void deleteJoint(const string& name);
    void renameJoint(const string& oldName, const string& newName);
    void updateJointData(const string& name);

private:
    void populateJointTreeView(Skeleton* skeleton, Joint* parent, QTreeWidgetItem* item);
    void addWidgetToTreeWidgetItems(QTreeWidgetItem* item);
    QHash<string,BaseEntityDisplayProperties>  _jointsDisplayProperties;
    void populateTreeViewJoints(Skeleton* skeleton, Joint* joint);

signals:
    void view_joint_added(const string& name, const string& parentName);
    void view_joint_selected(string name);
    void view_joint_renamed(string, string);
    void view_joint_deleted(string name);

    void view_joint_coordinates_changed(const string& name, const DCoordinate3& coordinates);
    void view_joint_scale_changed(const string& name, const DCoordinate3& scale);

private slots:
    void on_treeViewJoints_itemSelectionChanged();
    void on_toolButtonAdd_clicked();
    void handle_view_joint_edited(const string& name);
};
