#pragma once

#include "IMainWindowTab.h"

#include "ui_PostureEditorTab.h"

class PostureEditorTab: public IMainWindowTab, public Ui::PostureEditorTab
{
    Q_OBJECT
public:
    PostureEditorTab(QWidget* parent = 0);

private slots:
    void handleModelSkeletonSelected(Skeleton* selected, Skeleton* previous);

    void handleModelPostureAdded(Skeleton* skeleton, Posture* posture);
    void handleModelPostureDeleted(Skeleton* skeleton, const string& postureName);
    void handleModelPostureRenamed(const string& oldPostureName, const string& newPostureName);
    void handleModelPostureSelected(Skeleton* selectedSkeleton, Posture* selectedPosture, Posture* previousPosture);
    void handleModelPostureDataChanged(Posture* posture, const string& rootJoint);
    void handleModelJointSelected(const string& jointName);
};
