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
    ~TransformationsToolbar();

private:
    Ui::TransformationsToolbar *ui;

private slots:
    void on_doubleSpinBoxTranslateZ_valueChanged(double );
    void on_doubleSpinBoxTranslateY_valueChanged(double );
    void on_doubleSpinBoxTranslateX_valueChanged(double );

signals:
    void viewTranslationChanged(DCoordinate3 translate);
};
