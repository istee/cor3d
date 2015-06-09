#include "AddNewSkeleton.h"

#include <QFileDialog>
#include "Cor3dApplication.h"
#include "StdExtension.h"

using namespace std;

AddNewSkeleton::AddNewSkeleton(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    name->setLabel("Name");
}

void AddNewSkeleton::update_content()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    name->setValue(cor3dApp->cor3d->next_name());
}

void AddNewSkeleton::on_add_new_skeleton_button_released()
{
    emit view_skeleton_added(name->getValue());
}

void AddNewSkeleton::on_pushButton_released()
{
    string file_name = QFileDialog::getOpenFileName(this,tr("Import skeleton"), "", tr("SK File (*.sk)")).toStdString();
    emit view_skeleton_imported(file_name);
}
