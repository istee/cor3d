#include "EditPosture.h"
#include "ui_EditPosture.h"

#include "GUI/BasicWidgets/EditableDeletableListItem.h"

EditPosture::EditPosture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditPosture)
{
    ui->setupUi(this);
}

void EditPosture::populatePostureJoints(Skeleton* skeleton, Joint* parent)
{
    for (unsigned int i = 0; i < parent->get_children().size(); i++)
    {
        Joint* joint = skeleton->get_joint(parent->get_children()[i]);
        //EditJoint* editJoint = new EditJoint(skeleton, joint, treeViewJoints);
        EditableDeletableListItem* listItem = new EditableDeletableListItem(joint->get_name(), 0, ui->postureJointTreeWidget);
        listItem->showRename(false);
        listItem->showEdit(false);
        listItem->showDelete(false);
        ui->postureJointTreeWidget->addTreeWidgetItem(parent->get_name(), joint->get_name(), listItem);
        populatePostureJoints(skeleton, joint);
    }
}

void EditPosture::populatePostureJoints(Skeleton* skeleton, Posture* posture)
{
    ui->postureJointTreeWidget->clear();

    if (skeleton)
    {
        if (posture)
        {
            Joint* root = skeleton->get_joint(0);
            //EditJoint* editJoint = new EditJoint(skeleton, root, treeViewJoints);
            EditableDeletableListItem* listItem = new EditableDeletableListItem(root->get_name(), 0, ui->postureJointTreeWidget);
            listItem->showRename(false);
            listItem->showEdit(false);
            listItem->showDelete(false);
            ui->postureJointTreeWidget->addTopLevelTreeWidgetItem(root->get_name(), listItem);

            populatePostureJoints(skeleton, root);
        }
    }
}

EditPosture::~EditPosture()
{
    delete ui;
}

void EditPosture::on_postureJointTreeWidget_itemSelectionChanged()
{
}
