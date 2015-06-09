#pragma once

#include <QWidget>

#include "BaseEditWidget.h"

namespace Ui {
    class EditPostureJoint;
}

class EditPostureJoint : public BaseEditWidget
{
    Q_OBJECT

public:
    explicit EditPostureJoint(QWidget *parent = 0);
    virtual void updateContent(BaseEntity*);
    ~EditPostureJoint();

private:
    Ui::EditPostureJoint *ui;
};
