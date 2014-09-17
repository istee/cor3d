#pragma once

#include <QWidget>
#include <string>
#include "ui_AddNewSkeleton.h"
#include "BaseSideWidget.h"

using namespace std;

class AddNewSkeleton: public BaseSideWidget, public Ui::AddNewSkeleton
{
    Q_OBJECT
public:
    // special and default constructor
    AddNewSkeleton(QWidget *parent = 0);
    void update_content();

signals:
    void view_skeleton_added(const string& name);
    void view_skeleton_imported(const string& file_name);

private slots:
    void on_pushButton_released();
    void on_add_new_skeleton_button_released();

};
