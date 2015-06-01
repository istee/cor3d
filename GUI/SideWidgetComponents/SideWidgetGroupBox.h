#pragma once

#include <QGroupBox>
#include <QStyle>
#include <QEvent>
#include <QMouseEvent>
#include <QStyleOptionGroupBox>
#include <QStylePainter>
#include <QWidgetItem>
#include <QWidget>
#include <QList>
#include <iostream>

using namespace std;

class SideWidgetGroupBox: public QGroupBox
{
    Q_OBJECT

    bool        _check_box_state;
public:
    SideWidgetGroupBox(QWidget* parent = 0): QGroupBox(parent)
    {
        this->setCheckable(true);
        _check_box_state = true;
        connect(this, SIGNAL(toggled(bool)), this, SLOT(my_toggled(bool)));
    }

    bool event(QEvent *e)
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

    bool myKeyReleaseHandler(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Space)
            return true;
        return QGroupBox::event(event);
    }

    void myHandler(QMouseEvent *event)
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

    void toggled()
    {
        _check_box_state = !_check_box_state;
        set_content_visibility(_check_box_state);
        if (_check_box_state)
        {
            //cout << "Minimum " << sizeHint().width() << " " << sizeHint().height() << endl;
            this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        }
        else
        {
            //cout << "MinimumExpanding " << sizeHint().width() << " " << sizeHint().height() << endl;
            this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        }
        update();
        ((QWidget*) parent())->updateGeometry();
        //cout << "after " << sizeHint().width() << " " << sizeHint().height() << endl;
    }

    void initStyleOption(QStyleOptionGroupBox *option) const
    {
        QGroupBox::initStyleOption(option);
        QStyle::State flagToSet = _check_box_state ? QStyle::State_On : QStyle::State_Off;
        QStyle::State flagToRemove = _check_box_state ? QStyle::State_Off : QStyle::State_On;

        option->state |= flagToSet;
        option->state &= ~flagToRemove;
        option->state &= ~QStyle::State_Sunken;
    }

    void paintEvent(QPaintEvent *)
    {
        QStylePainter paint(this);
        QStyleOptionGroupBox option;
        initStyleOption(&option);
        paint.drawComplexControl(QStyle::CC_GroupBox, option);
    }

    void set_content_visibility(bool visible)
    {
        QList<QWidget*> list = this->findChildren<QWidget*>();
        for (QList<QWidget*>::iterator it = list.begin(); it != list.end(); it++)
        {
            (*it)->setVisible(visible);
        }
    }

private slots:
    void my_toggled(bool on)
    {
        toggled();
    }
};
