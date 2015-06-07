#include <QSignalMapper>

#include "ManagePostures.h"
#include "ui_ManagePostures.h"

#include "GUI/BasicWidgets/EditableDeletableListItem.h"

#include "GUI/SideWidgetComponents/EditJoint.h"

ManagePostures::ManagePostures(QWidget *parent) : BaseSideWidget(parent), ui(new Ui::ManagePostures)
{
    ui->setupUi(this);

    Skeleton* skeleton = _cor3d->get_skeleton();
    if (skeleton)
    {
        ui->addName->setValue(skeleton->nextAutoPostureName());
    }
}

void ManagePostures::addSkeleton(const string& name)
{
    EditableDeletableListItem* item = new EditableDeletableListItem(name, 0, ui->postureTreeWidget);
    item->showRename(false);
    item->showEdit(false);
    item->showDelete(false);
    ui->postureTreeWidget->addTopLevelTreeWidgetItem(name, item);
}

void ManagePostures::deleteSkeleton(const string& name)
{
    ui->postureTreeWidget->deleteTopLevelTreeWidgetItemByData(name);
}

void ManagePostures::renameSkeleton(const string& oldName, const string& newName)
{
    ui->postureTreeWidget->renameTreeWidgetItem(oldName, newName);
}

void ManagePostures::selectSkeleton(const string& skeletonName)
{
    ui->postureTreeWidget->selectTreeWidgetItemWithChildren(skeletonName);
    Skeleton* skeleton = _cor3d->get_skeleton();
    ui->addName->setValue(skeleton->nextAutoPostureName());
}

ManagePostures::~ManagePostures()
{
    delete ui;
}

void ManagePostures::on_postureTreeWidget_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    if (current->parent())
    {
        emit viewSkeletonSelected(current->parent()->data(0, Qt::UserRole).toString().toStdString());
        emit viewPostureSelected(current->data(0, Qt::UserRole).toString().toStdString());
    }
    else
    {
        emit viewSkeletonSelected(current->data(0, Qt::UserRole).toString().toStdString());
    }
}

void ManagePostures::on_toolButtonAdd_clicked()
{
    QTreeWidgetItem* item = ui->postureTreeWidget->currentItem();
    if (item && !item->parent())
    {
        emit viewPostureAdded(ui->addName->value());
    }
}

void ManagePostures::addPosture(Skeleton* skeleton, Posture* posture)
{
    EditableDeletableListItem* listItem = new EditableDeletableListItem(posture->get_name(), 0, ui->postureTreeWidget);
    connect(listItem, SIGNAL(view_list_item_renamed(string,string)), skeleton, SLOT(handle_view_posture_renamed(string,string)));
    connect(listItem, SIGNAL(view_list_item_deleted(string)), skeleton, SLOT(handle_view_posture_deleted(string)));

    ui->postureTreeWidget->addTreeWidgetItem(skeleton->get_name(), posture->get_name(), listItem);

    ui->addName->setValue(_cor3d->get_skeleton()->nextAutoPostureName());
}

void ManagePostures::deletePosture(const string& skeletonName, const string& postureName)
{
    QTreeWidgetItem *skeletonItem = ui->postureTreeWidget->getTopLevelTreeWidgetItemByData(skeletonName);
    QTreeWidgetItem *postureItem = ui->postureTreeWidget->getChildrenTreeWidgetItemByData(skeletonItem, postureName);
    postureItem = skeletonItem->takeChild(skeletonItem->indexOfChild(postureItem));
    delete postureItem;
}

void ManagePostures::renamePosture(const string& skeletonName, const string& oldPostureName, const string& newPostureName)
{
    QTreeWidgetItem *skeletonItem = ui->postureTreeWidget->getTopLevelTreeWidgetItemByData(skeletonName);
    QTreeWidgetItem *postureItem = ui->postureTreeWidget->getChildrenTreeWidgetItemByData(skeletonItem, oldPostureName);
    ui->postureTreeWidget->renameTreeWidgetItem(postureItem, newPostureName);
}
