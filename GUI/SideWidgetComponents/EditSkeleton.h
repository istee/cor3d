#pragma once

#include <QWidget>

#include "ui_EditSkeleton.h"
#include "BaseSideWidget.h"
#include "Model/Skeleton.h"

using namespace cor3d;

class EditSkeleton: public BaseSideWidget, public Ui::EditSkeleton
{
    Q_OBJECT

    void enable_edits();
    void disable_edits();
public:
    // special and default constructor
    EditSkeleton(QWidget *parent = 0);
    void update_content();
    void data_changed();

signals:
    void view_skeleton_name_changed(const string& name);
    void view_skeleton_model_changed(const string& file);
    void view_skeleton_model_scale_changed(const DCoordinate3& scale);
    void view_skeleton_model_offset_changed(const DCoordinate3& offset);
};
