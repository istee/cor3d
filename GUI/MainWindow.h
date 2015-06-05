#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "GUI/Toolbars/TransformationsToolbar.h"

class MainWindow: public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

private:
    TransformationsToolbar* _transformationToolbar;
    QAction* _transformationAction;

public:
    // special and default constructor
    MainWindow(QWidget *parent = 0);
    void initialize();

private slots:
    // private event handling methods/slots
    void on_tabWidget_currentChanged(QWidget* );
    void on_actionTransformations_triggered(bool checked);
    void on_actionImport_triggered();
    void on_actionExport_triggered();
    void on_actionRendering_options_activated();
    void on_action_Quit_triggered();

    void handle_model_translation_changed(const DCoordinate3&);
    void handle_model_rotation_changed(const DCoordinate3&);
    void handle_model_zoom_changed(double);
};
