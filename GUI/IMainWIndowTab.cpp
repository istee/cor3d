#include "IMainWindowTab.h"

void IMainWindowTab::viewTranslationChanged(const DCoordinate3& translation)
{
    glwidget->set_translation(translation);
    emit transformations_changed();
}

void IMainWindowTab::viewRotationChanged(const DCoordinate3& angles)
{
    glwidget->set_rotation(angles);
    emit transformations_changed();
}

void IMainWindowTab::viewZoomFactorChanged(double zoom)
{
    glwidget->set_zoom_factor(zoom);
    emit transformations_changed();
}
