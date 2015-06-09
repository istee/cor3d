#pragma once

#include <QWidget>
#include <QHash>
#include <string>
#include "ui_SkeletonList.h"
#include "BaseSideWidget.h"
#include "GUI/BasicWidgets/BaseEntityListItem.h"
#include "GUI/WidgetExtensions/BaseEntityDisplayProperties.h"

using namespace std;

class SkeletonList: public BaseSideWidget, public Ui::SkeletonList
{
    Q_OBJECT
public:
    // special and default constructor
    SkeletonList(QWidget *parent = 0);
    void update_content();
    void addSkeleton(Skeleton* skeleton);
    void deleteSkeleton(const string& name);
    void renameSkeleton(const string& oldName, const string& newName);
    void updateSkeletonModel(Skeleton* skeleton);
    void selectSkeleton(const string& name);

private:
    QHash<string,BaseEntityDisplayProperties>  _skeletonDisplayProperties;

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
