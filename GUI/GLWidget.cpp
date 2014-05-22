#include "GLWidget.h"


//--------------------------------
// special and default constructor
//--------------------------------
GLWidget::GLWidget(QWidget *parent, const QGLFormat &format): QGLWidget(format, parent)
{
    _timer = new QTimer(this);
    _timer->setInterval(0);

    connect(_timer, SIGNAL(timeout()), this, SLOT(_animate()));

    //std::cout << "Test cout";
    _skeleton = 0;
    _skeleton = new cagd::Skeleton(new cagd::DCoordinate3( 0.0,  0.0, 0.0), new cagd::DCoordinate3( 0.0,  4.0, 0.0));

    if (_skeleton)
    {
            _skeleton->AddLink(2, new cagd::DCoordinate3(0.0, 5.0, 0.0));
            _skeleton->AddLink(2, new cagd::DCoordinate3(3.0, 3.8, 0.5));
            _skeleton->AddLink(2, new cagd::DCoordinate3(-3.0, 3.7, 0.4));
            _skeleton->AddLink(4, new cagd::DCoordinate3(4.0, 4.8, 0.4));
            _skeleton->AddLink(5, new cagd::DCoordinate3(-4.0, 4.7, 0.4));
            _skeleton->AddLink(1, new cagd::DCoordinate3(2.0, -4.0, 0.0));
            _skeleton->AddLink(1, new cagd::DCoordinate3(-2.0, -4.0, 0.0));
            _skeleton->AddLink(8, new cagd::DCoordinate3(1.5, -7.0, 0.0));
            _skeleton->AddLink(9, new cagd::DCoordinate3(-1.5, -7.0, 0.0));
            /*
            (*_skeleton)[0] = cagd::DCoordinate3( 0.0,  0.0, 0.0);
            (*_skeleton)[1] = cagd::DCoordinate3( 0.0,  1.0, 0.0);
            (*_skeleton)[2] = cagd::DCoordinate3( 1.0, -1.0, 0.0);
            (*_skeleton)[3] = cagd::DCoordinate3( 0.0,  2.0, 0.0);
            (*_skeleton)[4] = cagd::DCoordinate3( 2.0, -1.0, 0.0);
            (*_skeleton)[5] = cagd::DCoordinate3( 1.0,  2.0, 0.0);
            (*_skeleton)[6] = cagd::DCoordinate3( 2.0, -2.0, 0.0);
            (*_skeleton)[7] = cagd::DCoordinate3( 1.0,  1.0, 0.0);
            (*_skeleton)[8] = cagd::DCoordinate3( 1.0, -2.0, 0.0);
            (*_skeleton)[9] = cagd::DCoordinate3( 3.0, -2.0, 0.0);

            _skeleton->AddLink(0, 0, 1);
            _skeleton->AddLink(0, 0, 2);
            // ...
            */
    }

}

GLWidget::~GLWidget()
{
    if (_dl)
    {
        glDeleteLists(_dl, 1);
    }
}

//--------------------------------------------------------------------------------------
// this virtual function is called once before the first call to paintGL() or resizeGL()
//--------------------------------------------------------------------------------------
void GLWidget::initializeGL()
{
    // creating a perspective projection matrix
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    _aspect = (float)width() / (float)height();
    _z_near = 1.0;
    _z_far = 1000.0;
    _fovy = 45.0;

    gluPerspective(_fovy, _aspect, _z_near, _z_far);

    // setting the model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _eye[0] = _eye[1] = 0.0, _eye[2] = 6.0;
    _center[0] = _center[1] = _center[2] = 0.0;
    _up[0] = _up[2] = 0.0, _up[1] = 1.0;

    gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

    // enabling depth test
    glEnable(GL_DEPTH_TEST);

    // setting the color of background
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // initial values of transformation parameters
    _zoom = 1.0;
    _angle_x = _angle_y = _angle_z = 0.0;
    _trans_x = _trans_y = _trans_z = 0.0;

    _point_count = 500000;

    for ( int i = 0; i < _point_count; ++i)
    {
        _x.push_back(-1.0 + 2.0 * (float)rand() / (float)RAND_MAX);
        _y.push_back(-1.0 + 2.0 * (float)rand() / (float)RAND_MAX);
        _z.push_back(-1.0 + 2.0 * (float)rand() / (float)RAND_MAX);
    }

    _dl = 0;
    _dl = glGenLists(1);

    if (_dl)
    {
        glNewList(_dl, GL_COMPILE);
            glBegin(GL_LINES);
            for (int i = 0; i < _point_count; ++i)
            {
                glColor3f(_x[i], _y[i], _z[i]);
                glVertex3f(_x[i], _y[i], _z[i]);
            }
            glEnd();
        glEndList();
    }

    _angle = 0;

    _timer->start();
}

//-----------------------
// the rendering function
//-----------------------
void GLWidget::paintGL()
{
    // clears the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // stores/duplicates the original model view matrix
    glPushMatrix();

        // applying transformations
        glRotatef(_angle_x, 1.0, 0.0, 0.0);
        glRotatef(_angle_y, 0.0, 1.0, 0.0);
        glRotatef(_angle_z, 0.0, 0.0, 1.0);

        glTranslated(_trans_x, _trans_y, _trans_z);

        glScaled(_zoom, _zoom, _zoom);

        // render something
//        glBegin(GL_TRIANGLES);
//            glColor3f(1.0, 0.0, 0.0);
//            glVertex3f(1.0, 0.0, 0.0);

//            glColor3f(0.0, 1.0, 0.0);
//            glVertex3f(0.0, 1.0, 0.0);

//            glColor3f(0.0, 0.0, 1.0);
//            glVertex3f(0.0, 0.0, 1.0);
//        glEnd();

        /*if (_dl)
        {
            glPushMatrix();
            glRotatef(_angle, 1.0, 1.0, 1.0);
            glCallList(_dl);
//            glBegin(GL_LINES);
//            for (int i = 0; i < _point_count; ++i)
//            {
//                glColor3f(_x[i], _y[i], _z[i]);
//                glVertex3f(_x[i], _y[i], _z[i]);
//            }
//            glEnd();
            glPopMatrix();
        }
        */

        if (_skeleton)
        {
            glColor3f(1.0, 0.0, 0.0);
            _skeleton->RenderLinks();
        }

    // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
    // i.e., the original model view matrix is restored
    glPopMatrix();
}

//----------------------------------------------------------------------------
// when the main window is resized one needs to redefine the projection matrix
//----------------------------------------------------------------------------
void GLWidget::resizeGL(int w, int h)
{
    // setting the new size of the rendering context
    glViewport(0, 0, w, h);

    // redefining the projection matrix
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    _aspect = (float)w / (float)h;

    gluPerspective(_fovy, _aspect, _z_near, _z_far);

    // switching back to the model view matrix
    glMatrixMode(GL_MODELVIEW);

    updateGL();
}

//-----------------------------------
// implementation of the public slots
//-----------------------------------

void GLWidget::set_angle_x(int value)
{
    if (_angle_x != value)
    {
        _angle_x = value;
        updateGL();
    }
}

void GLWidget::set_angle_y(int value)
{
    if (_angle_y != value)
    {
        _angle_y = value;
        updateGL();
    }
}

void GLWidget::set_angle_z(int value)
{
    if (_angle_z != value)
    {
        _angle_z = value;
        updateGL();
    }
}

void GLWidget::set_zoom_factor(double value)
{
    if (_zoom != value)
    {
        _zoom = value;
        updateGL();
    }
}

void GLWidget::set_trans_x(double value)
{
    if (_trans_x != value)
    {
        _trans_x = value;
        updateGL();
    }
}

void GLWidget::set_trans_y(double value)
{
    if (_trans_y != value)
    {
        _trans_y = value;
        updateGL();
    }
}

void GLWidget::set_trans_z(double value)
{
    if (_trans_z != value)
    {
        _trans_z = value;
        updateGL();
    }
}

void GLWidget::_animate()
{
    _angle += 1;

    if (_angle >= 360)
        _angle -= 360;

    updateGL();
}
