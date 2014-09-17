#pragma once

#include <QWidget>

#include "ui_ManagePoses.h"
#include "BaseSideWidget.h"
#include "Model/Skeleton.h"

using namespace cor3d;

class ManagePoses: public BaseSideWidget, public Ui::ManagePoses
{
    Q_OBJECT
public:
    // special and default constructor
    ManagePoses(QWidget *parent = 0);
    void update_content();

signals:
    void skeleton_pose_selected(unsigned int pose_id);
    void skeleton_pose_saved(const string& name);
    void skeleton_pose_deleted();
};
