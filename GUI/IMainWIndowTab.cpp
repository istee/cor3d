#include <QTabWidget>

#include "IMainWindowTab.h"
#include "glwidget.h"

IMainWindowTab::IMainWindowTab(QWidget* parent = 0): QWidget(parent)
{
    cor3dApp = (Cor3dApplication*) qApp;

    _isSelected = false;
}

void IMainWindowTab::setGLWidgetTranslation(const DCoordinate3& translation)
{
    glwidget->set_translation(translation);
}

void IMainWindowTab::setGLWidgetRotation(const DCoordinate3& angles)
{
    glwidget->set_rotation(angles);
}

void IMainWindowTab::setGLWidgetZoomFactor(double zoom)
{
    glwidget->set_zoom_factor(zoom);
}

void IMainWindowTab::setSelected(bool selected)
{
    _isSelected = selected;
}

void IMainWindowTab::updateGLWidget() const
{
    if (_isSelected)
    {
        glwidget->updateGL();
    }
}
