#pragma once

#include <QWidget>
#include "ui_RenderingOptionsWidget.h"
#include "BaseSideWidget.h"
#include "GUI/RenderingOptions.h"
#include "Cor3dApplication.h"

using namespace std;

class RenderingOptionsWidget: public BaseSideWidget, public Ui::RenderingOptionsWidget
{
    Q_OBJECT
    Cor3dApplication *cor3dApp;
public:
    // special and default constructor
    RenderingOptionsWidget(QWidget *parent = 0);
    void update_content();

signals:

    void view_skeleton_render_toggled(bool on);
    void view_skeleton_material_changed(int material_id);
    void view_joint_render_toggled(bool on);
    void view_joint_model_file_changed(const string& file);
    void view_joint_material_changed(int material_id);
    void view_selected_joint_material_changed(int material_id);
    void view_link_render_toggled(bool on);
    void view_link_model_file_changed(const string& file);
    void view_link_material_changed(int material_id);
};
