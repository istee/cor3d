#pragma once

#include <QWidget>
#include <QStandardItemModel>
#include <ui_Import.h>

using namespace std;

class Import : public QWidget, public Ui::Import
{
    Q_OBJECT
public:
    Import(QWidget *parent = 0);

private:
    QStandardItemModel *model;

private slots:
    void on_closeButton_clicked();
    void on_importButton_clicked();
    void on_importFile_changed(string filename);
    void addItemToModel(QStandardItem *item);
};

