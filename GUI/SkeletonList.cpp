#include "SkeletonList.h"

#include <iostream>
#include <QStringListModel>

<<<<<<< HEAD
#include <Cor3dApplication.h>

=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
#include "Model/Cor3d.h"
#include "Model/BaseEntity.h"

using namespace std;
using namespace cor3d;

SkeletonList::SkeletonList(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

<<<<<<< HEAD
void SkeletonList::update_content()
=======
void SkeletonList::update_list()
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
{
    QStringListModel *model;
    model = new QStringListModel(this);
    QStringList string_list;
<<<<<<< HEAD
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    const vector<BaseEntity> skeleton_list = cor3dApp->cor3d.get_skeleton_list();
=======
    const vector<BaseEntity> skeleton_list = Cor3d::getInstance().get_skeleton_list();
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
    for (vector<BaseEntity>::const_iterator it = skeleton_list.begin(); it != skeleton_list.end(); it++)
    {
        string_list << QString::fromStdString(it->get_name());
    }
    model->setStringList(string_list);
    skeleton_listview->setModel(model);
}
<<<<<<< HEAD

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
=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
