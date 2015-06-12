#pragma once

#include <QWidget>
#include <QHash>
#include <string>
#include "ui_SkeletonSideWidget.h"
#include "BaseSideWidget.h"
#include "GUI/BasicWidgets/BaseEntityListItem.h"

using namespace std;

class SkeletonSideWidget: public BaseSideWidget, public Ui::SkeletonSideWidget
{
    Q_OBJECT
public:
    // special and default constructor
    SkeletonSideWidget(QWidget *parent = 0);
    void addSkeleton(Skeleton* skeleton);
    void deleteSkeleton(const string& name);
    void renameSkeleton(const string& oldName, const string& newName);
    void updateSkeletonModel(Skeleton* skeleton);
    void selectSkeleton(const string& name);

signals:
    void viewSkeletonSelected(const string& name);
    void viewSkeletonAdded(const string& name);
    void viewSkeletonDeleted(const string& name);
    void viewSkeletonRenamed(const string& oldName, const string& newName);
private slots:
    void on_skeleton_listview_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void handleViewSkeletonAdded(const string& name);

    void handleViewSkeletonEdited(const string& name);
    void handleModelSkeletonDataChanged(Skeleton* skeleton);
};
