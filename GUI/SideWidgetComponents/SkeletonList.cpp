#include "SkeletonList.h"

#include <iostream>
#include <QStringListModel>
#include <QFileDialog>
#include <QToolButton>
#include <QStandardItem>
#include <QLabel>

#include <Cor3dApplication.h>

#include "Model/Cor3d.h"
#include "Model/BaseEntity.h"
#include "GUI/BasicWidgets/EditableDeletableListItem.h"
#include "GUI/SideWidgetComponents/TransformationsWidget.h"

using namespace std;
using namespace cor3d;

SkeletonList::SkeletonList(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    addName->setLabel("Name");
    skeleton_listview->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void SkeletonList::update_content()
{
    skeleton_listview->clear();
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    const vector<BaseEntity*> skeleton_list = cor3dApp->cor3d->get_skeleton_list();
    for (vector<BaseEntity*>::const_iterator it = skeleton_list.begin(); it != skeleton_list.end(); it++)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(130, 26));
        skeleton_listview->addItem(item);
        EditableDeletableListItem* listItem = new EditableDeletableListItem((*it)->get_name(), skeleton_listview);
        connect(listItem, SIGNAL(view_list_item_deleted(string)), this, SIGNAL(view_skeleton_deleted(const string&)));
        skeleton_listview->setItemWidget(item, listItem);
    }

    addName->setValue(cor3dApp->cor3d->next_name());
}

void SkeletonList::on_skeleton_listview_clicked(QModelIndex index)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    int id = cor3dApp->cor3d->get_skeleton_id_by_name(index.data().toString().toStdString());
    emit view_skeleton_selected(id);
}

void SkeletonList::on_skeleton_listview_activated(QModelIndex index)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    int id = cor3dApp->cor3d->get_skeleton_id_by_name(index.data().toString().toStdString());
    emit view_skeleton_selected(id);
}

void SkeletonList::on_toolButtonAdd_clicked()
{
    emit view_skeleton_added(addName->value());
}
