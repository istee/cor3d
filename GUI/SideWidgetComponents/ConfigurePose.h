#pragma once

#include <QWidget>

#include "ui_ConfigurePose.h"
#include "BaseSideWidget.h"
#include "Model/Skeleton.h"

using namespace cor3d;

class ConfigurePose: public BaseSideWidget, public Ui::ConfigurePose
{
    Q_OBJECT
public:
    // special and default constructor
    ConfigurePose(QWidget *parent = 0);
    void update_content();

signals:
    void view_joint_selected(unsigned int joint_id);
    void view_joint_set_to_position(const DCoordinate3& position);
    void skeleton_setting_edited();
};
