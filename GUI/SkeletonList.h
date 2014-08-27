#pragma once

#include <QWidget>
#include <string>
#include "ui_SkeletonList.h"

using namespace std;

class SkeletonList: public QWidget, public Ui::SkeletonList
{
    Q_OBJECT
public:
    // special and default constructor
    SkeletonList(QWidget *parent = 0);
    void update_content();

public slots:

signals:
    void skeleton_deleted();
    void skeleton_selected(const string& name);

private slots:

private slots:
    void on_skeleton_listview_clicked(QModelIndex index);
    void on_skeleton_listview_activated(QModelIndex index);
    void on_delete_button_released();
};
