#include "ManagePostures.h"
#include "ui_ManagePostures.h"

#include "GUI/BasicWidgets/EditableDeletableListItem.h"

#include "GUI/SideWidgetComponents/EditJoint.h"

ManagePostures::ManagePostures(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagePostures)
{
    ui->setupUi(this);
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
    ui->postureTreeWidget->selectTreeWidgetItem(skeletonName);
}

ManagePostures::~ManagePostures()
{
    delete ui;
}

void ManagePostures::on_postureTreeWidget_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    if (!current->parent() && !previous->parent())
    {
        emit viewSkeletonSelected(current->data(0, Qt::UserRole).toString().toStdString());
    }

    /*
    if (!current->parent())
    {
        emit viewSkeletonSelected(current->data(0, Qt::UserRole).toString().toStdString());
    }
    else
    {
        emit viewSkeletonSelected(current->parent()->data(0, Qt::UserRole).toString().toStdString());

    }
    */
}
