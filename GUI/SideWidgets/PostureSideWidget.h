#pragma once

#include <QListWidget>

#include "ui_PostureSideWidget.h"

#include "GUI/SideWidgets/BaseSideWidget.h"

using namespace std;

class PostureSideWidget : public BaseSideWidget, public Ui::PostureSideWidget
{
    Q_OBJECT

public:
    explicit PostureSideWidget(QWidget *parent = 0);
    void populatePostureList(Skeleton* skeleton);
    void addPosture(Skeleton* skeleton, Posture* posture);
    void deletePosture(Skeleton* skeleton, const string& postureName);
    void renamePosture(const string& oldPostureName, const string& newPostureName);
    void selectPosture(Skeleton* skeleton, Posture* posture);

signals:
    void viewPostureAdded(const string& postureName);
    void viewPostureRenamed(const string& oldPostureName, const string& newPostureName);
    void viewPostureDeleted(const string& postureName);
    void viewPostureSelected(const string& postureName);

private slots:
    void on_postureList_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void handleViewPostureAdded(const string& name);
};

