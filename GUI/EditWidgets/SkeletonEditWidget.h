#pragma once

#include <QWidget>

#include "ui_SkeletonEditWidget.h"
#include "BaseEditWidget.h"
#include "Model/Skeleton.h"
#include "Model/BaseEntity.h"

using namespace cor3d;
using namespace std;

class SkeletonEditWidget: public BaseEditWidget, public Ui::SkeletonEditWidget
{
    Q_OBJECT

public:
    // special and default constructor
    SkeletonEditWidget(Skeleton* skeleton, QWidget *parent = 0);
    void updateContent(BaseEntity* baseEntity);
};
