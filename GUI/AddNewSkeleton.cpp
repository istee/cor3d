#include "AddNewSkeleton.h"
<<<<<<< HEAD

#include "Cor3dApplication.h"
#include "StdExtension.h"
=======
#include <iostream>
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa

using namespace std;

AddNewSkeleton::AddNewSkeleton(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

<<<<<<< HEAD
void AddNewSkeleton::update_content()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    unsigned int skeleton_count = cor3dApp->cor3d.get_skeleton_count();
    string name = "Skeleton " + std::to_string(skeleton_count);
    if (cor3dApp->cor3d.is_skeleton_name_reserved(name))
    {
        unsigned int nr = 2;
        do
        {
            name = "Skeleton " + std::to_string(skeleton_count);
            name += "_";
            name += std::to_string(nr);
        } while (!cor3dApp->cor3d.is_skeleton_name_reserved(name));
    }
    new_skeleton_name->setText(QString::fromStdString(name));
}

void AddNewSkeleton::on_add_new_skeleton_button_released()
{
    emit skeleton_added(new_skeleton_name->text().toStdString());
}
=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
