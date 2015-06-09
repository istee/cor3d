#include "EditPosture.h"
#include "ui_EditPosture.h"

#include "GUI/BasicWidgets/BaseEntityListItem.h"
#include "GUI/EditWidgets/EditPostureJoint.h"
#include "GUI/EditWidgets/BaseEditWidget.h"

EditPosture::EditPosture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditPosture)
{
    ui->setupUi(this);
    currentPosture = 0;
}

void EditPosture::populatePostureJoints(Skeleton* skeleton, Joint* parent)
{
    for (unsigned int i = 0; i < parent->get_children().size(); i++)
    {
        Joint* joint = skeleton->get_joint(parent->get_children()[i]);
        BaseEditWidget* editPostureJoint = new EditPostureJoint(ui->postureJointTreeWidget);
        BaseEntityListItem* listItem = new BaseEntityListItem(joint->get_name(), editPostureJoint, ui->postureJointTreeWidget);
        connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewPostureJointEdited(string)));
        listItem->showRename(false);
        listItem->showEdit(true);
        listItem->showDelete(false);
        ui->postureJointTreeWidget->addTreeWidgetItem(parent->get_name(), joint->get_name(), listItem);
        populatePostureJoints(skeleton, joint);
    }
}

void EditPosture::populatePostureJoints(Skeleton* skeleton, Posture* posture)
{
    ui->postureJointTreeWidget->clear();

    if (currentPosture)
    {
        disconnect(currentPosture, SIGNAL(modelPostureIsEdited(Posture*,bool)), this, SLOT(handleModelPostureIsEdited(Posture*, bool)));
        disconnect(ui->acceptButton, SIGNAL(clicked()), posture, SLOT(handleViewChangesAccepted()));
        disconnect(ui->cancelButton, SIGNAL(clicked()), posture, SLOT(handleViewChangesCanceled()));
    }

    if (skeleton)
    {
        if (posture)
        {
            connect(posture, SIGNAL(modelPostureIsEdited(Posture*,bool)), this, SLOT(handleModelPostureIsEdited(Posture*, bool)));
            connect(ui->acceptButton, SIGNAL(clicked()), posture, SLOT(handleViewChangesAccepted()));
            connect(ui->cancelButton, SIGNAL(clicked()), posture, SLOT(handleViewChangesCanceled()));

            Joint* root = skeleton->get_joint(0);
            //EditJoint* editJoint = new EditJoint(skeleton, root, treeViewJoints);
            BaseEntityListItem* listItem = new BaseEntityListItem(root->get_name(), 0, ui->postureJointTreeWidget);
            listItem->showRename(false);
            listItem->showEdit(false);
            listItem->showDelete(false);
            ui->postureJointTreeWidget->addTopLevelTreeWidgetItem(root->get_name(), listItem);

            populatePostureJoints(skeleton, root);

            ui->acceptButton->setEnabled(posture->isEdited());
            ui->cancelButton->setEnabled(posture->isEdited());
        }
        ui->acceptButton->setEnabled(false);
        ui->cancelButton->setEnabled(false);
    }
}

EditPosture::~EditPosture()
{
    delete ui;
}

void EditPosture::on_postureJointTreeWidget_itemSelectionChanged()
{
}


void EditPosture::handleViewPostureJointEdited(const string& jointName)
{
    ui->postureJointTreeWidget->toggleEditWidget(jointName);
}

void EditPosture::handleModelPostureIsEdited(Posture* posture, bool isEdited)
{
    ui->acceptButton->setEnabled(isEdited);
    ui->cancelButton->setEnabled(isEdited);
}
