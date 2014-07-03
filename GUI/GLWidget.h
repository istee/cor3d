#pragma once

// GLU was removed from Qt starting from version 4.8

#include <GL/glew.h>
#include <QGLWidget>
#include <QGLFormat>
#include  <vector>
#include <QTimer>

#include <QMouseEvent>
#include <QPoint>

#include "../Model/Skeleton.h"
#include "../Core/Lights.h"
#include "../Core/DCoordinates3.h"
#include "../Core/Matrices.h"

class GLWidget: public QGLWidget
{
    Q_OBJECT

private:

    // variables defining the projection matrix
    float       _aspect;            // aspect ratio of the rendering window
    float       _fovy;              // field of view in direction y
    float       _z_near, _z_far;    // distance of near and far clipping planes

    // variables defining the model-view matrix
    float       _eye[3], _center[3], _up[3];

    // variables needed by transformations
    int         _angle_x, _angle_y, _angle_z;
    double      _zoom;
    double      _trans_x, _trans_y, _trans_z;

    int               _point_count;
    std::vector<float> _x, _y, _z;

    unsigned int        _dl;

    cagd::DirectionalLight  *_dir_light;

    cagd::TriangulatedMesh3 cone, sphere, cube;

    double                  _reposition_unit;

    cagd::XRotationMatrix x_rot_mat;
    cagd::YRotationMatrix y_rot_mat;
    cagd::ZRotationMatrix z_rot_mat;

    double                  mouse_pressed_x, mouse_pressed_y;
    double                  mouse_pressed_trans_x, mouse_pressed_trans_y, mouse_pressed_trans_z;

    std::vector<cagd::Skeleton>   _skeletons;

    bool drag;
    unsigned int _drag_type;
    cagd::DCoordinate3 _drag_offset;
    cagd::ColumnMatrix<double> _initial_normal;

    GLuint _dl_grid;

    void RenderMoveArrows(cagd::DCoordinate3 *position, bool glLoad = false);

public:
    // special and default constructor
    // the format specifies the properties of the rendering window
    GLWidget(QWidget* parent = 0, const QGLFormat& format = QGL::Rgba | QGL::DepthBuffer | QGL::DoubleBuffer);

    // redeclared virtual functions
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    // protected:
    // paintGL, _select_mode = true | false
    // process hits, unsigned int * _select_buffer
    //

    ~GLWidget();

public slots:
    // public event handling methods/slots
    void set_angle_x(int value);
    void set_angle_y(int value);
    void set_angle_z(int value);

    void set_zoom_factor(double value);

    void set_trans_x(double value);
    void set_trans_y(double value);
    void set_trans_z(double value);
    void set_render_mesh(int skeleton_id, bool value);
    void set_render_links(int skeleton_id, bool value);
    void set_render_joints(int skeleton_id, bool value);

signals:
    void zoomChanged(double newValue);
    void trans_xChanged(double newValue);
    void trans_yChanged(double newValue);
    void trans_zChanged(double newValue);
};
