#include "PostureGLWidget.h"

#include "Cor3dApplication.h"

PostureGLWidget::PostureGLWidget(QWidget *parent, const QGLFormat &format): GLWidget(parent, format)
{

}

void PostureGLWidget::specificPaintGL()
{
    Skeleton* skeleton = cor3dApp->cor3d->get_skeleton();
    if (skeleton)
    {
        RenderingOptions* rendering_options = cor3dApp->cor3d->get_rendering_options();
        skeleton->render_joints(rendering_options);
        skeleton->render_links(rendering_options);
        MatFBRuby.Apply();
        skeleton->render_chains(rendering_options);
        if (skeleton->is_joint_selected())
        {
            unsigned int joint_id = skeleton->get_selected_joint_id();
            DCoordinate3 position = skeleton->get_joint_coordinates(joint_id);
            render_move_arrows(rendering_options, &position);
        }
    }
}

void PostureGLWidget::drag_starting()
{
    cor3dApp->cor3d->get_skeleton()->construct_chains();
    GLWidget::drag_starting();
}

void PostureGLWidget::drag_finished()
{
    cor3dApp->cor3d->get_skeleton()->clear_chains();
    GLWidget::drag_finished();
}
