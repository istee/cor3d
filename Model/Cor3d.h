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
        Skeleton* getSkeletonByName(const string& skeletonName);
        RenderingOptions* get_rendering_options();
        void importSkeleton(ifstream& stream);
        unsigned int get_selected_skeleton_id() const;
        RenderingOptions* getRenderingOpstions() const
        {
            return _rendering_options;
        }

    private:
        bool is_skeleton_id_valid(int skeleton_id);
        bool is_skeleton_selected();

    signals:
        void model_translation_changed(const DCoordinate3&);
        void model_rotation_changed(const DCoordinate3&);
        void model_zoom_changed(double zoom);

        void modelSkeletonAdded(Skeleton* skeleton);
        void modelSkeletonDeleted(const string& name);
        void modelSkeletonRenamed(const string& oldName, const string& newName);
        void modelSkeletonSelected(Skeleton* selected, Skeleton* previous);

        void modelRenderingOptionsChanged(RenderingOptions* renderingOptions);
    public slots:
        void handle_view_translation_changed(const DCoordinate3&);
        void handle_view_rotation_changed(const DCoordinate3&);
        void handle_view_zoom_changed(double zoom);

        void handleViewSkeletonAdded(string);
        void handle_view_skeleton_selected(int);
        void handleViewSkeletonSelected(const string&);
        void handleViewSkeletonDeleted(const string&);
        void handle_view_skeleton_exported(const string&);
        void handleViewSkeletonRenamed(const string&, const string&);
    };
}
