#pragma once

#include "glwidget.h"

using namespace cagd;

class SkeletonGLWidget : public GLWidget {
    Q_OBJECT
protected:
    virtual void specificPaintGL();
    virtual void specificDrawPickObjects();
    virtual int specificPickCount();
    virtual void specificPick(unsigned int closestSelected);
    virtual void drag(double x, double y, double z);

public:
    // special and default constructor
    // the format specifies the properties of the rendering window
    SkeletonGLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);
};
