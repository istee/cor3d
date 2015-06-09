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

class GroupBoxExtension: public QGroupBox
{
    Q_OBJECT

    QSize           _sizeHint;
    QSizePolicy     _sizePolicy;
    bool            _checkBoxState;

public:
    GroupBoxExtension(QWidget* parent);
    bool event(QEvent *e);
    bool myKeyReleaseHandler(QKeyEvent *event);
    void myMouseHandler(QMouseEvent *event);
    void toggled();
    void initStyleOption(QStyleOptionGroupBox *option) const;
    void paintEvent(QPaintEvent *);
    void setContentVisibility(bool visible);
private slots:
    void handleToggle(bool on);

signals:
    void groupboxToggled(bool showContent);
};
