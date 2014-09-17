#pragma once

#include <QWidget>
#include "ui_TransformationsWidget.h"
#include "BaseSideWidget.h"
#include "Core/Transformations.h"
#include "GUI/GLWidget.h"

using namespace std;

class TransformationsWidget: public BaseSideWidget, public Ui::TransformationsWidget
{
    Q_OBJECT
    GLWidget*    _glwidget;
public:
    // special and default constructor
    TransformationsWidget(QWidget *parent = 0);
    void setGLWidget(GLWidget* glWidget);
    void update_content();

signals:
    void view_rotation_changed(const DCoordinate3& rotation);
    void view_translation_changed(const DCoordinate3& rotation);
    void view_zoom_factor_changed(double scale);

private slots:
    void rotation_changed(const DCoordinate3& rotation);
    void translation_changed(const DCoordinate3& rotation);
    void zoom_factor_changed(double scale);
};
