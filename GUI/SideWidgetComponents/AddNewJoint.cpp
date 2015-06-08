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

void AddNewJoint::addJoint(Skeleton* skeleton, Joint* joint, const string& parentName)
{
    EditJoint* editJoint = new EditJoint(skeleton, joint, treeViewJoints);
    EditableDeletableListItem* listItem = new EditableDeletableListItem(joint->get_name(), editJoint, treeViewJoints);
    connect(listItem, SIGNAL(viewListItemDeleted(string)), skeleton, SLOT(handleViewJointDeleted(string)));
    connect(listItem, SIGNAL(viewListItemRenamed(string,string)), skeleton, SLOT(handleViewJointRenamed(string, string)));
    connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewJointEdited(string)));

    treeViewJoints->addTreeWidgetItem(parentName, joint->get_name(), listItem);

    addName->setValue(_cor3d->get_skeleton()->next_joint_name());
}

void AddNewJoint::deleteJoint(const string& name)
{
    QTreeWidgetItem* item = treeViewJoints->getTreeWidgetItemByData(name);
    if (item->parent())
    {
        treeViewJoints->deleteTreeWidgetItemByData(item->parent()->data(0, Qt::UserRole).toString().toStdString(), name);
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

void AddNewJoint::updateJointData(Joint* joint)
{
    treeViewJoints->updateEditWidget(joint);
}

void AddNewJoint::populateTreeViewJoints(Skeleton* skeleton, Joint* parent)
{
    for (unsigned int i = 0; i < parent->get_children().size(); i++)
    {
        Joint* joint = skeleton->get_joint(parent->get_children()[i]);
        addJoint(skeleton, joint, parent->get_name());
        populateTreeViewJoints(skeleton, joint);
    }
}

void AddNewJoint::populateJoints(Skeleton* skeleton, Skeleton* previous)
{
    treeViewJoints->clear();

    if (previous)
    {
        disconnect(this, SIGNAL(viewJointAdded(string, string)), previous, SLOT(handleViewJointAdded(string,string)));
        disconnect(this, SIGNAL(viewJointSelected(string)), previous, SLOT(handleViewJointSelected(string)));
    }

    if (skeleton)
    {
        Joint* root = skeleton->get_joint(0);
        EditJoint* editJoint = new EditJoint(skeleton, root, treeViewJoints);
        EditableDeletableListItem* listItem = new EditableDeletableListItem(root->get_name(), editJoint, treeViewJoints);

        connect(this, SIGNAL(viewJointAdded(string, string)), skeleton, SLOT(handleViewJointAdded(string,string)));
        connect(this, SIGNAL(viewJointSelected(string)), skeleton, SLOT(handleViewJointSelected(string)));
        connect(listItem, SIGNAL(viewListItemDeleted(string)), skeleton, SLOT(handleViewJointDeleted(string)));
        connect(listItem, SIGNAL(viewListItemRenamed(string,string)), skeleton, SLOT(handleViewJointRenamed(string, string)));
        connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewJointEdited(string)));

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
        emit viewJointAdded(addName->value(), item->data(0, Qt::UserRole).toString().toStdString());
    }
}

void AddNewJoint::on_treeViewJoints_itemSelectionChanged()
{
    if (treeViewJoints->selectedItems().count() == 1)
    {
        emit(viewJointSelected(treeViewJoints->selectedItems()[0]->data(0, Qt::UserRole).toString().toStdString()));
    }
    else
    {
        emit(viewJointSelected(""));
    }
}

void AddNewJoint::handleViewJointEdited(const string& name)
{
    treeViewJoints->toggleEditWidget(name);
}
