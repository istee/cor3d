#pragma once

#include <QToolButton>

class ToolButtonExtension : public QToolButton
{
    Q_OBJECT
public:
    ToolButtonExtension(QWidget* parent = 0) : QToolButton(parent)
    {
        this->setMinimumSize(QSize(30, 30));
        this->setIconSize(QSize(30, 30));
    }
};
