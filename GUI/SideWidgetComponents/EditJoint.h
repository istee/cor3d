#pragma once

#include <QWidget>

#include "ui_EditJoint.h"
#include "BaseSideWidget.h"

#include "Core/DCoordinates3.h"
#include "Model/Joint.h"

using namespace cor3d;
using namespace cagd;
using namespace std;

class EditJoint: public BaseSideWidget, public Ui::EditJoint
{
    Q_OBJECT

    DCoordinate3 coordinate_settings;
    DCoordinate3 angle_settings;

public:
    // special and default constructor
    EditJoint(QWidget *parent = 0);
    void update_content();
    virtual void updateContent(BaseEntity*);

signals:
    /*
    void view_joint_selection_changed(int joint_id);
    void view_joint_parent_changed(int parent_id);
    void view_joint_type_changed(int joint_type);
    void view_joint_axis_changed(const string& name, const DCoordinate3& axis);
    void view_joint_orientation_changed(const DCoordinate3& orientation);
    void view_joint_configuration_changed(const DCoordinate3& configuration);
    */

    void view_joint_coordinates_changed(const string& name, const DCoordinate3& coordinates);
    void view_joint_scale_changed(const string& name, const DCoordinate3& scale);

private slots:
    void handle_joint_absolute_coordinates_changed(const DCoordinate3& coordinates);
    void handle_joint_relative_coordinates_changed(const DCoordinate3& coordinates);
    void handle_joint_scale_changed(const DCoordinate3& scale);
};
