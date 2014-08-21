#pragma once

#include <QWidget>
#include "ui_AddNewJoint.h"

class AddNewJoint: public QWidget, public Ui::AddNewJoint
{
    Q_OBJECT
public:
    // special and default constructor
    AddNewJoint(QWidget *parent = 0);
    void update_content();

public slots:

signals:

private slots:

};
