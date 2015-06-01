#pragma once

#include <QWidget>
#include <QObject>

#include "Cor3dApplication.h"

class BaseSideWidget: public QWidget {
    Q_OBJECT
    Cor3dApplication    *cor3dApp;
public:
    BaseSideWidget(QWidget *parent = 0): QWidget(parent) { cor3dApp = (Cor3dApplication*) qApp; }
    virtual void update_content() = 0;
    virtual void updateContent(BaseEntity*)
    {

    }
};
