#include "TransformationsWidget.h"

using namespace std;

TransformationsWidget::TransformationsWidget(QWidget *parent): BaseSideWidget(parent)
{
    setupUi(this);
    translate->setTitle("Translation");
    rotate->setTitle("Rotation");
    scale_label->setText("Scale");

    translate->setSettings(DCoordinate3(-100, 0.1, 100));
    rotate->setSettings(DCoordinate3(-180, 1, 180));
    scale_doubleSpinBox->setMinimum(0.1);
    scale_doubleSpinBox->setMaximum(10);
    scale_doubleSpinBox->setSingleStep(0.1);

    connect(rotate, SIGNAL(coordinates_changed(DCoordinate3)), this, SLOT(rotation_changed(DCoordinate3)));
    connect(translate, SIGNAL(coordinates_changed(DCoordinate3)), this, SLOT(translation_changed(DCoordinate3)));
    connect(scale_doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(zoom_factor_changed(double)));
}

void TransformationsWidget::setGLWidget(GLWidget* glwidget)
{
    _glwidget = glwidget;
}

void TransformationsWidget::update_content()
{
//    if (_glwidget)
//    {
//        blockSignals(true);
//        translate->setValue(_glwidget->get_translation());
//        rotate->setValue(_glwidget->get_rotation());
//        scale_doubleSpinBox->setValue(_glwidget->get_zoom_factor());
//        blockSignals(false);
//    }
}

void TransformationsWidget::rotation_changed(const DCoordinate3& rotation)
{
    emit rotation_changed(rotation);
}

void TransformationsWidget::translation_changed(const DCoordinate3& rotation)
{
    emit translation_changed(rotation);
}

void TransformationsWidget::zoom_factor_changed(double scale)
{
    emit zoom_factor_changed(scale);
}


