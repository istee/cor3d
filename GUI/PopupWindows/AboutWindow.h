#pragma once

#include <QWidget>

#include <ui_AboutWindow.h>

using namespace std;

class AboutWindow : public QWidget, public Ui::AboutWindow
{
    Q_OBJECT
public:
    AboutWindow(QWidget *parent = 0):QWidget(parent){setupUi(this);}
};

