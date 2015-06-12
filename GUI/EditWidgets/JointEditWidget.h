#pragma once

#include <QWidget>

#include "ui_JointEditWidget.h"
#include "BaseEditWidget.h"

#include "Core/DCoordinates3.h"
#include "Model/Joint.h"
#include "Model/Skeleton.h"

using namespace cor3d;
using namespace cagd;
using namespace std;

class JointEditWidget: public BaseEditWidget, public Ui::JointEditWidget
{
    Q_OBJECT

    DCoordinate3 _coordinateSettings;
    DCoordinate3 _angleSettings;

public:
    // special and default constructor
    JointEditWidget(Skeleton* skeleton, Joint* joint, QWidget *parent = 0);
    virtual void updateContent(BaseEntity*);

signals:
    void viewJointAbsoluteCoordinatesChanged(const string& name, const DCoordinate3& absoluteCoordinates);
    void viewJointRelativeCoordinatesChanged(const string& name, const DCoordinate3& relativeCoordinates);
    void viewJointScaleChanged(const string& name, const DCoordinate3& scale);

private slots:
    void handleJointAbsoluteCoordinatesChanged(const DCoordinate3& coordinates);
    void handleJointRelativeCoordinatesChanged(const DCoordinate3& coordinates);
    void handleJointScaleChanged(const DCoordinate3& scale);
};
