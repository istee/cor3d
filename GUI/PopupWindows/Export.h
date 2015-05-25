#pragma once

#include <QWidget>
#include <QStandardItemModel>

#include <ui_Export.h>

using namespace std;

class Export : public QWidget, public Ui::Export
{
    Q_OBJECT
public:
    Export(QWidget *parent = 0);

private:
    QStandardItemModel *model;
    void AddItemToModel(QStandardItem *item);

private slots:
    void on_buttonClearAll_clicked();
    void on_buttonSelectAll_clicked();
    void on_closeButton_clicked();
    void on_exportButton_clicked();
    void on_exportFile_changed(string filename);
};

