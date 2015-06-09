#include <QTreeWidget>

#include "GroupBoxExtension.h"

GroupBoxExtension::GroupBoxExtension(QWidget* parent = 0): QGroupBox(parent)
{
    this->setCheckable(true);
    _checkBoxState = true;
    _sizeHint = QSize(250, 50);
    _sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(this, SIGNAL(toggled(bool)), this, SLOT(handleToggle(bool)));
}

bool GroupBoxExtension::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::KeyRelease:
        return myKeyReleaseHandler((QKeyEvent*)e);
    case QEvent::MouseButtonRelease:
        myMouseHandler((QMouseEvent*)e);
        return true;
    default:
        return QGroupBox::event(e);
    }
}

bool GroupBoxExtension::myKeyReleaseHandler(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        toggled();
        return true;
    }
    return QGroupBox::event(event);
}

void GroupBoxExtension::myMouseHandler(QMouseEvent *event)
{
    QStyleOptionGroupBox box;
    initStyleOption(&box);
    QStyle::SubControl released = style()->hitTestComplexControl(QStyle::CC_GroupBox, &box, event->pos(), this);
    bool toggle = released == QStyle::SC_GroupBoxLabel || released == QStyle::SC_GroupBoxCheckBox;
    if (toggle)
    {
        toggled();
    }
}

void GroupBoxExtension::toggled()
{
    _checkBoxState = !_checkBoxState;
    setContentVisibility(_checkBoxState);
    emit (groupboxToggled(_checkBoxState));
}

void GroupBoxExtension::initStyleOption(QStyleOptionGroupBox *option) const
{
    QGroupBox::initStyleOption(option);
    QStyle::State flagToSet = _checkBoxState ? QStyle::State_On : QStyle::State_Off;
    QStyle::State flagToRemove = _checkBoxState ? QStyle::State_Off : QStyle::State_On;

    option->state |= flagToSet;
    option->state &= ~flagToRemove;
    option->state &= ~QStyle::State_Sunken;
}

void GroupBoxExtension::paintEvent(QPaintEvent *)
{
    QStylePainter paint(this);
    QStyleOptionGroupBox option;
    initStyleOption(&option);
    paint.drawComplexControl(QStyle::CC_GroupBox, option);
}

void GroupBoxExtension::setContentVisibility(bool visible)
{
    QList<QWidget*> list = this->findChildren<QWidget*>();
    for (QList<QWidget*>::iterator it = list.begin(); it != list.end(); it++)
    {
        (*it)->setVisible(visible);
    }
    QList<QTreeWidget*> treeWidgets = this->findChildren<QTreeWidget*>();
    for (QList<QTreeWidget*>::iterator it = treeWidgets.begin(); it != treeWidgets.end(); it++)
    {
        (*it)->setHeaderHidden(true);
    }
}

void GroupBoxExtension::handleToggle(bool on)
{
    toggled();
}
