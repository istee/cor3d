#pragma once

#include "IMainWindowTab.h"

#include "ui_SkeletonEditorTab.h"

#include "SkeletonGLWidget.h"

using namespace std;

class SkeletonEditorTab: public IMainWindowTab, public Ui::SkeletonEditorTab
{
    Q_OBJECT
public:
    SkeletonEditorTab(QWidget* parent = 0);

public slots:
    void handleModelSkeletonAdded(Skeleton* skeleton);
    void handleModelSkeletonDeleted(const string& name);
    void handleModelSkeletonRenamed(const string& oldName, const string& newName);
    void handleModelSkeletonSelected(Skeleton* selected, Skeleton* previous);

    void handleModelJointAdded(Skeleton* skeleton, Joint* joint, const string& name);
    void handleModelJointDeleted(const string& name);
    void handleModelJointRenamed(const string& oldName, const string& newName);
    void handleModelJointSelected(const string& name);
    void handleModelJointDataChanged(Joint* joint);
    void handle_model_rendering_options_changed();
    void handleModelSkeletonDataChanged(Skeleton* skeleton);
};
