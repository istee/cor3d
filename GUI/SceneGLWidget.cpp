#include "SceneGLWidget.h"

SceneGLWidget::SceneGLWidget(QWidget *parent, const QGLFormat &format): GLWidget(parent, format)
{

}

void SceneGLWidget::specificPaintGL()
{
    Skeleton* skeleton = cor3dApp->cor3d->get_skeleton();
    if (skeleton)
    {
        skeleton->render(cor3dApp->cor3d->get_rendering_options());
        if (skeleton->is_joint_selected())
        {
            unsigned int joint_id = skeleton->get_selected_joint_id();
            DCoordinate3 position = skeleton->get_joint(joint_id)->get_coordinates();
            render_move_arrows(cor3dApp->cor3d->get_rendering_options(), &position);
        }
    }
}

void SceneGLWidget::specificDrawPickObjects()
{

}

int SceneGLWidget::specificPickCount()
{

}

void SceneGLWidget::specificPick(unsigned int closestSelected)
{

}
