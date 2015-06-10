#include "SkeletonList.h"

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
#include "GUI/SideWidgetComponents/EditSkeleton.h"

using namespace std;
using namespace cor3d;

SkeletonList::SkeletonList(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    addName->setLabel("Name");
    //skeleton_listview->setSelectionBehavior(QAbstractItemView::SelectItems);

    connect(groupBox, SIGNAL(groupboxToggled(bool)), this, SLOT(handle_groupboxToggled(bool)));
    connect(addName, SIGNAL(baseEntityAdded(string)), this, SLOT(handleViewSkeletonAdded(string)));

    addName->setValue(_cor3d->nextName());
}

void SkeletonList::addSkeleton(Skeleton* skeleton)
{
    EditSkeleton* listItemWidget = new EditSkeleton();
    connect(listItemWidget, SIGNAL(viewSkeletonModelChanged(string)), skeleton, SLOT(handleViewSkeletonModelChanged(string)));
    connect(listItemWidget, SIGNAL(viewSkeletonModelOffsetChanged(DCoordinate3)), skeleton, SLOT(handleViewSkeletonModelOffsetChanged(DCoordinate3)));
    connect(listItemWidget, SIGNAL(viewSkeletonModelScaleChanged(DCoordinate3)), skeleton, SLOT(handleViewSkeletonModelScaleChanged(DCoordinate3)));
    listItemWidget->updateContent(skeleton);

    BaseEntityListItem* listItem = new BaseEntityListItem(skeleton->getName(), listItemWidget, skeleton_listview);
    connect(listItem, SIGNAL(viewListItemDeleted(string)), this, SIGNAL(viewSkeletonDeleted(const string&)));
    connect(listItem, SIGNAL(viewListItemRenamed(string,string)), this, SIGNAL(viewSkeletonRenamed(string,string)));
    connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewSkeletonEdited(string)));

    skeleton_listview->addListWigetItem(skeleton->getName(), listItem);

    addName->setValue(_cor3d->nextName());
}

void SkeletonList::deleteSkeleton(const string& name)
{
    skeleton_listview->deleteListWidgetItemByData(name);
    addName->setValue(_cor3d->nextName());
}

void SkeletonList::renameSkeleton(const string& oldName, const string& newName)
{
    skeleton_listview->renameListWidgetItem(oldName, newName);
}

void SkeletonList::updateSkeletonModel(Skeleton* skeleton)
{
    skeleton_listview->updateEditWidget(skeleton);
}

void SkeletonList::selectSkeleton(const string& name)
{
    skeleton_listview->selectListWidgetItem(name);
}

void SkeletonList::handleViewSkeletonEdited(const string& name)
{
    skeleton_listview->toggleEditWidget(name);
}

void SkeletonList::handleViewSkeletonAdded(const string& name)
{
    emit viewSkeletonAdded(name);
}

void SkeletonList::on_skeleton_listview_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if (current)
    {
        emit viewSkeletonSelected(current->data(Qt::UserRole).toString().toStdString());
    }
}

void SkeletonList::handleModelSkeletonDataChanged(Skeleton* skeleton)
{
    updateContent(skeleton);
}
