#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_RenderingOptionsWidget.h"
#include "BaseSideWidget.h"
#include "GUI/RenderingOptions.h"
#include "Cor3dApplication.h"

using namespace std;

class RenderingOptionsWidget: public QFrame, public Ui::RenderingOptionsWidget
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
    void view_joint_model_fileChanged(const string& file);
    void view_joint_material_changed(int material_id);
    void view_selected_joint_material_changed(int material_id);
    void view_link_render_toggled(bool on);
    void view_link_model_fileChanged(const string& file);
    void view_link_material_changed(int material_id);

private slots:
    void on_pushButton_3_clicked();
};
