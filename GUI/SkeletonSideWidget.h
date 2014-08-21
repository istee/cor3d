#pragma once

#include <QWidget>
#include "ui_SkeletonSideWidget.h"

class SkeletonSideWidget: public QWidget, public Ui::SkeletonSideWidget
{
    Q_OBJECT
public:
    // special and default constructor
    SkeletonSideWidget(QWidget *parent = 0);

public slots:

signals:

private slots:

};
