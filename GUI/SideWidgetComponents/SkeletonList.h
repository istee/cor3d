#pragma once

#include <QWidget>
#include <QHash>
#include <string>
#include "ui_SkeletonList.h"
#include "BaseSideWidget.h"
#include "GUI/BasicWidgets/EditableDeletableListItem.h"
#include "GUI/WidgetExtensions/BaseEntityDisplayProperties.h"

using namespace std;

class SkeletonList: public BaseSideWidget, public Ui::SkeletonList
{
    Q_OBJECT
public:
    // special and default constructor
    SkeletonList(QWidget *parent = 0);
    void update_content();
    void updateSkeletonModel(const string& skeletonName);

private:
    QHash<string,BaseEntityDisplayProperties>  _skeletonDisplayProperties;

signals:
    void view_skeleton_deleted();
    void view_skeleton_selected(int id);
    void view_skeleton_added(const string& name);
    void view_skeleton_deleted(const string& name);
    void view_skeleton_renamed(const string& oldName, const string& newName);

    void view_skeleton_model_changed(const string& name, const string& fileName);
    void view_skeleton_model_offset_changed(const string& name, const DCoordinate3& offset);
    void view_skeleton_model_scale_changed(const string& name, const DCoordinate3& scale);

private slots:
    void on_toolButtonAdd_clicked();
    void on_skeleton_listview_clicked(QModelIndex index);
    void on_skeleton_listview_activated(QModelIndex index);

    void handle_view_skeleton_edited(const string& name);
};
