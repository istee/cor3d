#pragma once

#include "ui_PostureEditWidget.h"

#include <QWidget>

#include "BaseEditWidget.h"
#include "Model/Skeleton.h"
#include "Model/Joint.h"
#include "Model/Posture.h"
#include "Core/DCoordinates3.h"

using namespace cagd;
using namespace std;

class PostureEditWidget : public BaseEditWidget, public Ui::PostureEditWidget
{
    Q_OBJECT
    unsigned int    _jointId;
    string          _jointName;
public:
    explicit PostureEditWidget(Skeleton* skeleton, Joint* joint, QWidget *parent = 0);
    virtual void updateContent(BaseEntity*);

signals:
    void viewPostureJointAbsoluteCoordinatesChanged(const string& jointName, const DCoordinate3& absoluteCoordinates);

private slots:
    void handleAbsoluteCoordinatesChanged(const DCoordinate3&);
};
