#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUi(this);

/*

  the structure of the main window's central widget

 *------------------------------------------------------*
 |                    central widget                    |
 |                                                      |
 |  *--*---------------------------*-----------------*  |
 |  |  |     rendering context     |   scroll area   |  |
 |  |  |       OpenGL widget       | *-------------* |  |
 |  |  |                           | | side widget | |  |
 |  |  |                           | |             | |  |
 |  |  |                           | |             | |  |
 |  |  |                           | *-------------* |  |
 |  *--*---------------------------*-----------------*  |
 |                                                      |
 *------------------------------------------------------*

*/
    _side_widget = new SideWidget(this);

    _scroll_area = new QScrollArea(this);
    _scroll_area->setWidget(_side_widget);
    _scroll_area->setSizePolicy(_side_widget->sizePolicy());
    _scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    _gl_widget = new GLWidget(this);
//    QWidget *window;
//    window = new QWidget(this);
//    _section_x = new GLWidget(window);
//    _section_x->set_angle_x(0);
//    _section_x->set_angle_y(0);
//    _section_x->set_angle_z(0);
//    _section_y = new GLWidget(window);
//    _section_y->set_angle_x(0);
//    _section_y->set_angle_y(90);
//    _section_y->set_angle_z(0);
//    _section_z = new GLWidget(window);
//    _section_z->set_angle_x(0);
//    _section_z->set_angle_y(90);
//    _section_z->set_angle_z(90);
//    window->setLayout(new QVBoxLayout());
//    window->layout()->addWidget(_section_x);
//    window->layout()->addWidget(_section_y);
//    window->layout()->addWidget(_section_z);

    centralWidget()->setLayout(new QHBoxLayout());
//    centralWidget()->layout()->addWidget(window);
    centralWidget()->layout()->addWidget(_gl_widget);
    centralWidget()->layout()->addWidget(_scroll_area);

    // creating a signal slot mechanism between the rendering context and the side widget
    connect(_side_widget->rotate_x_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_x(int)));
    connect(_side_widget->rotate_y_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_y(int)));
    connect(_side_widget->rotate_z_slider, SIGNAL(valueChanged(int)), _gl_widget, SLOT(set_angle_z(int)));

    connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_zoom_factor(double)));

    connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_x(double)));
    connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_y(double)));
    connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _gl_widget, SLOT(set_trans_z(double)));

    connect(_gl_widget, SIGNAL(zoomChanged(double)), _side_widget, SLOT(set_zoom_factor(double)));
    connect(_gl_widget, SIGNAL(trans_xChanged(double)), _side_widget, SLOT(set_trans_x(double)));
    connect(_gl_widget, SIGNAL(trans_yChanged(double)), _side_widget, SLOT(set_trans_y(double)));
    connect(_gl_widget, SIGNAL(trans_zChanged(double)), _side_widget, SLOT(set_trans_z(double)));

//    connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _section_x, SLOT(set_zoom_factor(double)));
//    connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _section_y, SLOT(set_zoom_factor(double)));
//    connect(_side_widget->zoom_factor_spin_box, SIGNAL(valueChanged(double)), _section_z, SLOT(set_zoom_factor(double)));

//    connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _section_x, SLOT(set_trans_x(double)));
//    connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _section_x, SLOT(set_trans_y(double)));
//    connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _section_x, SLOT(set_trans_z(double)));
//    connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _section_y, SLOT(set_trans_x(double)));
//    connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _section_y, SLOT(set_trans_y(double)));
//    connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _section_y, SLOT(set_trans_z(double)));
//    connect(_side_widget->trans_x_spin_box, SIGNAL(valueChanged(double)), _section_z, SLOT(set_trans_x(double)));
//    connect(_side_widget->trans_y_spin_box, SIGNAL(valueChanged(double)), _section_z, SLOT(set_trans_y(double)));
//    connect(_side_widget->trans_z_spin_box, SIGNAL(valueChanged(double)), _section_z, SLOT(set_trans_z(double)));

}

//--------------------------------
// implementation of private slots
//--------------------------------
void MainWindow::on_action_Quit_triggered()
{
    qApp->exit(0);
}
