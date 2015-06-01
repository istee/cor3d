#include "EditSkeleton.h"

#include <QFileDialog>

#include "Model/Cor3d.h"
#include "Cor3dApplication.h"

using namespace std;
using namespace cor3d;

EditSkeleton::EditSkeleton(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    model_file->setLabel("Model file");
    model_file->setCaption("Open OFF model file");
    model_file->setFilter("OFF Files (*.off)");
    model_scale->setTitle("Model scale");
    model_offset->setTitle("Model offset");

    connect(model_file, SIGNAL(file_changed(string)), this, SLOT(handle_skeleton_model_changed(string)));
    connect(model_scale, SIGNAL(coordinates_changed(DCoordinate3)), this, SLOT(handle_skeleton_model_scale_changed(DCoordinate3)));
    connect(model_offset, SIGNAL(coordinates_changed(DCoordinate3)), this, SLOT(handle_skeleton_model_offset_changed(DCoordinate3)));
}

void EditSkeleton::update_content()
{
    cout << "editskeleton update_content" << endl;
}

void EditSkeleton::updateContent(BaseEntity* baseEntity)
{
    Skeleton* skeleton = (Skeleton*) baseEntity;
    _skeletonName = skeleton->get_name();
    model_file->setValue(skeleton->get_model_file());
    model_scale->setValue(skeleton->get_model_scale());
    model_offset->setValue(skeleton->get_model_offset());
}

void EditSkeleton::handle_skeleton_model_changed(const string& file)
{
    emit view_skeleton_model_changed(_skeletonName, file);
}

void EditSkeleton::handle_skeleton_model_offset_changed(const DCoordinate3& offset)
{
    emit view_skeleton_model_offset_changed(_skeletonName, offset);
}

void EditSkeleton::handle_skeleton_model_scale_changed(const DCoordinate3& scale)
{
    emit view_skeleton_model_scale_changed(_skeletonName, scale);
}
