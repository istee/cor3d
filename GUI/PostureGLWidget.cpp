#include "PostureGLWidget.h"

#include "Cor3dApplication.h"

PostureGLWidget::PostureGLWidget(QWidget *parent, const QGLFormat &format): GLWidget(parent, format)
{

}

void PostureGLWidget::specificPaintGL()
{
    cout << "paint " << endl;
    if (_skeleton)
    {
        cout << "paint skeleton" << endl;
        if (_skeleton->selectedPosture())
        {
            cout << "paint posture " << _skeleton->selectedPosture()->get_name() << endl;

            RenderingOptions* rendering_options = cor3dApp->cor3d->get_rendering_options();
            _skeleton->selectedPosture()->renderPosture(rendering_options, true);
            if (_skeleton->is_joint_selected())
            {
                unsigned int joint_id = _skeleton->get_selected_joint_id();
                DCoordinate3 position = _skeleton->get_joint(joint_id)->get_coordinates();
                render_move_arrows(rendering_options, &position);
            }
        }
    }
}

void PostureGLWidget::specificPick()
{

}

void PostureGLWidget::drag(double x, double y, double z)
{
    cout << "drag van " << x << " " << y << " " << z << endl;
    _skeleton->selectedPosture()->MoveSelected(x, y, z);
}

void PostureGLWidget::drag_starting()
{
    _skeleton->selectedPosture()->constructChains(_skeleton->get_selected_joint_id());
    GLWidget::drag_starting();
}

void PostureGLWidget::drag_finished()
{
    _skeleton->selectedPosture()->FinalizeMove();
    _skeleton->selectedPosture()->clearChains();
    GLWidget::drag_finished();
}
