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

//    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
//    const vector<BaseEntity*> skeleton_list = cor3dApp->cor3d->get_skeleton_list();
//    QStandardItemModel *model = new QStandardItemModel();

//    for (vector<BaseEntity*>::const_iterator it = skeleton_list.begin(); it != skeleton_list.end(); it++)
//    {
//        QStandardItem *item = new QStandardItem(QString::fromStdString((*it)->get_name()));
//        item->setCheckable(true);
//        item->setCheckState(Qt::Checked);
//        model->appendRow(item);
//        cout << (*it)->get_name() << endl;
//    }
//    treeView->setModel(model);

    connect(importFile, SIGNAL(file_changed(string)), this, SLOT(on_importFile_changed(string)));
}

void Import::on_importButton_clicked()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    ifstream file;
    file.open(importFile->fileLabel->text().toAscii(), ios::out);
    cout << importFile->fileLabel->text().toStdString() << endl;
    if (file.is_open())
    {
        string text;
        unsigned int skeletonCount;
        file >> text >> skeletonCount;
            cout << "skeletonCount: " << skeletonCount << endl;
        for (unsigned int i = 0; i < skeletonCount; i++)
        {
            Skeleton* skeleton = new Skeleton();
            file >> *skeleton;
        }
    }
    else
    {
        cerr << "File could not be opened!\n"; // Report error
             cerr << "Error code: " << strerror(errno); // Get some info as to why
        cout << "nem irunk" << endl;
    }
}

void Import::on_importFile_changed(string filename)
{
    cout << filename << endl;
    importFile->setFilePath(filename);
}
