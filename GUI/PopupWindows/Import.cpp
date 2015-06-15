#include "Import.h"

#include <QTime>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <fstream>

#include "Cor3dApplication.h"
#include "Model/Cor3d.h"


Import::Import(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    importFile->setLabel("Import file:");
    importFile->setButtonText("Browse");
    importFile->setFilter("*.c3data");
    importFile->setCaption("Import file");
    importFile->setAcceptMode(QFileDialog::AcceptOpen);
    importFile->setFilePath("/SaveFiles");

    model = new QStandardItemModel();

    model->setColumnCount(1);
    model->setHeaderData(0, Qt::Horizontal, "Select items to import:");
    treeView->setModel(model);

    connect(importFile, SIGNAL(fileChanged(string)), this, SLOT(on_importFile_changed(string)));
}

void Import::on_importButton_clicked()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    ifstream file;
    file.open(importFile->getValue().data(), ios::out);
    if (file.is_open())
    {
        string text;
        unsigned int skeletonCount;
        file >> text >> skeletonCount;
        for (int i = 0; i < skeletonCount; i++)
        {
            file >> text;
        }
        for (unsigned int i = 0; i < skeletonCount; i++)
        {
            cor3dApp->cor3d->importSkeleton(file);
        }

        on_closeButton_clicked();
    }
    else
    {
        cerr << "File could not be opened!\n"; // Report error
             cerr << "Error code: " << strerror(errno); // Get some info as to why
    }
}

void Import::addItemToModel(QStandardItem *item)
{
    model->appendRow(item);
    buttonSelectAll->setEnabled(true);
    buttonClearAll->setEnabled(true);
    importButton->setEnabled(true);
}


void Import::on_importFile_changed(string filename)
{
    importFile->setFilePath(filename);
    ifstream file;
    file.open(importFile->getValue().data(), ios::out);
    if (file.is_open())
    {
        string text;
        file >> text;
        unsigned int skeletonCount;
        file >> skeletonCount;
        for (int i = 0; i < skeletonCount; i++)
        {
            file >> text;
            QStandardItem *item = new QStandardItem(QString::fromStdString(text));
            item->setCheckable(true);
            item->setCheckState(Qt::Checked);
            addItemToModel(item);
        }
        treeView->setModel(model);
    }
    file.close();
}

void Import::on_closeButton_clicked()
{
    this->close();
}
