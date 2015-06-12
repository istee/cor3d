#include <QSignalMapper>

#include "PostureSideWidget.h"

#include "GUI/BasicWidgets/BaseEntityListItem.h"

#include "GUI/EditWidgets/JointEditWidget.h"

PostureSideWidget::PostureSideWidget(QWidget *parent) : BaseSideWidget(parent)
{
    setupUi(this);
    addName->setLabel("Name");

    connect(addName, SIGNAL(baseEntityAdded(string)), this, SLOT(handleViewPostureAdded(string)));
}

void PostureSideWidget::populatePostureList(Skeleton* skeleton)
{
    postureList->clear();
    for (unsigned int i = 0; i < skeleton->getPostureCount(); i++)
    {
        Posture* posture = skeleton->getPostureById(i);
        addPosture(skeleton, posture);
    }
    if (skeleton->getSelectedPosture())
    {
        selectPosture(skeleton, skeleton->getSelectedPosture());
    }
    addName->setValue(skeleton->nextAutoPostureName());
}

void PostureSideWidget::handleViewPostureAdded(const string& name)
{
    emit viewPostureAdded(name);
}

void PostureSideWidget::addPosture(Skeleton* skeleton, Posture* posture)
{
    BaseEntityListItem* listItem = new BaseEntityListItem(posture->getName(), 0, postureList);
    connect(listItem, SIGNAL(viewListItemDeleted(string)), skeleton, SLOT(handleViewPostureDeleted(string)));
    connect(listItem, SIGNAL(viewListItemRenamed(string,string)), skeleton, SLOT(handleViewPostureRenamed(string,string)));
    listItem->addRenameToolButton();
    listItem->addDeleteToolButton();
    postureList->addListWigetItem(posture->getName(), listItem);
    addName->setValue(skeleton->nextAutoPostureName());
}

void PostureSideWidget::deletePosture(Skeleton* skeleton, const string& postureName)
{
    postureList->deleteListWidgetItemByData(postureName);
    addName->setValue(skeleton->nextAutoPostureName());
}

void PostureSideWidget::renamePosture(const string& oldPostureName, const string& newPostureName)
{
    postureList->renameListWidgetItem(oldPostureName, newPostureName);
}

void PostureSideWidget::selectPosture(Skeleton* skeleton, Posture* posture)
{
    postureList->selectListWidgetItem(posture->getName());
}


void PostureSideWidget::on_postureList_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if (current)
    {
        emit viewPostureSelected(current->data(Qt::UserRole).toString().toStdString());
    }
}
