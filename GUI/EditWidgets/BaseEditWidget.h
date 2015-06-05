#pragma once

#include <QWidget>

#include <string>

#include <Model/BaseEntity.h>

using namespace std;
using namespace cor3d;

class BaseEditWidget: public QWidget
{
    Q_OBJECT
protected:
    string              _entityName;

public:
    BaseEditWidget(QWidget* parent);
    void setEntityName(const string& entityName);
    virtual void updateContent(BaseEntity*) = 0;
};
