#include "EditSkeleton.h"

#include <QFileDialog>

#include "Model/Cor3d.h"
#include "Cor3dApplication.h"

using namespace std;
using namespace cor3d;

EditSkeleton::EditSkeleton(QWidget *parent): BaseEditWidget(parent)
{
    setupUi(this);
    model_file->setLabel("Model file");
    model_file->setCaption("Open OFF model file");
    model_file->setFilter("OFF Files (*.off)");
    model_scale->setTitle("Model scale");
    model_offset->setTitle("Model offset");

    model_scale->setSettings(DCoordinate3(0.1, 0.1, 10));
    model_offset->setSettings(DCoordinate3(-100, 0.1, 100));

    connect(model_file, SIGNAL(fileChanged(string)), this, SLOT(handleSkeletonModelChanged(string)));
    connect(model_scale, SIGNAL(CoordinatesChanged(DCoordinate3)), this, SLOT(handleSkeletonModelScaleChanged(DCoordinate3)));
    connect(model_offset, SIGNAL(CoordinatesChanged(DCoordinate3)), this, SLOT(handleSkeletonModelOffsetChanged(DCoordinate3)));
}

void EditSkeleton::update_content()
{
}

void EditSkeleton::updateContent(BaseEntity* baseEntity)
{
    Skeleton* skeleton = (Skeleton*) baseEntity;
    _skeletonName = skeleton->get_name();
    model_file->setValue(skeleton->get_model_file());
    model_scale->setValue(skeleton->get_model_scale());
    model_offset->setValue(skeleton->get_model_offset());
}

void EditSkeleton::handleSkeletonModelChanged(const string& file)
{
    emit viewSkeletonModelChanged(file);
}

void EditSkeleton::handleSkeletonModelOffsetChanged(const DCoordinate3& offset)
{
    emit viewSkeletonModelOffsetChanged(offset);
}

void EditSkeleton::handleSkeletonModelScaleChanged(const DCoordinate3& scale)
{
    emit viewSkeletonModelScaleChanged(scale);
}
