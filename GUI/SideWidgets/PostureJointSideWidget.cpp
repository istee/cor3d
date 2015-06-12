#include "PostureJointSideWidget.h"

#include "GUI/BasicWidgets/BaseEntityListItem.h"
#include "GUI/EditWidgets/PostureEditWidget.h"
#include "GUI/EditWidgets/BaseEditWidget.h"

PostureJointSideWidget::PostureJointSideWidget(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    currentPosture = 0;
}

void PostureJointSideWidget::populatePostureJoints(Skeleton* skeleton, Joint* parent)
{
    for (unsigned int i = 0; i < parent->get_children().size(); i++)
    {
        Joint* joint = skeleton->getJointById(parent->get_children()[i]);
        BaseEditWidget* editPostureJoint = new PostureEditWidget(skeleton, joint, postureJointTreeWidget);
        editPostureJoint->updateContent(skeleton->getSelectedPosture());
        BaseEntityListItem* listItem = new BaseEntityListItem(joint->getName(), editPostureJoint, postureJointTreeWidget);
        connect(listItem, SIGNAL(viewListItemEdited(string)), this, SLOT(handleViewPostureJointEditWidgeted(string)));
        listItem->addEditToolButton();
        postureJointTreeWidget->addTreeWidgetItem(parent->getName(), joint->getName(), listItem);
        populatePostureJoints(skeleton, joint);
    }
}

void PostureJointSideWidget::populatePostureJoints(Skeleton* skeleton, Posture* posture)
{
    postureJointTreeWidget->clear();

    if (currentPosture)
    {
        disconnect(currentPosture, SIGNAL(modelPostureIsEdited(Posture*,bool)), this, SLOT(handleModelPostureIsEdited(Posture*, bool)));
        disconnect(this, SIGNAL(viewPostureAlgorithmTypeSelected(string)), currentPosture, SLOT(handleViewPostureAlgorithmTypeSelected(string)));
        disconnect(this, SIGNAL(viewJointSelected(string)), currentPosture, SLOT(handleViewJointSelected(string)));
        disconnect(acceptButton, SIGNAL(clicked()), currentPosture, SLOT(handleViewChangesAccepted()));
        disconnect(cancelButton, SIGNAL(clicked()), currentPosture, SLOT(handleViewChangesCanceled()));
    }

    if (skeleton)
    {
        if (posture)
        {
            unsigned int algorithmType = posture->getAlgorithmType();
            rigidRadioButton->setEnabled(true);
            fabrikRadioButton->setEnabled(true);
            if (algorithmType)
            {
                rigidRadioButton->setChecked(true);
            }
            else
            {
                fabrikRadioButton->setChecked(true);
            }

            connect(posture, SIGNAL(modelPostureIsEdited(Posture*,bool)), this, SLOT(handleModelPostureIsEdited(Posture*, bool)));
            connect(posture, SIGNAL(modelPostureDataChanged(Posture*,string)), this, SLOT(handleModelPostureDataChanged(Posture*,string)));
            connect(this, SIGNAL(viewPostureAlgorithmTypeSelected(string)), posture, SLOT(handleViewPostureAlgorithmTypeSelected(string)));
            connect(this, SIGNAL(viewJointSelected(string)), skeleton, SLOT(handleViewJointSelected(string)));
            connect(acceptButton, SIGNAL(clicked()), posture, SLOT(handleViewChangesAccepted()));
            connect(cancelButton, SIGNAL(clicked()), posture, SLOT(handleViewChangesCanceled()));

            Joint* root = skeleton->getJointById(0);
            BaseEntityListItem* listItem = new BaseEntityListItem(root->getName(), 0, postureJointTreeWidget);
            postureJointTreeWidget->addTopLevelTreeWidgetItem(root->getName(), listItem);

            populatePostureJoints(skeleton, root);

            acceptButton->setEnabled(posture->isEdited());
            cancelButton->setEnabled(posture->isEdited());
        }
        else
        {
            acceptButton->setEnabled(false);
            cancelButton->setEnabled(false);
        }
    }
}

void PostureJointSideWidget::on_postureJointTreeWidget_itemSelectionChanged()
{
    if (postureJointTreeWidget->currentItem())
    {
        emit viewJointSelected(postureJointTreeWidget->currentItem()->data(0, Qt::UserRole).toString().toStdString());
    }
    else
    {
        emit viewJointSelected("");
    }
}

void PostureJointSideWidget::selectJoint(const string& jointName)
{
    postureJointTreeWidget->selectTreeWidgetItem(jointName);
}

void PostureJointSideWidget::handleViewPostureJointEditWidgeted(const string& jointName)
{
    postureJointTreeWidget->toggleEditWidget(jointName);
}

void PostureJointSideWidget::handleModelPostureIsEdited(Posture* posture, bool isEdited)
{
    acceptButton->setEnabled(isEdited);
    cancelButton->setEnabled(isEdited);
}

void PostureJointSideWidget::updateEditWidgets(QTreeWidgetItem* parent, Posture* posture)
{
    for (int i = 0; i < parent->childCount(); i++)
    {
        QTreeWidgetItem* child = parent->child(i);
        BaseEntityListItem* listItem = (BaseEntityListItem*) postureJointTreeWidget->itemWidget(child, 0);
        listItem->editWidget()->updateContent(posture);
        updateEditWidgets(child, posture);
    }
}

void PostureJointSideWidget::handleModelPostureDataChanged(Posture* posture, const string& rootJointName)
{
    QTreeWidgetItem* item = postureJointTreeWidget->getTreeWidgetItemByData(rootJointName);
    updateEditWidgets(item, posture);
}

void PostureJointSideWidget::on_rigidRadioButton_toggled(bool checked)
{
    string algorithmType = checked ? "RIGID" : "FABRIK";
    emit viewPostureAlgorithmTypeSelected(algorithmType);
}

void PostureJointSideWidget::on_fabrikRadioButton_toggled(bool checked)
{
    string algorithmType = checked ? "FABRIK" : "RIGID";
    emit viewPostureAlgorithmTypeSelected(algorithmType);
}
