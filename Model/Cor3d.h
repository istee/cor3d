#pragma once

#include <string>
#include <vector>
#include <map>
#include <QObject>

#include "Skeleton.h"
#include "BaseEntityCollection.h"

using namespace std;

namespace cor3d {
    class Cor3d: public QObject, public BaseEntityCollection {
        Q_OBJECT

        vector<Skeleton*>   _skeletons;
        int                 _selected_skeleton_id;

        RenderingOptions*   _rendering_options;





    protected:
        vector<Skeleton*> get_data()
        {
            return _skeletons;
        }

    public:
        Cor3d();

        int get_skeleton_id_by_name(const string& name) const;
        string next_name() const;
        vector<BaseEntity*> get_skeleton_list();
        Skeleton* get_skeleton();
        Skeleton* getSkeletonById(unsigned int skeletonId);
        RenderingOptions* get_rendering_options();
        void importSkeleton(ifstream& stream);

    private:
        bool is_skeleton_id_valid(int skeleton_id);
        bool is_skeleton_selected();

    signals:
        void model_skeleton_list_changed();
        void model_skeleton_selection_changed();
        void model_skeleton_name_changed();
        void model_skeleton_data_changed();
        void model_rendering_options_changed();

    public slots:
        void handle_view_skeleton_added(string);
        void handle_view_skeleton_imported(const string&);
        void handle_view_skeleton_selected(int);
        void handle_view_skeleton_deleted(const string&);
        void handle_view_skeleton_exported(const string&);
        void handle_view_skeleton_name_changed(const string&);
        void handle_view_skeleton_model_changed(const string&);
        void handle_view_skeleton_model_scale_changed(const DCoordinate3&);
        void handle_view_skeleton_model_offset_changed(const DCoordinate3&);

        void handle_view_skeleton_render_toggled(bool);
        void handle_view_skeleton_material_changed(int);
        void handle_view_joint_render_toggled(bool);
        void handle_view_joint_model_file_changed(const string&);
        void handle_view_joint_material_changed(int);
        void handle_view_selected_joint_material_changed(int);
        void handle_view_link_render_toggled(bool);
        void handle_view_link_model_file_changed(const string&);
        void handle_view_link_material_changed(int);

    };
}
