#pragma once

#include <QWidget>

#include "Cor3dApplication.h"
#include "GLWidget.h"

class IMainWindowTab: public QWidget
{
    Q_OBJECT

protected:
    Cor3dApplication*   cor3dApp;


public:
    IMainWindowTab(QWidget* parent);
    GLWidget*           glwidget;

public slots:
    void viewTranslationChanged(const DCoordinate3& translation);
    void viewRotationChanged(const DCoordinate3& angles);
    void viewZoomFactorChanged(double value);

    virtual void skeleton_list_changed() { }
    virtual void skeleton_selected() { }
    virtual void selected_skeleton_name_changed() { }
    virtual void selected_skeleton_data_changed() { }
    virtual void selected_skeleton_joint_list_changed() { }
    virtual void selected_skeleton_joint_selected() { }
    virtual void selected_skeleton_joint_name_changed() { }
    virtual void selected_skeleton_joint_selection_changed() { }
    virtual void selected_skeleton_joint_data_changed() { }

    virtual void transformations_changed() { }

    virtual void rendering_options_changed() { }

signals:
    void modelTransformationsChanged();
};
