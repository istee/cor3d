#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "GUI/Toolbars/TransformationsToolbar.h"

#include <iostream>

using namespace std;

class MainWindow: public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

private:
    TransformationsToolbar* _transformationToolbar;
    QAction*                _transformationAction;

public:
    // special and default constructor
    MainWindow(QWidget *parent = 0);
    void initialize();

private slots:
    // private event handling methods/slots
    void on_actionFile_triggered(bool checked);
    void on_actionAbout_triggered();
    void on_tabWidget_currentChanged(QWidget* );
    void on_actionTransformations_triggered(bool checked);
    void on_actionImport_triggered();
    void on_actionExport_triggered();
    void on_actionRendering_options_activated();
    void on_action_Quit_triggered();

    void handle_modelTranslationChanged(const DCoordinate3&);
    void handle_modelRotationChanged(const DCoordinate3&);
    void handle_modelZoomChanged(double);
};
