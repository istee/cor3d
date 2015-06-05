#pragma once

#include <QWidget>

#include "Cor3dApplication.h"
#include "GLWidget.h"

class IMainWindowTab: public QWidget
{
    Q_OBJECT

protected:
    Cor3dApplication*   cor3dApp;
    GLWidget*           glwidget;

public:
    IMainWindowTab(QWidget* parent);
    void updateGlWidget() const;
    void setGLWidgetTranslation(const DCoordinate3& translation);
    void setGLWidgetRotation(const DCoordinate3& angles);
    void setGLWidgetZoomFactor(double value);
};
