#include "SkeletonGLWidget.h"

#include "Cor3dApplication.h"

#include "Core/DCoordinates3.h"

SkeletonGLWidget::SkeletonGLWidget(QWidget *parent, const QGLFormat &format): GLWidget(parent, format)
{

}

DCoordinate3 SkeletonGLWidget::dragCoordinate()
{
    return _skeleton->getSelectedJoint()->get_coordinates();
}

void SkeletonGLWidget::specificPaintGL()
{
    Skeleton* skeleton = _skeleton;
    if (skeleton)
    {
        skeleton->render(cor3dApp->cor3d->getRenderingOptions());
        if (skeleton && skeleton->getSelectedJoint() && skeleton->getSelectedJoint()->get_parent() >= 0)
        {
            unsigned int joint_id = skeleton->getSelectedJoint()->getId();
            DCoordinate3 position = skeleton->getJointById(joint_id)->get_coordinates();
            render_move_arrows(cor3dApp->cor3d->getRenderingOptions(), &position);
        }
    }
}

void SkeletonGLWidget::specificDrawPickObjects()
{
    _skeleton->renderJoints(_renderingOptions, true);
    Joint* selectedJoint = _skeleton->getSelectedJoint();
    if (selectedJoint && selectedJoint->get_parent() >= 0)
    {
        DCoordinate3 selected_position = _skeleton->getSelectedJoint()->get_coordinates();

        render_move_arrows(_renderingOptions, &selected_position, _skeleton->getJointCount(), true);
    }
}

int SkeletonGLWidget::specificPickCount()
{
    GLuint size = 4 * _skeleton->getJointCount();
    if (_skeleton->getSelectedJoint())
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
        emit viewJointSelected(closestSelected - 6);
    }
}

void SkeletonGLWidget::drag(double x, double y, double z)
{
    emit viewJointAbsoluteCoordinatesChanged(DCoordinate3(x, y, z));
}
