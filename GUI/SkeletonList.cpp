#include "SkeletonList.h"

#include <iostream>
#include <QStringListModel>

#include <Cor3dApplication.h>

#include "Model/Cor3d.h"
#include "Model/BaseEntity.h"

using namespace std;
using namespace cor3d;

SkeletonList::SkeletonList(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

void SkeletonList::update_content()
{
    QStringListModel *model;
    model = new QStringListModel(this);
    QStringList string_list;
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    const vector<BaseEntity> skeleton_list = cor3dApp->cor3d.get_skeleton_list();
    for (vector<BaseEntity>::const_iterator it = skeleton_list.begin(); it != skeleton_list.end(); it++)
    {
        string_list << QString::fromStdString(it->get_name());
    }
    model->setStringList(string_list);
    skeleton_listview->setModel(model);
}

void SkeletonList::on_delete_button_released()
{
    emit skeleton_deleted();
}

void SkeletonList::on_skeleton_listview_activated(QModelIndex index)
{
    // this slot may be working only on other platforms than Windows
    emit skeleton_selected(index.data().toString().toStdString());
}

void SkeletonList::on_skeleton_listview_clicked(QModelIndex index)
{
    emit skeleton_selected(index.data().toString().toStdString());
}
