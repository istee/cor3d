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
            RenderingOptions* rendering_options = cor3dApp->cor3d->get_rendering_options();
            _skeleton->selectedPosture()->renderPosture(rendering_options, true);
            if (_skeleton->is_joint_selected())
            {
                DCoordinate3 position = _skeleton->selectedPosture()->getAbsolutePostureCoordinate(_skeleton->get_selected_joint_id());
                render_move_arrows(rendering_options, &position);
            }
        }
    }
}

void PostureGLWidget::specificDrawPickObjects()
{
    _skeleton->selectedPosture()->renderPostureJoints(cor3dApp->cor3d->get_rendering_options(), true);

    if (_skeleton->is_joint_selected() && _skeleton->selectedPosture())
    {
        DCoordinate3 selected_position = _skeleton->selectedPosture()->getAbsolutePostureCoordinate(_skeleton->get_selected_joint_id());

        render_move_arrows(cor3dApp->cor3d->get_rendering_options(), &selected_position, _skeleton->get_joint_count(), true);
    }
}

int PostureGLWidget::specificPickCount()
{
    GLuint size = 4 * _skeleton->get_joint_count();
    if (_skeleton->is_joint_selected())
    {
        size += 24;
    }
    return size;
}

void PostureGLWidget::specificPick(unsigned int closestSelected)
{
    if (closestSelected < 6)
    {
        is_drag = true;
        _drag_type = closestSelected;
        this->drag_starting();
    }
    else
    {
        emit view_joint_selectionChanged(closestSelected - 6);
    }
}

void PostureGLWidget::drag(double x, double y, double z)
{
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
