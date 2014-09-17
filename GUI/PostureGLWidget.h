#pragma once

#include "GLWidget.h"

class PostureGLWidget : public GLWidget {
    Q_OBJECT
protected:
    virtual void specificPaintGL();

public:
    // special and default constructor
    // the format specifies the properties of the rendering window
    PostureGLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);

    void drag_starting();
    void drag_finished();

signals:
    void view_joint_fabrik_moved(const DCoordinate3&);
};
