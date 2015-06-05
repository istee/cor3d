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
#include "GUI/SideWidgetComponents/EditSkeleton.h"

using namespace std;
using namespace cor3d;

SkeletonList::SkeletonList(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    addName->setLabel("Name");
    skeleton_listview->setSelectionBehavior(QAbstractItemView::SelectItems);

    _skeletonDisplayProperties = QHash<string,BaseEntityDisplayProperties>();

    connect(groupBox, SIGNAL(groupbox_toggled(bool)), this, SLOT(handle_groupbox_toggled(bool)));

    addName->setValue(_cor3d->next_name());
}

void SkeletonList::addSkeleton(const string& name)
{
    Skeleton* skeleton = _cor3d->getSkeletonByName(name);

    EditSkeleton* listItemWidget = new EditSkeleton();
    connect(listItemWidget, SIGNAL(view_skeleton_model_changed(string,string)), this, SIGNAL(view_skeleton_model_changed(string,string)));
    connect(listItemWidget, SIGNAL(view_skeleton_model_offset_changed(string,DCoordinate3)), this, SIGNAL(view_skeleton_model_offset_changed(string,DCoordinate3)));
    connect(listItemWidget, SIGNAL(view_skeleton_model_scale_changed(string,DCoordinate3)), this, SIGNAL(view_skeleton_model_scale_changed(string,DCoordinate3)));
    listItemWidget->updateContent(skeleton);

    EditableDeletableListItem* listItem = new EditableDeletableListItem(name, listItemWidget, skeleton_listview);
    connect(listItem, SIGNAL(view_list_item_deleted(string)), this, SIGNAL(view_skeleton_deleted(const string&)));
    connect(listItem, SIGNAL(view_list_item_renamed(string,string)), this, SIGNAL(view_skeleton_renamed(string,string)));
    connect(listItem, SIGNAL(view_list_item_edited(string)), this, SLOT(handle_view_skeleton_edited(string)));

    skeleton_listview->addListWigetItem(name, listItem);

    addName->setValue(_cor3d->next_name());
}

void SkeletonList::deleteSkeleton(const string& name)
{
    skeleton_listview->deleteListWidgetItemByData(name);
    addName->setValue(_cor3d->next_name());
}

void SkeletonList::renameSkeleton(const string& oldName, const string& newName)
{
    skeleton_listview->renameListWidgetItem(oldName, newName);
}

void SkeletonList::update_content()
{
    /*
    cout << "why the fuck are we here? " << endl;

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
        cout << *selected << endl << endl;
        skeleton_listview->setCurrentIndex(skeleton_listview->model()->index(selected->get_id(), 0));
    }

    addName->setValue(cor3dApp->cor3d->next_name());
    */
}

void SkeletonList::updateSkeletonModel(const string& skeletonName)
{
    skeleton_listview->updateEditWidget(_cor3d->getSkeletonByName(skeletonName));
}

void SkeletonList::selectSkeleton(const string& name)
{
    skeleton_listview->selectListWidgetItem(name);
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
    skeleton_listview->toggleEditWidget(name);
}

void SkeletonList::on_toolButtonAdd_clicked()
{
    emit view_skeleton_added(addName->value());
}
