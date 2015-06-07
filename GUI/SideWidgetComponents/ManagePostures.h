#pragma once

#include <QTreeWidget>

#include "GUI/SideWidgetComponents/BaseSideWidget.h"

using namespace std;

namespace Ui {
    class ManagePostures;
}

class ManagePostures : public BaseSideWidget
{
    Q_OBJECT

public:
    explicit ManagePostures(QWidget *parent = 0);
    void addSkeleton(const string& skeletonName);
    void deleteSkeleton(const string& name);
    void renameSkeleton(const string& oldName, const string& newName);
    void selectSkeleton(const string& skeletonName);
    void addPosture(Skeleton* skeleton, Posture* posture);
    void deletePosture(const string& skeletonName, const string& postureName);
    void renamePosture(const string& skeletonName, const string& oldPostureName, const string& newPostureName);
    ~ManagePostures();

signals:
    void viewSkeletonSelected(const string& skeletonName);
    void viewPostureAdded(const string& postureName);
    void viewPostureRenamed(const string& skeletonName, const string& oldPostureName, const string& newPostureName);
    void viewPostureDeleted(const string& skeletonName, const string& postureName);
    void viewPostureSelected(const string& postureName);
    void viewPostureDeselected();


private:
    Ui::ManagePostures *ui;

private slots:
    void on_toolButtonAdd_clicked();
    void on_postureTreeWidget_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
};

