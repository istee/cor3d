#pragma once

#include <QApplication>
#include <QFile>

#include "Model/Cor3d.h"

using namespace cor3d;

class Cor3dApplication: public QApplication
{
public:

    Cor3d *cor3d;

    Cor3dApplication(int argc, char** argv): QApplication(argc, argv)
    {
        cor3d = new Cor3d();

        QFile styleSheet("Resources/stylesheet.qss");  //path where the file is stored
        if (!styleSheet.open(QIODevice::ReadOnly))
        {
            qWarning("Unable to open ../Resources/stylesheet.qss");
            return;
        }
        qApp->setStyleSheet(styleSheet.readAll());

    }
};
