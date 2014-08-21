#pragma once

#include <QWidget>
#include "ui_EditSkeleton.h"

class EditSkeleton: public QWidget, public Ui::EditSkeleton
{
    Q_OBJECT

    void enable_edits();
    void disable_edits();
public:
    // special and default constructor
    EditSkeleton(QWidget *parent = 0);
    void update();

public slots:

signals:

private slots:

};
