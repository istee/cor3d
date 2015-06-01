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

    QSize           _sizeHint;
    QSizePolicy     _sizePolicy;

protected:
    bool            _check_box_state;

public:
    SideWidgetGroupBox(QWidget* parent);
    bool event(QEvent *e);
    bool myKeyReleaseHandler(QKeyEvent *event);
    void myHandler(QMouseEvent *event);
    void toggled();
    void initStyleOption(QStyleOptionGroupBox *option) const;
    void paintEvent(QPaintEvent *);
    void set_content_visibility(bool visible);
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
private slots:
    void my_toggled(bool on);
};
