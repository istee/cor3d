#include "SkeletonSideWidget.h"

#include <iostream>
#include <QStringListModel>
#include <QFileDialog>
#include <QToolButton>
#include <QStandardItem>
#include <QLabel>
#include <QListWidget>

#include <Cor3dApplication.h>

#include "Model/Cor3d.h"
#include "Model/BaseEntity.h"
#include "GUI/BasicWidgets/BaseEntityListItem.h"
#include "GUI/EditWidgets/SkeletonEditWidget.h"
#include "GUI/BasicWidgets/BaseEntityListItem.h"

using namespace std;
using namespace cor3d;

SkeletonSideWidget::SkeletonSideWidget(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    addName->setLabel("Name");
    //skeleton_listview->setSelectionBehavior(QAbstractItemView::SelectItems);

    connect(groupBox, SIGNAL(groupboxToggled(bool)), this, SLOT(handle_groupboxToggled(bool)));
    connect(addName, SIGNAL(baseEntityAdded(string)), this, SLOT(handleViewSkeletonAdded(string)));

    addName->setValue(_cor3d->nextName());
}

void SkeletonSideWidget::addSkeleton(Skeleton* skeleton)
{
    SkeletonEditWidget* listItemWidget = new SkeletonEditWidget(skeleton, skeleton_listview);
    listItemWidget->updateContent(skeleton);

    BaseEntityListItem* listItem = new BaseEntityListItem(skeleton->getName(), listItemWidget, skeleton_listview);
    listItem->addRenameToolButton();
    listItem->addEditToolButton();
    listItem->addDeleteToolButton();
    connect(listItem, SIGNAL(viewListItemDeleted(string)), this, SIGNAL(viewSkeletonDeleted(const string&)));
    connect(listItem, SIGNAL(viewListItemRenamed(string,string)), this, SIGNAL(viewSkeletonRenamed(string,string)));
    connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewSkeletonEdited(string)));

    skeleton_listview->addListWigetItem(skeleton->getName(), listItem);

    addName->setValue(_cor3d->nextName());
}

void SkeletonSideWidget::deleteSkeleton(const string& name)
{
    skeleton_listview->deleteListWidgetItemByData(name);
    addName->setValue(_cor3d->nextName());
}

void SkeletonSideWidget::renameSkeleton(const string& oldName, const string& newName)
{
    skeleton_listview->renameListWidgetItem(oldName, newName);
}

void SkeletonSideWidget::updateSkeletonModel(Skeleton* skeleton)
{
    skeleton_listview->updateEditWidget(skeleton);
}

void SkeletonSideWidget::selectSkeleton(const string& name)
{
    skeleton_listview->selectListWidgetItem(name);
}

void SkeletonSideWidget::handleViewSkeletonEdited(const string& name)
{
    skeleton_listview->toggleEditWidget(name);
}

void SkeletonSideWidget::handleViewSkeletonAdded(const string& name)
{
    emit viewSkeletonAdded(name);
}

void SkeletonSideWidget::on_skeleton_listview_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if (current)
    {
        emit viewSkeletonSelected(current->data(Qt::UserRole).toString().toStdString());
    }
}

void SkeletonSideWidget::handleModelSkeletonDataChanged(Skeleton* skeleton)
{
    if (skeleton)
    {
        skeleton_listview->updateEditWidget(skeleton);
        /*
        QListWidgetItem item = skeleton_listview->getListWidgetItemByData(skeleton->getName());
        BaseEntityListItem* listItem = (BaseEntityListItem*) skeleton_listview->itemWidget(item);
        BaseEditWidget* editWidget = listItem->editWidget();
        editWidget->updateContent(skeleon);
        */
    }
}
