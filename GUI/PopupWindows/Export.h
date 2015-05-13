#pragma once

#include <QWidget>
#include <ui_Export.h>

using namespace std;

class Export : public QWidget, public Ui::Export
{
    Q_OBJECT
public:
    Export(QWidget *parent = 0);

private slots:
    void on_exportButton_clicked();
    void on_exportFile_changed(string filename);
};

