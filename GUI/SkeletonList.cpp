#include "SkeletonList.h"

#include <iostream>
#include <QStringListModel>

#include "Model/Cor3d.h"
#include "Model/BaseEntity.h"

using namespace std;
using namespace cor3d;

SkeletonList::SkeletonList(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

void SkeletonList::update_list()
{
    QStringListModel *model;
    model = new QStringListModel(this);
    QStringList string_list;
    const vector<BaseEntity> skeleton_list = Cor3d::getInstance().get_skeleton_list();
    for (vector<BaseEntity>::const_iterator it = skeleton_list.begin(); it != skeleton_list.end(); it++)
    {
        string_list << QString::fromStdString(it->get_name());
    }
    model->setStringList(string_list);
    skeleton_listview->setModel(model);
}
