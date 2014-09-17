#include "SkeletonList.h"

#include <iostream>
#include <QStringListModel>
#include <QFileDialog>

#include <Cor3dApplication.h>

#include "Model/Cor3d.h"
#include "Model/BaseEntity.h"

using namespace std;
using namespace cor3d;

SkeletonList::SkeletonList(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    skeleton_listview->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void SkeletonList::update_content()
{
    QStringListModel *model;
    model = new QStringListModel(this);
    QStringList string_list;
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    const vector<BaseEntity*> skeleton_list = cor3dApp->cor3d->get_skeleton_list();
    for (vector<BaseEntity*>::const_iterator it = skeleton_list.begin(); it != skeleton_list.end(); it++)
    {
        string_list << QString::fromStdString((*it)->get_name());
    }
    model->setStringList(string_list);
    skeleton_listview->setModel(model);
    Skeleton* selected_skeleton = cor3dApp->cor3d->get_skeleton();
    if (selected_skeleton)
    {
        delete_button->setEnabled(true);
        save_button->setEnabled(true);
        QModelIndex index = model->index(selected_skeleton->get_id());
        skeleton_listview->setCurrentIndex(index);
    }
    else
    {
        delete_button->setEnabled(false);
        save_button->setEnabled(false);
    }

}

void SkeletonList::on_delete_button_released()
{
    emit view_skeleton_deleted();
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

void SkeletonList::on_save_button_released()
{
    string file_name = QFileDialog::getSaveFileName(this,tr("Export skeleton"), "", tr("SK File (*.sk)")).toStdString();
    emit view_skeleton_exported(file_name);
}
