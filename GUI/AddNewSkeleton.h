#pragma once

#include <QWidget>
#include <string>
#include "ui_AddNewSkeleton.h"

using namespace std;

class AddNewSkeleton: public QWidget, public Ui::AddNewSkeleton
{
    Q_OBJECT
public:
    // special and default constructor
    AddNewSkeleton(QWidget *parent = 0);
    void update_content();

signals:
    void skeleton_added(const string& name);

private slots:
    void on_add_new_skeleton_button_released();
};
