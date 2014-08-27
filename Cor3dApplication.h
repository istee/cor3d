#include <QApplication>

#include "Model/Cor3d.h"

using namespace cor3d;

class Cor3dApplication: public QApplication
{
public:

    Cor3d cor3d;

    Cor3dApplication(int argc, char** argv): QApplication(argc, argv)
    {
        cor3d = Cor3d();
    }
};
