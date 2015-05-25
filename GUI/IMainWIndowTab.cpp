#include "IMainWindowTab.h"

IMainWindowTab::IMainWindowTab(QWidget* parent = 0): QWidget(parent)
{
    cor3dApp = (Cor3dApplication*) qApp;
}

void IMainWindowTab::viewTranslationChanged(const DCoordinate3& translation)
{
    glwidget->set_translation(translation);
    glwidget->updateGL();
}

void IMainWindowTab::viewRotationChanged(const DCoordinate3& angles)
{
    glwidget->set_rotation(angles);
    glwidget->updateGL();
}

void IMainWindowTab::viewZoomFactorChanged(double zoom)
{
    glwidget->set_zoom_factor(zoom);
    glwidget->updateGL();
}
