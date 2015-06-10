#include "AddNewJoint.h"

#include <QTreeWidgetItem>

#include "Cor3dApplication.h"
#include "Model/Cor3d.h"
#include "StdExtension.h"
#include "GUI/BasicWidgets/BaseEntityListItem.h"
#include "GUI/SideWidgetComponents/EditJoint.h"

using namespace std;
using namespace cor3d;

AddNewJoint::AddNewJoint(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    addName->setLabel("Name");

    connect(groupBox, SIGNAL(groupboxToggled(bool)), this, SLOT(handle_groupboxToggled(bool)));
    connect(addName, SIGNAL(baseEntityAdded(string)), this, SLOT(handleViewJointAdded(string)));
}

void AddNewJoint::addJoint(Skeleton* skeleton, Joint* joint, const string& parentName)
{
    EditJoint* editJoint = new EditJoint(skeleton, joint, treeViewJoints);
    BaseEntityListItem* listItem = new BaseEntityListItem(joint->getName(), editJoint, treeViewJoints);
    connect(listItem, SIGNAL(viewListItemDeleted(string)), skeleton, SLOT(handleViewJointDeleted(string)));
    connect(listItem, SIGNAL(viewListItemRenamed(string,string)), skeleton, SLOT(handleViewJointRenamed(string, string)));
    connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewJointEdited(string)));

    treeViewJoints->addTreeWidgetItem(parentName, joint->getName(), listItem);

    addName->setValue(_cor3d->getSelectedSkeleton()->nextAutoJointName());
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
        Joint* joint = skeleton->getJointById(parent->get_children()[i]);
        addJoint(skeleton, joint, parent->getName());
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
        Joint* root = skeleton->getJointById(0);
        EditJoint* editJoint = new EditJoint(skeleton, root, treeViewJoints);
        BaseEntityListItem* listItem = new BaseEntityListItem(root->getName(), editJoint, treeViewJoints);

        connect(this, SIGNAL(viewJointAdded(string, string)), skeleton, SLOT(handleViewJointAdded(string,string)));
        connect(this, SIGNAL(viewJointSelected(string)), skeleton, SLOT(handleViewJointSelected(string)));
        connect(listItem, SIGNAL(viewListItemDeleted(string)), skeleton, SLOT(handleViewJointDeleted(string)));
        connect(listItem, SIGNAL(viewListItemRenamed(string,string)), skeleton, SLOT(handleViewJointRenamed(string, string)));
        connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewJointEdited(string)));

        listItem->showEdit(false);
        listItem->showDelete(false);
        treeViewJoints->addTopLevelTreeWidgetItem(root->getName(), listItem);

        populateTreeViewJoints(skeleton, root);

        addName->setValue(skeleton->nextAutoJointName());
    }
}

void AddNewJoint::selectJoint(const string& name)
{
    treeViewJoints->selectTreeWidgetItem(name);
}

void AddNewJoint::handleViewJointAdded(const string& name)
{
    QTreeWidgetItem* item = treeViewJoints->currentItem();
    if (item)
    {
        emit viewJointAdded(name, item->data(0, Qt::UserRole).toString().toStdString());
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
