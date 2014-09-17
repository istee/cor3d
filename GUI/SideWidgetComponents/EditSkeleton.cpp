#include "EditSkeleton.h"

#include <QFileDialog>

#include "Model/Cor3d.h"
#include "Cor3dApplication.h"

using namespace std;
using namespace cor3d;

EditSkeleton::EditSkeleton(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    name->setLabel("Name");
    model_file->setLabel("Model file");
    model_file->setCaption("Open OFF model file");
    model_file->setFilter("OFF Files (*.off)");
    model_scale->setTitle("Model scale");
    model_offset->setTitle("Model offset");

    connect(name, SIGNAL(name_changed(string)), this, SIGNAL(view_skeleton_name_changed(string)));
    connect(model_file, SIGNAL(file_changed(string)), this, SIGNAL(view_skeleton_model_changed(string)));
    connect(model_scale, SIGNAL(coordinates_changed(DCoordinate3)), this, SIGNAL(view_skeleton_model_scale_changed(DCoordinate3)));
    connect(model_offset, SIGNAL(coordinates_changed(DCoordinate3)), this, SIGNAL(view_skeleton_model_offset_changed(DCoordinate3)));
}

void EditSkeleton::update_content()
{
    Cor3dApplication *cor3dApp = (Cor3dApplication*) qApp;
    Skeleton* selected_skeleton = cor3dApp->cor3d->get_skeleton();
    if (selected_skeleton)
    {
        this->setEnabled(true);
        name->setValue(selected_skeleton->get_name());
        model_file->setValue(selected_skeleton->get_model_file());
        model_scale->setValue(selected_skeleton->get_model_scale());
        model_offset->setValue(selected_skeleton->get_model_offset());
    }
    else
    {
        this->setEnabled(false);
    }
}
