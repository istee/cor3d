#pragma once

#include <QWidget>
#include <ui_Import.h>

using namespace std;

class Import : public QWidget, public Ui::Import
{
    Q_OBJECT
public:
    Import(QWidget *parent = 0);

private slots:
    void on_importButton_clicked();
    void on_importFile_changed(string filename);
};

