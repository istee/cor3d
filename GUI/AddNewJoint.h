#pragma once

#include <QWidget>
#include <string>
#include "ui_AddNewJoint.h"

using namespace std;

class AddNewJoint: public QWidget, public Ui::AddNewJoint
{
    Q_OBJECT
public:
    // special and default constructor
    AddNewJoint(QWidget *parent = 0);
    void update_content();

public slots:

signals:
    void joint_added(const string& name, int parent_id);

private slots:
    void on_add_new_joint_button_released();
};
