#include "SkeletonGLWidget.h"

#include "Cor3dApplication.h"

SkeletonGLWidget::SkeletonGLWidget(QWidget *parent, const QGLFormat &format): GLWidget(parent, format)
{

}


void SkeletonGLWidget::specificPaintGL()
{
    Skeleton* skeleton = _skeleton;
    if (skeleton)
    {
        skeleton->render(cor3dApp->cor3d->get_rendering_options());
        if (skeleton && skeleton->is_joint_selected())
        {
            unsigned int joint_id = skeleton->get_selected_joint_id();
            DCoordinate3 position = skeleton->get_joint(joint_id)->get_coordinates();
            render_move_arrows(cor3dApp->cor3d->get_rendering_options(), &position);
        }
    }
}

void SkeletonGLWidget::specificDrawPickObjects()
{
    _skeleton->render_joints(cor3dApp->cor3d->get_rendering_options(), true);

    if (_skeleton->is_joint_selected())
    {
        DCoordinate3 selected_position = _skeleton->get_selected_joint()->get_coordinates();

        render_move_arrows(cor3dApp->cor3d->get_rendering_options(), &selected_position, _skeleton->get_joint_count(), true);
    }
}

int SkeletonGLWidget::specificPickCount()
{
    GLuint size = 4 * _skeleton->get_joint_count();
    if (_skeleton->is_joint_selected())
    {
        size += 24;
    }
    return size;
}

void SkeletonGLWidget::specificPick(unsigned int closestSelected)
{
    if (closestSelected < 6)
    {
        is_drag = true;
        _drag_type = closestSelected;
        this->drag_starting();
    }
    else
    {
        emit view_joint_selection_changed(closestSelected - 6);
    }
}
