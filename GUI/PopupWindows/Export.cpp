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
    exportFile->setLabel("Export file:");
    exportFile->setButtonText("Browse");
    exportFile->setFilter("*.c3data");
    exportFile->setCaption("Export file");
    exportFile->setAcceptMode(QFileDialog::AcceptSave);
    exportFile->setFilePath(QDir::currentPath().toStdString() + "/cor3d export " + QDateTime::currentDateTime().toString(QString::fromStdString("yyyy-MM-dd-hhmmss")).toStdString() + ".c3data");

    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    const vector<BaseEntity*> skeleton_list = cor3dApp->cor3d->get_skeleton_list();
    QStandardItemModel *model = new QStandardItemModel();

    for (vector<BaseEntity*>::const_iterator it = skeleton_list.begin(); it != skeleton_list.end(); it++)
    {
        QStandardItem *item = new QStandardItem(QString::fromStdString((*it)->get_name()));
        item->setCheckable(true);
        item->setCheckState(Qt::Checked);
        model->appendRow(item);
        cout << (*it)->get_name() << endl;
    }
    treeView->setModel(model);

    connect(exportFile, SIGNAL(file_changed(string)), this, SLOT(on_exportFile_changed(string)));
}

void Export::on_exportButton_clicked()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    ofstream file;
    file.open(exportFile->fileLabel->text().toAscii(), ios::out);
    cout << exportFile->fileLabel->text().toStdString() << endl;
    if (file.is_open())
    {
        int skeletonCount = treeView->model()->rowCount();
        file << "skeleton_count: " << skeletonCount << endl;
        for (int i = 0; i < skeletonCount; i++)
        {
            string skeletonName = treeView->model()->index(i,0).data().toString().toStdString();
            int skeletonId = cor3dApp->cor3d->get_skeleton_id_by_name(skeletonName);
            Skeleton *skeleton = cor3dApp->cor3d->getSkeletonById(skeletonId);
            if (skeleton)
            {
                file << *skeleton << endl;
            }
        }
    }
    else
    {
        cerr << "File could not be opened!\n"; // Report error
             cerr << "Error code: " << strerror(errno); // Get some info as to why
        cout << "nem irunk" << endl;
    }
}

void Export::on_exportFile_changed(string filename)
{
    cout << filename << endl;
    exportFile->setFilePath(filename);
}
