#pragma once

#include "GLWidget.h"

class SceneGLWidget : public GLWidget {
    Q_OBJECT
public:
    // special and default constructor
    // the format specifies the properties of the rendering window
    SceneGLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);
};
