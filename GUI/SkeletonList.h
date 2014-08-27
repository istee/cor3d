#pragma once

#include <QWidget>
<<<<<<< HEAD
#include <string>
#include "ui_SkeletonList.h"

using namespace std;

=======
#include "ui_SkeletonList.h"

>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
class SkeletonList: public QWidget, public Ui::SkeletonList
{
    Q_OBJECT
public:
    // special and default constructor
    SkeletonList(QWidget *parent = 0);
<<<<<<< HEAD
    void update_content();
=======
    void update_list();
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa

public slots:

signals:
<<<<<<< HEAD
    void skeleton_deleted();
    void skeleton_selected(const string& name);

private slots:

private slots:
    void on_skeleton_listview_clicked(QModelIndex index);
    void on_skeleton_listview_activated(QModelIndex index);
    void on_delete_button_released();
=======

private slots:
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
};
