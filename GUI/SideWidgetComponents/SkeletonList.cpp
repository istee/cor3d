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
#include "GUI/BasicWidgets/EditableDeletableListItem.h"
#include "GUI/SideWidgetComponents/TransformationsWidget.h"
#include "GUI/SideWidgetComponents/EditSkeleton.h"

using namespace std;
using namespace cor3d;

SkeletonList::SkeletonList(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    addName->setLabel("Name");
    skeleton_listview->setSelectionBehavior(QAbstractItemView::SelectItems);

    _skeletonDisplayProperties = QHash<string,BaseEntityDisplayProperties>();
}

void SkeletonList::update_content()
{
    //skeleton_listview->clear();
    QList<string> currentSkeletonList = QList<string>();
    for(int row = 0; row < skeleton_listview->count(); row++)
    {
             QListWidgetItem *item = skeleton_listview->item(row);
             EditableDeletableListItem* listItem = (EditableDeletableListItem*)skeleton_listview->itemWidget(item);
             currentSkeletonList.push_back(listItem->labelText());
    }


    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    const vector<BaseEntity*> skeleton_list = cor3dApp->cor3d->get_skeleton_list();
    for (vector<BaseEntity*>::const_iterator it = skeleton_list.begin(); it != skeleton_list.end(); it++)
    {
        if (currentSkeletonList.indexOf((*it)->get_name()) == -1)
        {
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString((*it)->get_name()));
            QFont f;
            f.setPointSize(1);
            item->setFont(f);
            item->setSizeHint(QSize(130, 40));
            skeleton_listview->addItem(item);

            EditSkeleton* listItemWidget = new EditSkeleton();
            connect(listItemWidget, SIGNAL(view_skeleton_model_changed(string,string)), this, SIGNAL(view_skeleton_model_changed(string,string)));
            connect(listItemWidget, SIGNAL(view_skeleton_model_offset_changed(string,DCoordinate3)), this, SIGNAL(view_skeleton_model_offset_changed(string,DCoordinate3)));
            connect(listItemWidget, SIGNAL(view_skeleton_model_scale_changed(string,DCoordinate3)), this, SIGNAL(view_skeleton_model_scale_changed(string,DCoordinate3)));
            listItemWidget->updateContent(*it);

            EditableDeletableListItem* listItem = new EditableDeletableListItem((*it)->get_name(), listItemWidget, skeleton_listview);
            connect(listItem, SIGNAL(view_list_item_deleted(string)), this, SIGNAL(view_skeleton_deleted(const string&)));
            connect(listItem, SIGNAL(view_list_item_renamed(string,string)), this, SIGNAL(view_skeleton_renamed(string,string)));
            connect(listItem, SIGNAL(view_list_item_edited(string)), this, SLOT(handle_view_skeleton_edited(string)));

            skeleton_listview->setItemWidget(item, listItem);
        }
        else
        {
            QList<QListWidgetItem *> items = skeleton_listview->findItems(QString::fromStdString((*it)->get_name()), Qt::MatchExactly);
            if (items.size() == 1) {
                EditableDeletableListItem* listItem = (EditableDeletableListItem*)skeleton_listview->itemWidget(items[0]);
                listItem->editWidget()->updateContent(*it);
                currentSkeletonList.removeOne((*it)->get_name());
            }
        }
    }

    for(int i = 0; i < currentSkeletonList.count(); i++)
    {
        QList<QListWidgetItem *> items = skeleton_listview->findItems(QString::fromStdString(currentSkeletonList.at(i)), Qt::MatchExactly);
        int row = items[0]->listWidget()->row(items[0]);
        QListWidgetItem* item = skeleton_listview->takeItem(row);
        delete item;
    }

    Skeleton* selected = cor3dApp->cor3d->get_skeleton();
    if (selected)
    {
        skeleton_listview->setCurrentIndex(skeleton_listview->model()->index(selected->get_id(), 0));
    }

    addName->setValue(cor3dApp->cor3d->next_name());
}

void SkeletonList::updateSkeletonModel(const string& skeletonName)
{
    cout << "update skeleton model: " << skeletonName << endl;
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    QList<QListWidgetItem *> items = skeleton_listview->findItems(QString::fromStdString(skeletonName), Qt::MatchExactly);
    if (items.size() == 1) {
        EditableDeletableListItem* listItem = (EditableDeletableListItem*)skeleton_listview->itemWidget(items[0]);
        listItem->editWidget()->updateContent(cor3dApp->cor3d->getSkeletonById(cor3dApp->cor3d->get_skeleton_id_by_name(skeletonName)));
    }
}

void SkeletonList::on_skeleton_listview_clicked(QModelIndex index)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    QListWidgetItem* item = skeleton_listview->item(index.row());
    EditableDeletableListItem* widget = (EditableDeletableListItem*)(skeleton_listview->itemWidget(item));
    int id = cor3dApp->cor3d->get_skeleton_id_by_name(widget->labelText());
    emit view_skeleton_selected(id);
}

void SkeletonList::on_skeleton_listview_activated(QModelIndex index)
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    QListWidgetItem* item = skeleton_listview->item(index.row());
    EditableDeletableListItem* widget = (EditableDeletableListItem*)(skeleton_listview->itemWidget(item));
    int id = cor3dApp->cor3d->get_skeleton_id_by_name(widget->labelText());
    emit view_skeleton_selected(id);
}

void SkeletonList::handle_view_skeleton_edited(const string& name)
{
    QList<QListWidgetItem *> items = skeleton_listview->findItems(QString::fromStdString(name), Qt::MatchExactly);
    if (items.size() == 1) {
        EditableDeletableListItem* listItem = (EditableDeletableListItem*)skeleton_listview->itemWidget(items[0]);
        listItem->showEditWidget(!listItem->isEditWidgetVisible());
        items[0]->setSizeHint(listItem->sizeHint());
    }


    //EditSkeleton* editSkeletonWidget = new EditSkeleton();
    //listItem->addEditWidget(editSkeletonWidget);
    //int count = skeleton_listview->count();
    //for(int i = 0; i < count; i++)
    //{
      //QListWidgetItem *item = skeleton_listview->item(i);
      //item->setSizeHint(QSize(item->sizeHint().width(), editSkeletonWidget->height() + 30));
    //}
}

void SkeletonList::on_toolButtonAdd_clicked()
{
    emit view_skeleton_added(addName->value());
}
