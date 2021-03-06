#include "Export.h"

#include <QTime>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <fstream>

#include "Cor3dApplication.h"
#include "Model/Cor3d.h"


Export::Export(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    exportButton->setEnabled(false);
    exportFile->setLabel("Export file:");
    exportFile->setButtonText("Browse");
    exportFile->setFilter("*.c3data");
    exportFile->setCaption("Export file");
    exportFile->setAcceptMode(QFileDialog::AcceptSave);
    exportFile->setFilePath(QDir::currentPath().toStdString() + "/cor3d export " + QDateTime::currentDateTime().toString(QString::fromStdString("yyyy-MM-dd-hhmmss")).toStdString() + ".c3data");

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    const vector<BaseEntity*> skeleton_list = cor3dApp->cor3d->getSkeletonList();
    model = new QStandardItemModel();
    model->setColumnCount(1);
    model->setHeaderData(0, Qt::Horizontal, "Select skeletons to export:");

    for (vector<BaseEntity*>::const_iterator it = skeleton_list.begin(); it != skeleton_list.end(); it++)
    {
        QStandardItem *item = new QStandardItem(QString::fromStdString((*it)->getName()));
        item->setCheckable(true);
        item->setCheckState(Qt::Checked);
        AddItemToModel(item);
    }
    treeView->setModel(model);

    connect(exportFile, SIGNAL(fileChanged(string)), this, SLOT(on_exportFile_changed(string)));
}

void Export::AddItemToModel(QStandardItem *item)
{
    model->appendRow(item);
    buttonSelectAll->setEnabled(true);
    buttonClearAll->setEnabled(true);
    exportButton->setEnabled(true);
}

void Export::on_exportButton_clicked()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    ofstream file;
    file.open(exportFile->getValue().data(), ios::out);
    if (file.is_open())
    {
        int skeletonCount = treeView->model()->rowCount();
        file << "skeleton_count: " << skeletonCount << endl;
        for (int i = 0; i < skeletonCount; i++)
        {
            string skeletonName = treeView->model()->index(i,0).data().toString().toStdString();
            Skeleton *skeleton = cor3dApp->cor3d->getSkeletonByName(skeletonName);
            file << skeleton->getName() << endl;
        }
        for (int i = 0; i < skeletonCount; i++)
        {
            string skeletonName = treeView->model()->index(i,0).data().toString().toStdString();
            Skeleton *skeleton = cor3dApp->cor3d->getSkeletonByName(skeletonName);
            if (skeleton)
            {
                file << *skeleton << endl;
            }
        }

        on_closeButton_clicked();
    }
    else
    {
        cerr << "File could not be opened!\n"; // Report error
             cerr << "Error code: " << strerror(errno); // Get some info as to why
    }
}

void Export::on_exportFile_changed(string filename)
{
    exportFile->setFilePath(filename);
}

void Export::on_closeButton_clicked()
{
    this->close();
}

void Export::on_buttonSelectAll_clicked()
{
    for (int i = 0 ; i < model->rowCount() ; i++)
    {
        model->item(i)->setCheckState(Qt::Checked);
    }
    treeView->setModel(model);
}

void Export::on_buttonClearAll_clicked()
{
    for (int i = 0 ; i < model->rowCount() ; i++)
    {
        model->item(i)->setCheckState(Qt::Unchecked);
    }
    treeView->setModel(model);
}
