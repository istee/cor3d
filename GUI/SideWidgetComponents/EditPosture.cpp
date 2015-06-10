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
        Joint* joint = skeleton->getJointById(parent->get_children()[i]);
        BaseEditWidget* editPostureJoint = new EditPostureJoint(skeleton, joint, ui->postureJointTreeWidget);
        editPostureJoint->updateContent(skeleton->getSelectedPosture());
        BaseEntityListItem* listItem = new BaseEntityListItem(joint->getName(), editPostureJoint, ui->postureJointTreeWidget);
        connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewPostureJointEdited(string)));
        listItem->showRename(false);
        listItem->showEdit(true);
        listItem->showDelete(false);
        ui->postureJointTreeWidget->addTreeWidgetItem(parent->getName(), joint->getName(), listItem);
        populatePostureJoints(skeleton, joint);
    }
}

void EditPosture::populatePostureJoints(Skeleton* skeleton, Posture* posture)
{
    ui->postureJointTreeWidget->clear();

    if (currentPosture)
    {
        disconnect(currentPosture, SIGNAL(modelPostureIsEdited(Posture*,bool)), this, SLOT(handleModelPostureIsEdited(Posture*, bool)));
        disconnect(this, SIGNAL(viewPostureAlgorithmTypeSelected(string)), currentPosture, SLOT(handleViewPostureAlgorithmTypeSelected(string)));
        disconnect(this, SIGNAL(viewJointSelected(string)), currentPosture, SLOT(handleViewJointSelected(string)));
        disconnect(ui->acceptButton, SIGNAL(clicked()), currentPosture, SLOT(handleViewChangesAccepted()));
        disconnect(ui->cancelButton, SIGNAL(clicked()), currentPosture, SLOT(handleViewChangesCanceled()));
    }

    if (skeleton)
    {
        if (posture)
        {
            unsigned int algorithmType = posture->getAlgorithmType();
            ui->rigidRadioButton->setEnabled(true);
            ui->fabrikRadioButton->setEnabled(true);
            if (algorithmType)
            {
                ui->rigidRadioButton->setChecked(true);
            }
            else
            {
                ui->fabrikRadioButton->setChecked(true);
            }

            connect(posture, SIGNAL(modelPostureIsEdited(Posture*,bool)), this, SLOT(handleModelPostureIsEdited(Posture*, bool)));
            connect(this, SIGNAL(viewPostureAlgorithmTypeSelected(string)), posture, SLOT(handleViewPostureAlgorithmTypeSelected(string)));
            connect(this, SIGNAL(viewJointSelected(string)), skeleton, SLOT(handleViewJointSelected(string)));
            connect(ui->acceptButton, SIGNAL(clicked()), posture, SLOT(handleViewChangesAccepted()));
            connect(ui->cancelButton, SIGNAL(clicked()), posture, SLOT(handleViewChangesCanceled()));

            Joint* root = skeleton->getJointById(0);
            BaseEntityListItem* listItem = new BaseEntityListItem(root->getName(), 0, ui->postureJointTreeWidget);
            listItem->showRename(false);
            listItem->showEdit(false);
            listItem->showDelete(false);
            ui->postureJointTreeWidget->addTopLevelTreeWidgetItem(root->getName(), listItem);

            populatePostureJoints(skeleton, root);

            ui->acceptButton->setEnabled(posture->isEdited());
            ui->cancelButton->setEnabled(posture->isEdited());
        }
        else
        {
            ui->acceptButton->setEnabled(false);
            ui->cancelButton->setEnabled(false);
        }
    }
}

EditPosture::~EditPosture()
{
    delete ui;
}

void EditPosture::on_postureJointTreeWidget_itemSelectionChanged()
{
    if (ui->postureJointTreeWidget->currentItem())
    {
        emit viewJointSelected(ui->postureJointTreeWidget->currentItem()->data(0, Qt::UserRole).toString().toStdString());
    }
    else
    {
        emit viewJointSelected("");
    }
}

void EditPosture::selectJoint(const string& jointName)
{
    ui->postureJointTreeWidget->selectTreeWidgetItem(jointName);
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

void EditPosture::on_rigidRadioButton_toggled(bool checked)
{
    string algorithmType = checked ? "RIGID" : "FABRIK";
    emit viewPostureAlgorithmTypeSelected(algorithmType);
}

void EditPosture::on_fabrikRadioButton_toggled(bool checked)
{
    string algorithmType = checked ? "FABRIK" : "RIGID";
    emit viewPostureAlgorithmTypeSelected(algorithmType);
}
