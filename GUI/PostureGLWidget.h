#pragma once

#include "glwidget.h"

class PostureGLWidget : public GLWidget {
    Q_OBJECT
protected:
    virtual void specificPaintGL();
    virtual void specificDrawPickObjects();
    virtual int specificPickCount();
    virtual void specificPick(unsigned int closestSelected);
    virtual DCoordinate3 dragCoordinate();

public:
    // special and default constructor
    // the format specifies the properties of the rendering window
    PostureGLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);

    virtual void drag(double x, double y, double z);
    void drag_starting();
    void drag_finished();

signals:
    void view_joint_fabrik_moved(const DCoordinate3&);
};
