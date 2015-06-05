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
    importFile->setFilePath("");

    model = new QStandardItemModel();

    model->setColumnCount(1);
    model->setHeaderData(0, Qt::Horizontal, "Select items to import:");
    treeView->setModel(model);

    connect(importFile, SIGNAL(file_changed(string)), this, SLOT(on_importFile_changed(string)));
}

void Import::on_importButton_clicked()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    ifstream file;
    file.open(importFile->fileLabel->text().toAscii(), ios::out);
    if (file.is_open())
    {
        string text;
        unsigned int skeletonCount;
        file >> text >> skeletonCount;
        for (unsigned int i = 0; i < skeletonCount; i++)
        {
            cor3dApp->cor3d->importSkeleton(file);
        }
    }
    else
    {
        cerr << "File could not be opened!\n"; // Report error
             cerr << "Error code: " << strerror(errno); // Get some info as to why
    }
}

void Import::on_importFile_changed(string filename)
{
    importFile->setFilePath(filename);
}

void Import::on_closeButton_clicked()
{
    this->close();
}
