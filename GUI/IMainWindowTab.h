#pragma once

#include <QWidget>

#include "Cor3dApplication.h"
#include "glwidget.h"

class IMainWindowTab: public QWidget
{
    Q_OBJECT

protected:
    Cor3dApplication*   cor3dApp;
    GLWidget*           glwidget;
    bool                _isSelected;

public:
    IMainWindowTab(QWidget* parent);
    void setGLWidgetTranslation(const DCoordinate3& translation);
    void setGLWidgetRotation(const DCoordinate3& angles);
    void setGLWidgetZoomFactor(double value);
    void setSelected(bool selected);
public slots:
    void updateGLWidget() const;
};
