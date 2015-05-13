#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

class MainWindow: public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    // special and default constructor
    MainWindow(QWidget *parent = 0);
    void initialize();

private slots:
    // private event handling methods/slots
    void on_actionImport_triggered();
    void on_actionExport_triggered();
    void on_actionRendering_options_activated();
    void on_action_Quit_triggered();

};
