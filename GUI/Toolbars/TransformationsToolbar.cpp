#include "TransformationsToolbar.h"
#include "ui_TransformationsToolbar.h"

TransformationsToolbar::TransformationsToolbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformationsToolbar)
{
    ui->setupUi(this);
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

