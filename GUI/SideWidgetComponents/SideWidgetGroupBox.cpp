#include "SideWidgetGroupBox.h"

SideWidgetGroupBox::SideWidgetGroupBox(QWidget* parent = 0): QGroupBox(parent)
{
    this->setCheckable(true);
    _check_box_state = true;
    _sizeHint = QSize(250, 50);
    _sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    connect(this, SIGNAL(toggled(bool)), this, SLOT(my_toggled(bool)));
}

bool SideWidgetGroupBox::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::KeyRelease:
        return myKeyReleaseHandler((QKeyEvent*)e);
    case QEvent::MouseButtonRelease:
        myHandler((QMouseEvent*)e);
        return true;
    default:
        return QGroupBox::event(e);
    }
}

bool SideWidgetGroupBox::myKeyReleaseHandler(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
        return true;
    return QGroupBox::event(event);
}

void SideWidgetGroupBox::myHandler(QMouseEvent *event)
{
    QStyleOptionGroupBox box;
    initStyleOption(&box);
    QStyle::SubControl released = style()->hitTestComplexControl(QStyle::CC_GroupBox, &box,
                                                                 event->pos(), this);
    bool toggle = released == QStyle::SC_GroupBoxLabel || released == QStyle::SC_GroupBoxCheckBox;
    if (toggle)
    {
        toggled();
    }
}

void SideWidgetGroupBox::toggled()
{
    _check_box_state = !_check_box_state;
    set_content_visibility(_check_box_state);
    emit (groupbox_toggled(_check_box_state));
}

void SideWidgetGroupBox::initStyleOption(QStyleOptionGroupBox *option) const
{
    QGroupBox::initStyleOption(option);
    QStyle::State flagToSet = _check_box_state ? QStyle::State_On : QStyle::State_Off;
    QStyle::State flagToRemove = _check_box_state ? QStyle::State_Off : QStyle::State_On;

    option->state |= flagToSet;
    option->state &= ~flagToRemove;
    option->state &= ~QStyle::State_Sunken;
}

void SideWidgetGroupBox::paintEvent(QPaintEvent *)
{
    QStylePainter paint(this);
    QStyleOptionGroupBox option;
    initStyleOption(&option);
    paint.drawComplexControl(QStyle::CC_GroupBox, option);
}

void SideWidgetGroupBox::set_content_visibility(bool visible)
{
    QList<QWidget*> list = this->findChildren<QWidget*>();
    for (QList<QWidget*>::iterator it = list.begin(); it != list.end(); it++)
    {
        (*it)->setVisible(visible);
    }
}

void SideWidgetGroupBox::my_toggled(bool on)
{
    toggled();
}
