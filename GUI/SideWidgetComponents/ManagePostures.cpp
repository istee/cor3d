#include <QSignalMapper>

#include "ManagePostures.h"
#include "ui_ManagePostures.h"

#include "GUI/BasicWidgets/EditableDeletableListItem.h"

#include "GUI/SideWidgetComponents/EditJoint.h"

ManagePostures::ManagePostures(QWidget *parent) : BaseSideWidget(parent), ui(new Ui::ManagePostures)
{
    ui->setupUi(this);
}

void ManagePostures::populatePostureList(Skeleton* skeleton)
{
    ui->postureList->clear();
    for (unsigned int i = 0; i < skeleton->postureCount(); i++)
    {
        Posture* posture = skeleton->getPostureById(i);
        addPosture(skeleton, posture);
    }
    if (skeleton->selectedPosture())
    {
        selectPosture(skeleton, skeleton->selectedPosture());
    }
    ui->addName->setValue(skeleton->nextAutoPostureName());
}

ManagePostures::~ManagePostures()
{
    delete ui;
}

void ManagePostures::on_toolButtonAdd_clicked()
{
    emit viewPostureAdded(ui->addName->value());
}

void ManagePostures::addPosture(Skeleton* skeleton, Posture* posture)
{
    EditableDeletableListItem* listItem = new EditableDeletableListItem(posture->get_name(), 0, ui->postureList);
    connect(listItem, SIGNAL(viewListItemDeleted(string)), skeleton, SLOT(handleViewPostureDeleted(string)));
    connect(listItem, SIGNAL(viewListItemRenamed(string,string)), skeleton, SLOT(handleViewPostureRenamed(string,string)));
    listItem->showEdit(false);
    ui->postureList->addListWigetItem(posture->get_name(), listItem);
    ui->addName->setValue(skeleton->nextAutoPostureName());
}

void ManagePostures::deletePosture(const string& postureName)
{
    ui->postureList->deleteListWidgetItemByData(postureName);
}

void ManagePostures::renamePosture(const string& oldPostureName, const string& newPostureName)
{
    ui->postureList->renameListWidgetItem(oldPostureName, newPostureName);
}

void ManagePostures::selectPosture(Skeleton* skeleton, Posture* posture)
{
    ui->postureList->selectListWidgetItem(posture->get_name());
}


void ManagePostures::on_postureList_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if (current)
    {
        emit viewPostureSelected(current->data(Qt::UserRole).toString().toStdString());
    }
}
