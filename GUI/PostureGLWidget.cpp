#include "PostureGLWidget.h"

#include "Cor3dApplication.h"

PostureGLWidget::PostureGLWidget(QWidget *parent, const QGLFormat &format): GLWidget(parent, format)
{

}

void PostureGLWidget::specificPaintGL()
{
    if (_skeleton)
    {
        if (_skeleton->selectedPosture())
        {
            cout << "draw posture " << _skeleton->selectedPosture()->get_name() << endl;

            RenderingOptions* rendering_options = cor3dApp->cor3d->get_rendering_options();
            _skeleton->render_joints(rendering_options);
            _skeleton->render_links(rendering_options);
            MatFBRuby.Apply();
            _skeleton->render_chains(rendering_options);
            if (_skeleton->is_joint_selected())
            {
                unsigned int joint_id = _skeleton->get_selected_joint_id();
                DCoordinate3 position = _skeleton->get_joint(joint_id)->get_coordinates();
                render_move_arrows(rendering_options, &position);
            }
        }
    }
}

void PostureGLWidget::drag(double x, double y, double z)
{
    emit view_joint_fabrik_moved(DCoordinate3(x, y, z));
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
