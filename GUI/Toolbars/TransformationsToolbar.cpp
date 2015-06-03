#include "TransformationsToolbar.h"
#include "ui_TransformationsToolbar.h"

#include <QLineEdit>

TransformationsToolbar::TransformationsToolbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformationsToolbar)
{
    ui->setupUi(this);
}

void TransformationsToolbar::setTranslation(const DCoordinate3& translation)
{
    this->ui->doubleSpinBoxTranslateX->setValue(translation.x());
    this->ui->doubleSpinBoxTranslateY->setValue(translation.y());
    this->ui->doubleSpinBoxTranslateZ->setValue(translation.z());
}

void TransformationsToolbar::setRotation(const DCoordinate3& rotation)
{
    this->ui->doubleSpinBoxRotateX->setValue(rotation.x());
    this->ui->doubleSpinBoxRotateY->setValue(rotation.y());
    this->ui->doubleSpinBoxRotateZ->setValue(rotation.z());
}

void TransformationsToolbar::setZoomFactor(const double& zoomFactor)
{
    this->ui->doubleSpinBoxZoomFactor->setValue(zoomFactor * 100);
}

TransformationsToolbar::~TransformationsToolbar()
{
    delete ui;
}

void TransformationsToolbar::on_doubleSpinBoxTranslateX_valueChanged(double x)
{
    emit viewTranslationChanged(DCoordinate3(x, this->ui->doubleSpinBoxTranslateY->value(), this->ui->doubleSpinBoxTranslateZ->value()));
}

void TransformationsToolbar::on_doubleSpinBoxTranslateY_valueChanged(double y)
{
    emit viewTranslationChanged(DCoordinate3(this->ui->doubleSpinBoxTranslateX->value(), y, this->ui->doubleSpinBoxTranslateZ->value()));
}

void TransformationsToolbar::on_doubleSpinBoxTranslateZ_valueChanged(double z)
{
    emit viewTranslationChanged(DCoordinate3(this->ui->doubleSpinBoxTranslateX->value(), this->ui->doubleSpinBoxTranslateY->value(), z));
}

void TransformationsToolbar::on_doubleSpinBoxRotateX_valueChanged(double x)
{
    emit viewRotationChanged(DCoordinate3(x, this->ui->doubleSpinBoxRotateY->value(), this->ui->doubleSpinBoxRotateZ->value()));
}

void TransformationsToolbar::on_doubleSpinBoxRotateY_valueChanged(double y)
{
    emit viewRotationChanged(DCoordinate3(this->ui->doubleSpinBoxRotateX->value(), y, this->ui->doubleSpinBoxRotateZ->value()));
}

void TransformationsToolbar::on_doubleSpinBoxRotateZ_valueChanged(double z)
{
    emit viewRotationChanged(DCoordinate3(this->ui->doubleSpinBoxRotateX->value(), this->ui->doubleSpinBoxRotateY->value(), z));
}

void TransformationsToolbar::on_doubleSpinBoxZoomFactor_valueChanged(double zoomFactor)
{
    emit viewZoomFactorChanged(zoomFactor / 100);
}
