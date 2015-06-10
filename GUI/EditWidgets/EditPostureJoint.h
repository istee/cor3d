#pragma once

#include <QWidget>

#include "BaseEditWidget.h"
#include "Model/Skeleton.h"
#include "Model/Joint.h"
#include "Model/Posture.h"
#include "Core/DCoordinates3.h"

namespace Ui {
    class EditPostureJoint;
}

using namespace cagd;
using namespace std;

class EditPostureJoint : public BaseEditWidget
{
    Q_OBJECT
    unsigned int    _jointId;
    string          _jointName;
public:
    explicit EditPostureJoint(Skeleton* skeleton, Joint* joint, QWidget *parent = 0);
    virtual void updateContent(BaseEntity*);
    ~EditPostureJoint();

signals:
    void viewPostureJointAbsoluteCoordinatesChanged(const string& jointName, const DCoordinate3& absoluteCoordinates);

private slots:
    void handleAbsoluteCoordinatesChanged(const DCoordinate3&);

private:
    Ui::EditPostureJoint *ui;
};
