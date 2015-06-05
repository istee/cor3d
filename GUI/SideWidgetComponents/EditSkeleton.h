#pragma once

#include <QWidget>

#include "ui_EditSkeleton.h"
#include "GUI/EditWidgets/BaseEditWidget.h"
#include "Model/Skeleton.h"
#include "Model/BaseEntity.h"

using namespace cor3d;
using namespace std;

class EditSkeleton: public BaseEditWidget, public Ui::EditSkeleton
{
    Q_OBJECT

    void enable_edits();
    void disable_edits();
    string _skeletonName;
public:
    // special and default constructor
    EditSkeleton(QWidget *parent = 0);
    void update_content();
    void updateContent(BaseEntity* baseEntity);
    void data_changed();

signals:
    void view_skeleton_model_changed(const string& skeletonName, const string& file);
    void view_skeleton_model_scale_changed(const string& skeletonName, const DCoordinate3& scale);
    void view_skeleton_model_offset_changed(const string& skeletonName, const DCoordinate3& offset);

private slots:
    void handle_skeleton_model_changed(const string& file);
    void handle_skeleton_model_scale_changed(const DCoordinate3& scale);
    void handle_skeleton_model_offset_changed(const DCoordinate3& offset);
};
