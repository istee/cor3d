#include "GLWidget.h"
#include <math.h>

#include "../Core/Colors4.h"
#include "../Core/Materials.h"
#include "../Core/HCoordinates3.h"
#include "../Core/Constants.h"
#include "../Core/Transformations.h"

using namespace cagd;
using namespace std;

//--------------------------------
// special and default constructor
//--------------------------------
GLWidget::GLWidget(QWidget *parent, const QGLFormat &format): QGLWidget(format, parent)
{

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
    glewInit();

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

    TriangulatedMesh3 mesh;
    mesh.LoadFromOFF("Models/mouse.off");
    mesh.UpdateVertexBufferObjects();

    cone.LoadFromOFF("Models/cone.off");
    cone.UpdateVertexBufferObjects();

    sphere.LoadFromOFF("Models/sphere.off");
    sphere.UpdateVertexBufferObjects();

    cube.LoadFromOFF("Models/cube.off");
    cube.UpdateVertexBufferObjects();

    cagd::Skeleton sk = cagd::Skeleton(0, 0.1, -1.7, -1.5, mesh, &cone, &sphere);
    sk.AddLink(0, 0.1, 0.5, -0.7);
    sk.AddLink(1, 0.8, 0.4, -0.6);
    sk.AddLink(2, 1.9, 0.3, -0.55);
    sk.AddLink(3, 2.4, 0.3, -0.7);
    sk.AddLink(3, 2.5, 0.3, -0.55);
    sk.AddLink(3, 2.45, 0.3, -0.4);
    sk.AddLink(3, 2.1, 0.3, -0.2);
    sk.AddLink(0, 0.9, -2.3, -0.85);
    sk.AddLink(8, 0.9, -2.3, 0.7);
    sk.AddLink(0, 0.1, -1.9, -2.65);
    sk.AddLink(10, 0.1, -2.1, -3.8);
    _skeletons.push_back(sk);

    //cout << _skeletons[0] << endl;
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    _dir_light = 0;
    _dir_light = new DirectionalLight(
            GL_LIGHT0,
            HCoordinate3(0.0, 0.0, 1.0, 0.0),
            Color4(0.4, 0.4, 0.4, 1.0),
            Color4(0.8, 0.8, 0.8, 1.0),
            Color4(1.0, 1.0, 1.0, 1.0));

    _dir_light->Enable();

    _reposition_unit = 0.1;

    drag = false;

    // Rotation matrix, plane normal vetor test
    RowMatrix<int> angles = RowMatrix<int>(3);
    _initial_normal = ColumnMatrix<double>(3);
    _initial_normal[0] = 0.0;
    _initial_normal[1] = 0.0;
    _initial_normal[2] = 1.0;
    Matrix<double> result;
    DCoordinate3 result_vector;

    angles[0] = 0;
    angles[1] = 0;
    angles[2] = 0;
    x_rot_mat = XRotationMatrix(angles[0]);
    y_rot_mat = YRotationMatrix(angles[1]);
    z_rot_mat = ZRotationMatrix(angles[2]);
    result = x_rot_mat * y_rot_mat * z_rot_mat * _initial_normal;
    result_vector = DCoordinate3(result(0,0), result(1, 0), result(2, 0));
    result_vector.normalize();
    //cout << x_rot_mat << y_rot_mat << z_rot_mat << result;
    //cout << angles << result_vector << endl << endl;

    angles[0] = 90;
    angles[1] = 0;
    angles[2] = 0;
    x_rot_mat = XRotationMatrix(angles[0]);
    y_rot_mat = YRotationMatrix(angles[1]);
    z_rot_mat = ZRotationMatrix(angles[2]);
    result = x_rot_mat * y_rot_mat * z_rot_mat * _initial_normal;
    result_vector = DCoordinate3(result(0,0), result(1, 0), result(2, 0));
    result_vector.normalize();
    //cout << x_rot_mat << y_rot_mat << z_rot_mat << result;
    //cout << angles << result_vector << endl << endl;

    angles[0] = 0;
    angles[1] = 90;
    angles[2] = 0;
    x_rot_mat = XRotationMatrix(angles[0]);
    y_rot_mat = YRotationMatrix(angles[1]);
    z_rot_mat = ZRotationMatrix(angles[2]);
    result = x_rot_mat * y_rot_mat * z_rot_mat * _initial_normal;
    result_vector = DCoordinate3(result(0,0), result(1, 0), result(2, 0));
    result_vector.normalize();
    //cout << x_rot_mat << y_rot_mat << z_rot_mat << result;
    //cout << angles << result_vector << endl << endl;

    angles[0] = 0;
    angles[1] = 0;
    angles[2] = 90;
    x_rot_mat = XRotationMatrix(angles[0]);
    y_rot_mat = YRotationMatrix(angles[1]);
    z_rot_mat = ZRotationMatrix(angles[2]);
    result = x_rot_mat * y_rot_mat * z_rot_mat * _initial_normal;
    result_vector = DCoordinate3(result(0,0), result(1, 0), result(2, 0));
    result_vector.normalize();
    //cout << x_rot_mat << y_rot_mat << z_rot_mat << result;
    //cout << angles << result_vector << endl << endl;

    GLdouble x_min = -3.0, x_max = 3.0;
    GLdouble y_min = -3.0, y_max = 3.0;
    GLdouble z_min = -3.0, z_max = 3.0;

    GLuint div = 10;

    GLdouble dx = (x_max - x_min) / (div - 1);
    GLdouble dy = (y_max - y_min) / (div - 1);
    GLdouble dz = (z_max - z_min) / (div - 1);

    _dl_grid = 0;
    _dl_grid = glGenLists(1);

    glNewList(_dl_grid, GL_COMPILE);

        glPointSize(5.0);
        glBegin(GL_POINTS);

            for (GLuint i = 0; i < div; ++i)
            {
                GLdouble x = x_min + i * dx;

                for (GLuint j = 0; j < div; ++j)
                {
                    GLdouble y = y_min + j * dy;

                    for (GLuint k = 0; k < div; ++k)
                    {
                        GLdouble z = z_min + k * dz;

                        glColor3d(x, y, z);
                        glVertex3d(x, y, z);
                    }
                }

            }

        glEnd();

        glPointSize(1.0);

    glEndList();

}

//-----------------------
// the rendering function
//-----------------------
void GLWidget::paintGL()
{
    // clears the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // stores/duplicates the original model view matrix
    glPushMatrix();

        // applying transformations
        glRotatef(_angle_x, 1.0, 0.0, 0.0);
        glRotatef(_angle_y, 0.0, 1.0, 0.0);
        glRotatef(_angle_z, 0.0, 0.0, 1.0);

        glTranslated(_trans_x, _trans_y, _trans_z);

        glScaled(_zoom, _zoom, _zoom);

        glDisable(GL_LIGHTING);
        //glCallList(_dl_grid);


        glBegin(GL_LINES);
            float modelViewMatrix[16];
            glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);
//            cout << "matrix: " << endl;
//            for (int i = 0; i < 4; i++)
//            {
//                cout << modelViewMatrix[i * 4] << " " << modelViewMatrix[i * 4 + 1] << " " << modelViewMatrix[i * 4 + 2] << " " << modelViewMatrix[i * 4 + 3] << endl;
//            }
            //glColor3f(1.0, 0.0, 0.0);
            //glVertex3f(0.0, 0.0, 0.0);
            //glVertex3f(modelViewMatrix[2], modelViewMatrix[6], modelViewMatrix[11]);

            x_rot_mat = XRotationMatrix(_angle_x);
            y_rot_mat = YRotationMatrix(_angle_y);
            z_rot_mat = ZRotationMatrix(_angle_z);
            ColumnMatrix<double> z_unit = ColumnMatrix<double>(3);
            z_unit[0] = 0.0;
            z_unit[1] = 0.0;
            z_unit[2] = 1.0;

            Matrix<double> normal = x_rot_mat * y_rot_mat * z_rot_mat * z_unit;
            //cout << normal << endl;
            //glColor3f(1.0, 0.0, 0.0);
            //glVertex3f(0, 0, 0);
            //glVertex3f(normal(0,0), normal(1, 0), normal(2,0));
        glEnd();

        glEnable(GL_LIGHTING);
        for(std::vector<cagd::Skeleton>::iterator it = _skeletons.begin(); it != _skeletons.end(); ++it) {
            it->Render(false);
        }

//        glDisable(GL_LIGHTING);
//        glBegin(GL_TRIANGLES);
//        glColor3f(1.0, 0.0, 0.0);
//        glVertex3f(1.0, 0.0, 0.0);
//        glColor3f(0.0, 1.0, 0.0);
//        glVertex3f(0.0, 1.0, 0.0);
//        glColor3f(0.0, 0.0, 1.0);
//        glVertex3f(0.0, 0.0, 1.0);
//        glEnd();

        DCoordinate3 *selected_position = _skeletons[0].GetSelectedPosition();
        if (selected_position)
        {
            RenderMoveArrows(selected_position);
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

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    mouse_pressed_x = event->x();
    mouse_pressed_y = event->y();
    mouse_pressed_trans_x = _trans_x;
    mouse_pressed_trans_y = _trans_y;
    mouse_pressed_trans_z = _trans_z;
    if (event->button() == Qt::LeftButton)
    {
        GLint viewport[4];

        glGetIntegerv(GL_VIEWPORT, viewport);

        GLuint size = 4 * _skeletons[0].JointCount();
        GLuint *pick_buffer = new GLuint[size];
        if (pick_buffer)
        {
            glSelectBuffer(size, pick_buffer);

            glRenderMode(GL_SELECT);


            glInitNames();
            glPushName(0);

            GLfloat projection_matrix[16];
            glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix);

            glMatrixMode(GL_PROJECTION);

            glPushMatrix();


                glLoadIdentity();
                gluPickMatrix((GLdouble)event->x(), (GLdouble)(viewport[3] - event->y()), 5.0, 5.0, viewport);

                glMultMatrixf(projection_matrix);

                glMatrixMode(GL_MODELVIEW);


                glPushMatrix();

                // rotating around the coordinate axes
                glRotatef(_angle_x, 1.0, 0.0, 0.0);
                glRotatef(_angle_y, 0.0, 1.0, 0.0);
                glRotatef(_angle_z, 0.0, 0.0, 1.0);


                // translate
                glTranslated(_trans_x, _trans_y, _trans_z);

                // scaling
                glScalef(_zoom, _zoom, _zoom);

                DCoordinate3 *selected_position = _skeletons[0].GetSelectedPosition();
                if (selected_position)
                {
                    RenderMoveArrows(selected_position, true);
                }

                // a kiválasztáshoz elégséges csak a joint-okat kirajzolni
                _skeletons[0].RenderJoints(true, 6); // ahol true a glLoadName() függvény alkalmazását aktíválja
                    // ahogy bejárod a skeleton joint-jait a glLoadName függvénynek az egyes joint-ok id-ját kell átadnod
                }


            glPopMatrix();

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();

            glMatrixMode(GL_MODELVIEW);

            int nhits = glRenderMode(GL_RENDER);

            if (nhits)
            {
                GLuint closest_selected = pick_buffer[3];
                GLuint closest_depth    = pick_buffer[1];


                for (GLuint i = 1; i < nhits; ++i)
                {
                    GLuint offset = i * 4;
                    if (pick_buffer[offset + 1] < closest_depth)

                    {
                        closest_selected = pick_buffer[offset + 3];
                        closest_depth    = pick_buffer[offset + 1];
                    }
                }

                if (closest_selected < 6)
                {
                    drag = true;
                    _drag_type = closest_selected;
                }
                else
                {
                    _skeletons[0].SetSelected(closest_selected - 6);
                }
            }
            else
            {
                drag = false;
                _skeletons[0].SetSelected(-1);
            }

            delete pick_buffer, pick_buffer = 0;
            updateGL();
        }

    // test
    GLint viewport[4]; //var to hold the viewport info
    GLdouble modelview[16]; //var to hold the modelview info
    GLdouble projection[16]; //var to hold the projection matrix info
    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    winX = (float)event->x();
    winY = (float)viewport[3] - (float)event->y();
    winZ = 1.0;

    float modelViewMatrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf(modelViewMatrix);

    cout << worldX << " " << worldY << " " << worldZ << endl;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    if (drag)
    {
        x_rot_mat = XRotationMatrix(_angle_x);
        y_rot_mat = YRotationMatrix(_angle_y);
        z_rot_mat = ZRotationMatrix(_angle_z);

        double matModelView[16], matProjection[16];
        int viewport[4];

        // get matrix and viewport:
        glGetDoublev( GL_MODELVIEW_MATRIX, matModelView );
        glGetDoublev( GL_PROJECTION_MATRIX, matProjection );
        glGetIntegerv( GL_VIEWPORT, viewport );

        Transformation TMV(matModelView);
        Transformation TIMV;

        if (TMV.GetInverse(TIMV))
        {
            Transformation TIMVT = TIMV.Transpose();
//            Matrix<double> normal = z_rot_mat * y_rot_mat * x_rot_mat * _initial_normal;
//            DCoordinate3 n = DCoordinate3(normal(0,0), normal(1,0), normal(2,0));
            DCoordinate3 n = TIMVT * DCoordinate3(0.0, 0.0, 1.0);
//            cout << "before normalizing: " << n << " , " << n.length() << endl;
            n.normalize();

            DCoordinate3 p0 = DCoordinate3(*(_skeletons[0].GetSelectedPosition()));

            double mouseX = event->x();
            double mouseY = event->y();

            DCoordinate3 l1;
            DCoordinate3 l2;
            double  x,  y,  z;


            // window pos of mouse, Y is inverted on Windows
            double winX = (double)mouseX;
            double winY = viewport[3] - (double)mouseY;

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            // get point on the 'near' plane (third param is set to 0.0)
            gluUnProject(winX, winY, 0.0, matModelView, matProjection, viewport, &x, &y, &z);
            l1 = DCoordinate3(x, y, z);

            // get point on the 'far' plane (third param is set to 1.0)
            gluUnProject(winX, winY, 1.0, matModelView, matProjection, viewport, &x, &y, &z);
            l2 = DCoordinate3(x, y, z);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glMultMatrixd(matModelView);

            double d = ((p0 - l1) * n) / ((l2 - l1) * n);

            cout << "d: " << d << endl;

            if (d >= 0.0 && d <= 1.0)
            {
                DCoordinate3 result = l1 + ((l2 - l1) * d);
                ColumnMatrix<double> result_matrix = ColumnMatrix<double>(3);
                result_matrix[0] = result[0];
                result_matrix[1] = result[1];
                result_matrix[2] = result[2];

                Matrix<double> rotated_result_matrix = z_rot_mat * y_rot_mat * x_rot_mat * result_matrix;
                result[0] = rotated_result_matrix(0, 0);
                result[1] = rotated_result_matrix(1, 0);
                result[2] = rotated_result_matrix(2, 0);
//                cout << "d: " << d << endl;
//                cout << "normal: " << n << endl;
//                cout << "p0: " << p0 << endl;
//                cout << "point: " << result << endl;


                DCoordinate3 *new_coord = _skeletons[0].GetSelectedPosition();
                if (_drag_type == 0)
                {
                    (*new_coord)[0] = result[0] - 1;
                    //_skeletons[0].MoveSelected(result[0] - 1, (*new_coord)[1], (*new_coord)[2]);
                }
                else if (_drag_type == 1)
                {
                    (*new_coord)[1] = result[1];
                    //_skeletons[0].MoveSelected((*new_coord)[0], result[1] - 1, (*new_coord)[2]);
                }
                else if (_drag_type == 2)
                {
                    (*new_coord)[2] = result[2];
                }
                else if (_drag_type == 3)
                {
                    (*new_coord)[1] = result[1] - 0.5;
                    (*new_coord)[2] = -result[2];
                }
                else if (_drag_type == 4)
                {
                    (*new_coord)[0] = result[0] - 0.5;
                    (*new_coord)[2] = -result[2];
                }
                else if (_drag_type == 5)
                {
                    (*new_coord)[0] = result[0] - 0.5;
                    (*new_coord)[1] = result[1] - 0.5;
                }
            }
        }
    }
    else
    {
        double disp_x = (event->x() - mouse_pressed_x) / 100.0;
        double disp_y = (mouse_pressed_y - event->y()) / 100.0;

//        double rad_x = _angle_x * PI / 180;
//        double rad_y = _angle_y * PI / 180;
//        double rad_z = _angle_z * PI / 180;

//        double sin_x = sin(rad_x);
//        double sin_y = sin(rad_y);
//        double sin_z = sin(rad_z);
//        double cos_x = cos(rad_x);
//        double cos_y = cos(rad_y);
//        double cos_z = cos(rad_z);

//        double new_trans_x, new_trans_y, new_trans_z;
//        new_trans_x = disp_x * (cos_y * cos_z) + disp_y * (cos_y * sin_z);
//        new_trans_y = disp_x * (sin_x * sin_y * cos_z) + disp_y * (cos_x * cos_z - sin_x * sin_y * sin_z);
//        new_trans_z = disp_x * (sin_x * sin_z - cos_x * sin_y * cos_z) + disp_y * (cos_x * sin_y * sin_z + sin_x * cos_z);

        x_rot_mat = XRotationMatrix(_angle_x);
        y_rot_mat = YRotationMatrix(_angle_y);
        z_rot_mat = ZRotationMatrix(_angle_z);
        ColumnMatrix<double> mouse = ColumnMatrix<double>(3);
        mouse[0] = disp_x;
        mouse[1] = disp_y;
        mouse[2] = 0.0;

        Matrix<double> normal = z_rot_mat * y_rot_mat * x_rot_mat * mouse;

        emit trans_xChanged(mouse_pressed_trans_x + normal(0,0));
        emit trans_yChanged(mouse_pressed_trans_y + normal(1,0));
        emit trans_zChanged(mouse_pressed_trans_z + normal(2,0));
    }


//    if (event->button() == Qt::LeftButton)
//    {
//        if (event->modifiers() & Qt::ShiftModifier)
//        {
//            Qt::AltModifier, Qt::ControlModifier
//        }
//    }
    updateGL();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    event->accept();
//    if (((event->modifiers() & Qt::ControlModifier) || (event->modifiers() & Qt::AltModifier) || (event->modifiers() & Qt::ShiftModifier)) && _joint_position)
//    {
//        if ((event->modifiers() & Qt::ControlModifier))

//        {
//            (*_joint_position)[0] += event->delta() / 120.0 * _reposition_unit;
//        }

//        if ((event->modifiers() & Qt::AltModifier))
//        {
//            (*_joint_position)[1] += event->delta() / 120.0 * _reposition_unit;

//        }

//        if ((event->modifiers() & Qt::ShiftModifier))
//        {
//            (*_joint_position)[2] += event->delta() / 120.0 * _reposition_unit;
//        }
//    }
//    else
    {
        double new_zoom = _zoom + event->delta() / 1200.0;
        if (new_zoom < 0.01)
            new_zoom = 0.01;

        emit zoomChanged(new_zoom);
    }

    updateGL();
}

void GLWidget::set_render_mesh(int skeleton_id, bool value)
{
    if (skeleton_id == -1)
    {
        for(std::vector<cagd::Skeleton>::iterator it = _skeletons.begin(); it != _skeletons.end(); ++it) {
            it->SetRenderMesh(value);
        }
    }
    updateGL();
}

void GLWidget::set_render_links(int skeleton_id, bool value)
{
    if (skeleton_id == -1)
    {
        for(std::vector<cagd::Skeleton>::iterator it = _skeletons.begin(); it != _skeletons.end(); ++it) {
            it->SetRenderLinks(value);
        }
    }
    updateGL();
}

void GLWidget::set_render_joints(int skeleton_id, bool value)
{
    if (skeleton_id == -1)
    {
        for(std::vector<cagd::Skeleton>::iterator it = _skeletons.begin(); it != _skeletons.end(); ++it) {
            it->SetRenderJoints(value);
        }
    }
    updateGL();
}

void GLWidget::RenderMoveArrows(DCoordinate3 *position, bool glLoad)
{
    double line_offset = 1;
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(position->x(), position->y(), position->z());
        glVertex3f(position->x() + line_offset, position->y(), position->z());

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(position->x(), position->y(), position->z());
        glVertex3f(position->x(), position->y() + line_offset, position->z());

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(position->x(), position->y(), position->z());
        glVertex3f(position->x(), position->y(), position->z() + line_offset);
    glEnd();

    float matrix[16];

    matrix[0] = 1;
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0.0;

    matrix[4] = 0;
    matrix[5] = 1;
    matrix[6] = 0;
    matrix[7] = 0.0;

    matrix[ 8] = 0;
    matrix[ 9] = 0;
    matrix[10] = 1;
    matrix[11] = 0.0;

    matrix[12] = position->x();
    matrix[13] = position->y();
    matrix[14] = position->z();
    matrix[15] = 1.0;

    glPushMatrix();
        MatFBRuby.Apply();
        glMultMatrixf(matrix);
        glScalef(0.01 / _zoom, 0.5 / _zoom, 0.5 / _zoom);
        if (glLoad)
        {
            glLoadName(3);
        }
        cube.Render();
    glPopMatrix();
    glPushMatrix();
        MatFBTurquoise.Apply();
        glMultMatrixf(matrix);
        glScalef(0.5 / _zoom, 0.01 / _zoom, 0.5 / _zoom);
        if (glLoad)
        {
            glLoadName(4);
        }
        cube.Render();
    glPopMatrix();
    glPushMatrix();
        MatFBEmerald.Apply();
        glMultMatrixf(matrix);
        glScalef(0.5 / _zoom, 0.5 / _zoom, 0.01 / _zoom);
        if (glLoad)
        {
            glLoadName(5);
        }
        cube.Render();
    glPopMatrix();

    matrix[12] += line_offset;
    glPushMatrix();
        MatFBRuby.Apply();
        glMultMatrixf(matrix);
        glRotatef(90, 0.0, 1.0, 0.0);
        //glRotatef(-90, 1.0, 0.0, 0.0);
        glScalef(0.1 / _zoom, 0.1 / _zoom, 0.3 / _zoom);
        glColor3f(1.0, 0.0, 0.0);
        if (glLoad)
        {
            glLoadName(0);
        }
        cone.Render();
    glPopMatrix();
    matrix[12] -= line_offset;

    matrix[13] += line_offset;
    glPushMatrix();
        MatFBTurquoise.Apply();
        glMultMatrixf(matrix);
        glRotatef(-90, 1.0, 0.0, 0.0);
        glScalef(0.1 / _zoom, 0.1 / _zoom, 0.3 / _zoom);
        glColor3f(0.0, 1.0, 0.0);
        if (glLoad)
        {
            glLoadName(1);
        }
        cone.Render();
    glPopMatrix();
    matrix[13] -= line_offset;

    matrix[14] += line_offset;
    glPushMatrix();
        MatFBEmerald.Apply();
        glMultMatrixf(matrix);
        glScalef(0.1 / _zoom, 0.1 / _zoom, 0.3 / _zoom);
        glColor3f(0.0, 0.0, 1.0);
        if (glLoad)
        {
            glLoadName(2);
        }
        cone.Render();
    glPopMatrix();
}
