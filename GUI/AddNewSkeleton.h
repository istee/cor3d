#pragma once

#include <QWidget>
#include "ui_AddNewSkeleton.h"

class AddNewSkeleton: public QWidget, public Ui::AddNewSkeleton
{
    Q_OBJECT
public:
    // special and default constructor
    AddNewSkeleton(QWidget *parent = 0);

public slots:

signals:

private slots:

};
