#include "AddNewJoint.h"

#include <QTreeWidgetItem>

#include "Cor3dApplication.h"
#include "Model/Cor3d.h"
#include "StdExtension.h"
#include "GUI/BasicWidgets/EditableDeletableListItem.h"
#include "GUI/SideWidgetComponents/EditJoint.h"

using namespace std;
using namespace cor3d;

AddNewJoint::AddNewJoint(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    addName->setLabel("Name");
    _jointsDisplayProperties = QHash<string,BaseEntityDisplayProperties>();

    connect(groupBox, SIGNAL(groupbox_toggled(bool)), this, SLOT(handle_groupbox_toggled(bool)));
}

void AddNewJoint::addJoint(const string& name)
{
    Joint* joint = _cor3d->get_skeleton()->get_joint(name);
    string parentName = _cor3d->get_skeleton()->get_parent_joint(name)->get_name();

    EditJoint* editJoint = new EditJoint(treeViewJoints);
    editJoint->updateContent(joint);
    connect(editJoint, SIGNAL(view_joint_coordinates_changed(string,DCoordinate3)), this, SIGNAL(view_joint_coordinates_changed(string,DCoordinate3)));
    connect(editJoint, SIGNAL(view_joint_scale_changed(string,DCoordinate3)), this, SIGNAL(view_joint_scale_changed(string,DCoordinate3)));

    EditableDeletableListItem* listItem = new EditableDeletableListItem(name, editJoint, treeViewJoints);
    connect(listItem, SIGNAL(view_list_item_renamed(string,string)), this, SIGNAL(view_joint_renamed(string, string)));
    connect(listItem, SIGNAL(view_list_item_deleted(string)), this, SIGNAL(view_joint_deleted(const string&)));
    connect(listItem, SIGNAL(view_list_item_edited(string)), this, SLOT(handle_view_joint_edited(string)));

    treeViewJoints->addTreeWidgetItem(parentName, name, listItem);

    addName->setValue(_cor3d->get_skeleton()->next_joint_name());
}

void AddNewJoint::deleteJoint(const string& name)
{
    Joint* parent = _cor3d->get_skeleton()->get_parent_joint(name);
    if (parent)
    {
        treeViewJoints->deleteTreeWidgetItemByData(parent->get_name(), name);
    }
    else
    {
        treeViewJoints->deleteTopLevelTreeWidgetItemByData(name);
    }
}

void AddNewJoint::renameJoint(const string& oldName, const string& newName)
{
    treeViewJoints->renameTreeWidgetItem(oldName, newName);
}

void AddNewJoint::updateJointData(const string& name)
{
    treeViewJoints->updateEditWidget((BaseEntity*)_cor3d->get_skeleton()->get_joint(name));
}

void AddNewJoint::populateTreeViewJoints(Skeleton* skeleton, Joint* parent)
{
    for (unsigned int i = 0; i < parent->get_children().size(); i++)
    {
        Joint* joint = skeleton->get_joint(parent->get_children()[i]);
        addJoint(joint->get_name());
        populateTreeViewJoints(skeleton, joint);
    }
}

void AddNewJoint::update_content()
{
    QTreeWidgetItem* rootItem = treeViewJoints->topLevelItem(0);
    if (rootItem)
    {
        string oldRootName = rootItem->data(0, Qt::UserRole).toString().toStdString();
        deleteJoint(oldRootName);
    }

    Skeleton* skeleton = _cor3d->get_skeleton();
    if (skeleton)
    {
        Joint* root = skeleton->get_joint(0);
        EditableDeletableListItem* listItem = new EditableDeletableListItem(root->get_name(), new EditJoint(), treeViewJoints);
        connect(listItem, SIGNAL(view_list_item_renamed(string,string)), this, SIGNAL(view_joint_renamed(string, string)));
        listItem->showEdit(false);
        listItem->showDelete(false);
        treeViewJoints->addTopLevelTreeWidgetItem(root->get_name(), listItem);

        populateTreeViewJoints(skeleton, root);

        addName->setValue(skeleton->next_joint_name());
    }
}

void AddNewJoint::selectJoint(const string& name)
{
    treeViewJoints->selectTreeWidgetItem(name);
}

void AddNewJoint::on_toolButtonAdd_clicked()
{
    QTreeWidgetItem* item = treeViewJoints->currentItem();
    if (item)
    {
        Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
        cor3dApp->cor3d->get_skeleton()->addJoint(item->data(0, Qt::UserRole).toString().toStdString(), addName->value());
        //emit view_joint_added(item->data(0, Qt::UserRole), name->value());
    }
}

void AddNewJoint::on_treeViewJoints_itemSelectionChanged()
{
    if (treeViewJoints->selectedItems().count() == 1)
    {
        emit(view_joint_selected(treeViewJoints->selectedItems()[0]->data(0, Qt::UserRole).toString().toStdString()));
    }
    else
    {
        emit(view_joint_selected(""));
    }
}

void AddNewJoint::handle_view_joint_edited(const string& name)
{
    treeViewJoints->toggleEditWidget(name);
}
