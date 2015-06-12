#include "PostureGLWidget.h"

#include "Cor3dApplication.h"

PostureGLWidget::PostureGLWidget(QWidget *parent, const QGLFormat &format): GLWidget(parent, format)
{

}

DCoordinate3 PostureGLWidget::dragCoordinate()
{
    return _skeleton->getSelectedPosture()->getAbsolutePostureCoordinate(_skeleton->getSelectedPosture()->selectedJoint()->getId());
}

void PostureGLWidget::specificPaintGL()
{
    if (_skeleton)
    {
        if (_skeleton->getSelectedPosture())
        {
            RenderingOptions* rendering_options = cor3dApp->cor3d->getRenderingOptions();
            _skeleton->getSelectedPosture()->renderPosture(rendering_options, true);
            if (_skeleton->getSelectedJoint() && _skeleton->getSelectedJoint()->getId() > 0)
            {
                DCoordinate3 position = _skeleton->getSelectedPosture()->getAbsolutePostureCoordinate(_skeleton->getSelectedJoint()->getId());
                render_move_arrows(rendering_options, &position);
            }
        }
    }
}

void PostureGLWidget::specificDrawPickObjects()
{
    if (_skeleton->getSelectedPosture())
    {
        _skeleton->getSelectedPosture()->renderPostureJoints(cor3dApp->cor3d->getRenderingOptions(), true);

        if (_skeleton->getSelectedJoint() && _skeleton->getSelectedJoint()->getId() > 0)
        {
            DCoordinate3 selected_position = _skeleton->getSelectedPosture()->getAbsolutePostureCoordinate(_skeleton->getSelectedJoint()->getId());

            render_move_arrows(cor3dApp->cor3d->getRenderingOptions(), &selected_position, _skeleton->getJointCount(), true);
        }
    }
}

int PostureGLWidget::specificPickCount()
{
    GLuint size = 4 * _skeleton->getJointCount();
    if (_skeleton->getSelectedJoint())
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
        emit viewJointSelected(closestSelected - 6);
    }
}

void PostureGLWidget::drag(double x, double y, double z)
{
    //_skeleton->getSelectedPosture()->MoveSelected(x, y, z);
    emit viewPostureJointAbsoluteCoordinatesChanged(DCoordinate3(x, y, z));
}

void PostureGLWidget::drag_starting()
{
    //_skeleton->getSelectedPosture()->constructChains(_skeleton->get_selectedJoint_id());
    GLWidget::drag_starting();
}

void PostureGLWidget::drag_finished()
{
    //_skeleton->getSelectedPosture()->FinalizeMove();
    //_skeleton->getSelectedPosture()->clearChains();
    GLWidget::drag_finished();
}
