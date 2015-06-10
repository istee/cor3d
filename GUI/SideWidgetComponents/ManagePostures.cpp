#include <QSignalMapper>

#include "ManagePostures.h"
#include "ui_ManagePostures.h"

#include "GUI/BasicWidgets/BaseEntityListItem.h"

#include "GUI/SideWidgetComponents/EditJoint.h"

ManagePostures::ManagePostures(QWidget *parent) : BaseSideWidget(parent), ui(new Ui::ManagePostures)
{
    ui->setupUi(this);
    ui->addName->setLabel("Name");

    connect(ui->addName, SIGNAL(baseEntityAdded(string)), this, SLOT(handleViewPostureAdded(string)));
}

void ManagePostures::populatePostureList(Skeleton* skeleton)
{
    ui->postureList->clear();
    for (unsigned int i = 0; i < skeleton->getPostureCount(); i++)
    {
        Posture* posture = skeleton->getPostureById(i);
        addPosture(skeleton, posture);
    }
    if (skeleton->getSelectedPosture())
    {
        selectPosture(skeleton, skeleton->getSelectedPosture());
    }
    ui->addName->setValue(skeleton->nextAutoPostureName());
}

ManagePostures::~ManagePostures()
{
    delete ui;
}

void ManagePostures::handleViewPostureAdded(const string& name)
{
    emit viewPostureAdded(name);
}

void ManagePostures::addPosture(Skeleton* skeleton, Posture* posture)
{
    BaseEntityListItem* listItem = new BaseEntityListItem(posture->getName(), 0, ui->postureList);
    connect(listItem, SIGNAL(viewListItemDeleted(string)), skeleton, SLOT(handleViewPostureDeleted(string)));
    connect(listItem, SIGNAL(viewListItemRenamed(string,string)), skeleton, SLOT(handleViewPostureRenamed(string,string)));
    listItem->showEdit(false);
    ui->postureList->addListWigetItem(posture->getName(), listItem);
    ui->addName->setValue(skeleton->nextAutoPostureName());
}

void ManagePostures::deletePosture(Skeleton* skeleton, const string& postureName)
{
    ui->postureList->deleteListWidgetItemByData(postureName);
    ui->addName->setValue(skeleton->nextAutoPostureName());
}

void ManagePostures::renamePosture(const string& oldPostureName, const string& newPostureName)
{
    ui->postureList->renameListWidgetItem(oldPostureName, newPostureName);
}

void ManagePostures::selectPosture(Skeleton* skeleton, Posture* posture)
{
    ui->postureList->selectListWidgetItem(posture->getName());
}


void ManagePostures::on_postureList_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if (current)
    {
        emit viewPostureSelected(current->data(Qt::UserRole).toString().toStdString());
    }
}
