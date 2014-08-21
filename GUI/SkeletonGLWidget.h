#pragma once

#include "GLWidget.h"

class SkeletonGLWidget : public GLWidget {
public:
    // special and default constructor
    // the format specifies the properties of the rendering window
    SkeletonGLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);
};
