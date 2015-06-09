#include "SceneGLWidget.h"

SceneGLWidget::SceneGLWidget(QWidget *parent, const QGLFormat &format): GLWidget(parent, format)
{

}

void SceneGLWidget::specificPaintGL()
{
    Skeleton* skeleton = cor3dApp->cor3d->getSelectedSkeleton();
    if (skeleton)
    {
        skeleton->render(cor3dApp->cor3d->getRenderingOptions());
        if (skeleton->is_joint_selected())
        {
            unsigned int joint_id = skeleton->get_selectedJoint_id();
            DCoordinate3 position = skeleton->get_joint(joint_id)->get_coordinates();
            render_move_arrows(cor3dApp->cor3d->getRenderingOptions(), &position);
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
