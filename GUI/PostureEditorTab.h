#pragma once

#include "IMainWindowTab.h"

#include "ui_PostureEditorTab.h"

class PostureEditorTab: public IMainWindowTab, public Ui::PostureEditorTab
{
    Q_OBJECT
public:
    PostureEditorTab(QWidget* parent = 0);

private slots:
    void handleModelSkeletonAdded(Skeleton* skeleton);
    void handleModelSkeletonDeleted(const string& name);
    void handle_model_skeleton_selection_changed(const string& oldSelectionName, const string& newSelectionName);
    void handleModelSkeletonRenamed(const string& oldName, const string& newName);

    void handleModelPostureAdded(Skeleton* skeleton, Posture* posture);
    void handleModelPostureDeleted(const string& skeletonName, const string& postureName);
    void handleModelPostureRenamed(const string& skeletonName, const string& oldPostureName, const string& newPostureName);
};
