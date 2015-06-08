#pragma once

#include "glwidget.h"

class SceneGLWidget : public GLWidget {
protected:
    virtual void specificPaintGL();
    virtual void specificPick();

public:
    // special and default constructor
    // the format specifies the properties of the rendering window
    SceneGLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);
};
