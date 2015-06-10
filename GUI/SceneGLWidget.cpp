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
        if (skeleton->getSelectedJoint())
        {
            unsigned int joint_id = skeleton->getSelectedJoint()->getId();
            DCoordinate3 position = skeleton->getJointById(joint_id)->get_coordinates();
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
