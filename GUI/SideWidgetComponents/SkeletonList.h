#pragma once

#include <QWidget>
#include <string>
#include "ui_SkeletonList.h"
#include "BaseSideWidget.h"

using namespace std;

class SkeletonList: public BaseSideWidget, public Ui::SkeletonList
{
    Q_OBJECT
public:
    // special and default constructor
    SkeletonList(QWidget *parent = 0);
    void update_content();

public slots:

signals:
    void view_skeleton_deleted();
    void view_skeleton_selected(int id);
    void view_skeleton_exported(const string& file);

private slots:
    void on_save_button_released();
    void on_skeleton_listview_clicked(QModelIndex index);
    void on_skeleton_listview_activated(QModelIndex index);
    void on_delete_button_released();
};
