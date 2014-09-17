#pragma once

#include <QWidget>

#include "ui_ManageScene.h"
#include "BaseSideWidget.h"
#include "Model/Skeleton.h"

using namespace cor3d;

class ManageScene: public BaseSideWidget, public Ui::ManageScene
{
    Q_OBJECT
public:
    // special and default constructor
    ManageScene(QWidget *parent = 0);
    void update_content();

signals:
    void skeleton_added_to_scene(unsigned int skeleton_id, const string& stage_name, const DCoordinate3& position_offset);

private slots:
    void on_pushButton_released();
};
