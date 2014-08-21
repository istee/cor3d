#pragma once

#include "GLWidget.h"
#include "SceneGLWidget.h"

class SceneView
{
    SceneGLWidget   _scene_widget;
public:
    SceneView(QWidget* parent = 0);
};
