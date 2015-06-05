#include "BaseEditWidget.h"

BaseEditWidget::BaseEditWidget(QWidget *parent = 0): QWidget(parent)
{
}

void BaseEditWidget::setEntityName(const string& entityName)
{
    _entityName = entityName;
}
