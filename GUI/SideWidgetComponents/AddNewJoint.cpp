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
}

void AddNewJoint::populateJointTreeView(Skeleton* skeleton, Joint* parent,QTreeWidgetItem* parentItem)
{
    vector<unsigned int> childrenIds = parent->get_children();
    for (vector<unsigned int>::iterator it = childrenIds.begin(); it != childrenIds.end(); it++)
    {
        Joint* child = skeleton->get_joint(*it);
        QTreeWidgetItem* childItem =  new QTreeWidgetItem();
        childItem->setData(0, Qt::UserRole, QVariant(QString::fromStdString(child->get_name())));
        populateJointTreeView(skeleton, child, childItem);
        parentItem->addChild(childItem);
    }
}

void AddNewJoint::addWidgetToTreeWidgetItems(QTreeWidgetItem* item)
{
    EditableDeletableListItem* listItem = new EditableDeletableListItem(item->data(0, Qt::UserRole).toString().toStdString(), new EditJoint(), treeViewJoints);
    connect(listItem, SIGNAL(view_list_item_renamed(string,string)), this, SIGNAL(view_joint_renamed(string, string)));
    connect(listItem, SIGNAL(view_list_item_deleted(string)), this, SIGNAL(view_joint_deleted(const string&)));
    treeViewJoints->setItemWidget(item, 0, listItem);

    for( int i = 0; i < item->childCount(); ++i )
            addWidgetToTreeWidgetItems(item->child(i));
}

void AddNewJoint::addJoint(const string& name)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton* skeleton = cor3dApp->cor3d->get_skeleton();
    unsigned int jointId = skeleton->getJointIdByName(name);
    Joint* joint = skeleton->get_joint(jointId);

    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setData(0, Qt::UserRole, QVariant(QString::fromStdString(name)));
    Joint* parent = skeleton->get_joint(joint->get_parent());
    QTreeWidgetItem* parentItem = treeViewJoints->getTreeWidgetItemByData(parent->get_name());
    parentItem->addChild(item);

    EditableDeletableListItem* listItem = new EditableDeletableListItem(item->data(0, Qt::UserRole).toString().toStdString(), new EditJoint(), treeViewJoints);
    connect(listItem, SIGNAL(view_list_item_renamed(string,string)), this, SIGNAL(view_joint_renamed(string, string)));
    connect(listItem, SIGNAL(view_list_item_deleted(string)), this, SIGNAL(view_joint_deleted(const string&)));
    treeViewJoints->setItemWidget(item, 0, listItem);
    parentItem->setExpanded(true);

    addName->setValue(skeleton->next_joint_name());
}

void AddNewJoint::deleteJoint(const string& name)
{
    QTreeWidgetItem* item = treeViewJoints->getTreeWidgetItemByData(name);
    delete item;
}

void AddNewJoint::renameJoint(const string& oldName, const string& newName)
{
    QTreeWidgetItem* item = treeViewJoints->getTreeWidgetItemByData(oldName);
    item->setData(0, Qt::UserRole, QVariant(QString::fromStdString(newName)));
    EditableDeletableListItem* itemWidget = (EditableDeletableListItem*) treeViewJoints->itemWidget(item, 0);
    itemWidget->setLabelText(newName);
}

void AddNewJoint::update_content()
{
    cout << "update_content joint" << endl;

    this->setEnabled(false);

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton* skeleton = cor3dApp->cor3d->get_skeleton();

    treeViewJoints->clear();

    if (skeleton)
    {
        this->setEnabled(true);
        Joint* root = skeleton->get_joint(0);
        QTreeWidgetItem* rootItem = new QTreeWidgetItem();
        rootItem->setData(0, Qt::UserRole, QVariant(QString::fromStdString(root->get_name())));
        populateJointTreeView(skeleton, root, rootItem);
        treeViewJoints->addTopLevelItem(rootItem);

        QModelIndexList indexes = treeViewJoints->model()->match(treeViewJoints->model()->index(0,0), Qt::DisplayRole, "*", -1, Qt::MatchWildcard|Qt::MatchRecursive);
        foreach (QModelIndex index, indexes)
        {
            treeViewJoints->expand(index);
        }

        addWidgetToTreeWidgetItems(treeViewJoints->invisibleRootItem()->child(0));

        addName->setValue(skeleton->next_joint_name());
    }
}

void AddNewJoint::selectJoint(const string& name)
{
    QTreeWidgetItem* item = treeViewJoints->currentItem();
    if (item)
    {
        string value = item->data(0, Qt::UserRole).toString().toStdString();
        if (name != value)
        {
            item = treeViewJoints->getTreeWidgetItemByData(name);
            if (item)
            {
                treeViewJoints->setCurrentItem(item);
            }
            else
            {
                item = treeViewJoints->currentItem();
                treeViewJoints->setCurrentItem(item, 0, QItemSelectionModel::Deselect);
            }
        }
    }
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
