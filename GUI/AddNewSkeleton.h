#pragma once

#include <QWidget>
<<<<<<< HEAD
#include <string>
#include "ui_AddNewSkeleton.h"

using namespace std;

=======
#include "ui_AddNewSkeleton.h"

>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
class AddNewSkeleton: public QWidget, public Ui::AddNewSkeleton
{
    Q_OBJECT
public:
    // special and default constructor
    AddNewSkeleton(QWidget *parent = 0);
<<<<<<< HEAD
    void update_content();

signals:
    void skeleton_added(const string& name);

private slots:
    void on_add_new_skeleton_button_released();
=======

public slots:

signals:

private slots:

>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
};
