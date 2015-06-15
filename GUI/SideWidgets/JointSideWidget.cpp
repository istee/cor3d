#include "JointSideWidget.h"

#include <QTreeWidgetItem>

#include "Cor3dApplication.h"
#include "Model/Cor3d.h"
#include "StdExtension.h"
#include "GUI/BasicWidgets/BaseEntityListItem.h"
#include "GUI/EditWidgets/JointEditWidget.h"

using namespace std;
using namespace cor3d;

JointSideWidget::JointSideWidget(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    addName->setLabel("Name");
    addName->setEnabled(false);
    addName->setLabel("New joint name: ");
    addName->setToolTip("Add new joint with the specified name");

    connect(groupBox, SIGNAL(groupboxToggled(bool)), this, SLOT(handle_groupboxToggled(bool)));
    connect(addName, SIGNAL(baseEntityAdded(string)), this, SLOT(handleViewJointAdded(string)));
}

void JointSideWidget::addJoint(Skeleton* skeleton, Joint* joint, const string& parentName)
{

    JointEditWidget* editJoint = new JointEditWidget(skeleton, joint, treeViewJoints);
    BaseEntityListItem* listItem = new BaseEntityListItem(joint->getName(), editJoint, treeViewJoints);
    listItem->addRenameToolButton();
    listItem->addEditToolButton();
    listItem->addDeleteToolButton();
    connect(listItem, SIGNAL(viewListItemDeleted(string)), skeleton, SLOT(handleViewJointDeleted(string)));
    connect(listItem, SIGNAL(viewListItemRenamed(string,string)), skeleton, SLOT(handleViewJointRenamed(string, string)));
    connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewJointEditWidgetToggled(string)));

    treeViewJoints->addTreeWidgetItem(parentName, joint->getName(), listItem);

    QTreeWidgetItem* parentItem = treeViewJoints->getTreeWidgetItemByData(parentName);
    if (parentItem->childCount() == 1)
    {
        BaseEntityListItem* parentListItem = (BaseEntityListItem*) treeViewJoints->itemWidget(parentItem, 0);
        parentListItem->addMirrorToolButton();
        connect(parentListItem, SIGNAL(viewListItemMirrored(string)), skeleton, SLOT(handleViewJointMirrored(string)));
    }
    if (parentItem->childCount() > 1)
    {
        BaseEntityListItem* parentListItem = (BaseEntityListItem*) treeViewJoints->itemWidget(parentItem, 0);
        parentListItem->deleteMirrorToolButton();
    }

    addName->setValue(skeleton->nextAutoJointName());
}

void JointSideWidget::deleteJoint(const string& name)
{
    QTreeWidgetItem* item = treeViewJoints->getTreeWidgetItemByData(name);
    if (item->parent())
    {
        if (item->parent()->childCount() == 1)
        {
            BaseEntityListItem* parentListItem = (BaseEntityListItem*) treeViewJoints->itemWidget(item->parent(), 0);
            parentListItem->deleteMirrorToolButton();
        }
        if (item->parent()->childCount() == 1)
        {
            BaseEntityListItem* parentListItem = (BaseEntityListItem*) treeViewJoints->itemWidget(item->parent(), 0);
            parentListItem->deleteMirrorToolButton();
        }
        treeViewJoints->deleteTreeWidgetItemByData(item->parent()->data(0, Qt::UserRole).toString().toStdString(), name);
    }
    else
    {
        treeViewJoints->deleteTopLevelTreeWidgetItemByData(name);
    }
}

void JointSideWidget::renameJoint(const string& oldName, const string& newName)
{
    treeViewJoints->renameTreeWidgetItem(oldName, newName);
}

void JointSideWidget::updateJointData(Joint* joint)
{
    treeViewJoints->updateEditWidget(joint);
}

void JointSideWidget::populateTreeViewJoints(Skeleton* skeleton, Joint* parent)
{
    for (unsigned int i = 0; i < parent->get_children().size(); i++)
    {
        Joint* joint = skeleton->getJointById(parent->get_children()[i]);
        addJoint(skeleton, joint, parent->getName());
        populateTreeViewJoints(skeleton, joint);
    }
}

void JointSideWidget::populateJoints(Skeleton* skeleton, Skeleton* previous)
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
        JointEditWidget* editJoint = new JointEditWidget(skeleton, root, treeViewJoints);
        BaseEntityListItem* listItem = new BaseEntityListItem(root->getName(), editJoint, treeViewJoints);
        listItem->addRenameToolButton();

        connect(this, SIGNAL(viewJointAdded(string, string)), skeleton, SLOT(handleViewJointAdded(string,string)));
        connect(this, SIGNAL(viewJointSelected(string)), skeleton, SLOT(handleViewJointSelected(string)));
        connect(listItem, SIGNAL(viewListItemDeleted(string)), skeleton, SLOT(handleViewJointDeleted(string)));
        connect(listItem, SIGNAL(viewListItemRenamed(string,string)), skeleton, SLOT(handleViewJointRenamed(string, string)));
        connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewJointEditWidgetToggled(string)));

        treeViewJoints->addTopLevelTreeWidgetItem(root->getName(), listItem);


        populateTreeViewJoints(skeleton, root);

        addName->setEnabled(true);
        addName->setValue(skeleton->nextAutoJointName());
    }
}

void JointSideWidget::selectJoint(const string& name)
{
    treeViewJoints->selectTreeWidgetItem(name);
}

void JointSideWidget::handleViewJointAdded(const string& name)
{
    QTreeWidgetItem* item = treeViewJoints->currentItem();
    if (item)
    {
        emit viewJointAdded(name, item->data(0, Qt::UserRole).toString().toStdString());
    }
}

void JointSideWidget::on_treeViewJoints_itemSelectionChanged()
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

void JointSideWidget::handleViewJointEditWidgetToggled(const string& name)
{
    treeViewJoints->toggleEditWidget(name);
}
