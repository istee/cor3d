#pragma once

#include <string>
#include <vector>
#include <map>
#include <QObject>

#include "Skeleton.h"
#include "BaseEntityCollection.h"

using namespace std;

namespace cor3d {
    class Cor3d: public QObject{
        Q_OBJECT

        vector<Skeleton*>               _skeletons;
        int                             _selectedSkeletonId;
        RenderingOptions*               _renderingOptions;
        //BaseEntityCollection<Skeleton>  _baseEntitys;

    public:
        Cor3d();
        string nextName() const;
        vector<BaseEntity*> getSkeletonSideWidget();
        Skeleton* getSelectedSkeleton();
        Skeleton* getSkeletonById(unsigned int skeletonId);
        Skeleton* getSkeletonByName(const string& skeletonName);
        void importSkeleton(ifstream& stream);
        RenderingOptions* getRenderingOptions() const;

    signals:
        void modelTranslationChanged(const DCoordinate3&);
        void modelRotationChanged(const DCoordinate3&);
        void modelZoomChanged(double zoom);

        void modelSkeletonAdded(Skeleton* skeleton);
        void modelSkeletonDeleted(const string& name);
        void modelSkeletonRenamed(const string& oldName, const string& newName);
        void modelSkeletonSelected(Skeleton* selected, Skeleton* previous);
        void modelPostureSelected(Skeleton* selectedSkeleton, Posture* selectedPosture, Skeleton* previousSkeleton, Posture* previousPosture);

        void modelRenderingOptionsChanged(RenderingOptions* renderingOptions);
    public slots:
        void handleViewTranslationChanged(const DCoordinate3&);
        void handleViewRotationChanged(const DCoordinate3&);
        void handleViewZoomChanged(double zoom);

        void handleViewSkeletonAdded(string);
        void handleViewSkeletonSelected(const string&);
        void handleViewSkeletonDeleted(const string&);
        void handle_view_skeleton_exported(const string&);
        void handleViewSkeletonRenamed(const string&, const string&);
    };
}
