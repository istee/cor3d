#pragma once

#include <QWidget>
#include "ui_SkeletonList.h"

class SkeletonList: public QWidget, public Ui::SkeletonList
{
    Q_OBJECT
public:
    // special and default constructor
    SkeletonList(QWidget *parent = 0);
    void update_list();

public slots:

signals:

private slots:
};
