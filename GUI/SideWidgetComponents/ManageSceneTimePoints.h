#pragma once

#include <QWidget>

#include "ui_ManageSceneTimePoints.h"
#include "BaseSideWidget.h"
#include "Model/Skeleton.h"

using namespace cor3d;

class ManageSceneTimePoints: public BaseSideWidget, public Ui::ManageSceneTimePoints
{
    Q_OBJECT
public:
    // special and default constructor
    ManageSceneTimePoints(QWidget *parent = 0);
    void update_content();

signals:
    void time_point_added_to_scene(unsigned int skeleton_id, unsigned int pose_id, double time);

private slots:
    void on_pushButton_released();
};
