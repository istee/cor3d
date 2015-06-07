#pragma once

#include <QWidget>
#include <QObject>

#include "Model/Cor3d.h"
#include "Cor3dApplication.h"

class BaseSideWidget: public QWidget {
    Q_OBJECT
    QSizePolicy         _expandedPolicy;
    QSizePolicy         _collapsedPolicy;

protected:
    string              _entityName;
    Cor3d*              _cor3d;

public:
    BaseSideWidget(QWidget *parent = 0): QWidget(parent)
    {
        _cor3d = ((Cor3dApplication*) qApp)->cor3d;
        _expandedPolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        _collapsedPolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }

    virtual void updateContent(BaseEntity*)
    {

    }

protected slots:
    void handle_groupbox_toggled(bool show)
    {
        if (show)
        {
            this->setSizePolicy(_expandedPolicy);
        }
        else
        {
            this->setSizePolicy(_collapsedPolicy);
        }

        this->adjustSize();
    }
};
