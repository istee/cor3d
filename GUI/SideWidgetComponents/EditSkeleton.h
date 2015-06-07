#pragma once

#include <QWidget>

#include "ui_EditSkeleton.h"
#include "GUI/EditWidgets/BaseEditWidget.h"
#include "Model/Skeleton.h"
#include "Model/BaseEntity.h"

using namespace cor3d;
using namespace std;

class EditSkeleton: public BaseEditWidget, public Ui::EditSkeleton
{
    Q_OBJECT

    void enable_edits();
    void disable_edits();
    string _skeletonName;
public:
    // special and default constructor
    EditSkeleton(QWidget *parent = 0);
    void update_content();
    void updateContent(BaseEntity* baseEntity);
    void data_changed();

signals:
    void viewSkeletonModelChanged(const string& file);
    void viewSkeletonModelScaleChanged(const DCoordinate3& scale);
    void viewSkeletonModelOffsetChanged(const DCoordinate3& offset);

private slots:
    void handleSkeletonModelChanged(const string& file);
    void handleSkeletonModelScaleChanged(const DCoordinate3& scale);
    void handleSkeletonModelOffsetChanged(const DCoordinate3& offset);
};
