#pragma once

#include <QWidget>

#include "Core/DCoordinates3.h"

namespace Ui {
    class TransformationsToolbar;
}

using namespace cagd;

class TransformationsToolbar : public QWidget
{
    Q_OBJECT

public:
    explicit TransformationsToolbar(QWidget *parent = 0);
    void setTranslation(const DCoordinate3& translation);
    void setRotation(const DCoordinate3& rotation);
    void setZoomFactor(const double& zoomFactor);
    ~TransformationsToolbar();

private:
    Ui::TransformationsToolbar *ui;

private slots:
    void on_doubleSpinBoxZoomFactor_valueChanged(double );
    void on_doubleSpinBoxRotateZ_valueChanged(double );
    void on_doubleSpinBoxRotateY_valueChanged(double );
    void on_doubleSpinBoxRotateX_valueChanged(double );
    void on_doubleSpinBoxTranslateZ_valueChanged(double );
    void on_doubleSpinBoxTranslateY_valueChanged(double );
    void on_doubleSpinBoxTranslateX_valueChanged(double );

signals:
    void viewTranslationChanged(DCoordinate3 translation);
    void viewRotationChanged(DCoordinate3 rotation);
    void viewZoomFactorChanged(double zoomFactor);
};
