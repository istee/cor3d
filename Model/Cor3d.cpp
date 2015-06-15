#include <sstream>
#include <fstream>
#include <string>

#include "Cor3d.h"
#include "BaseEntity.h"
#include "Skeleton.h"
#include "BaseEntityCollection.h"

namespace cor3d {
    Cor3d::Cor3d(): QObject(), _skeletons(BaseEntityCollection("Skeleton"))
    {
        _renderingOptions = new RenderingOptions();
        //_skeletons1312232 = BaseEntityCollection("Skeleton");

        emit modelRenderingOptionsChanged(_renderingOptions);

        //_skeletons = BaseEntityCollection("Skeleton");

        //_baseEntitys = BaseEntityCollection<Skeleton>();
        //BaseEntityCollection<Skeleton> b = BaseEntityCollection<Skeleton>();
    }

    string Cor3d::nextName() const
    {
        return _skeletons.nextAutoName();
    }

    Skeleton* Cor3d::getSelectedSkeleton()
    {
        Skeleton* selectedSkeleton = static_cast<Skeleton*>(_skeletons.getSelectedEntity());
        if (selectedSkeleton)
        {
            return selectedSkeleton;
        }
        return 0;
    }

    Skeleton* Cor3d::getSkeletonByName(const string& skeletonName)
    {
        return static_cast<Skeleton*>(_skeletons[skeletonName]);
    }

    const vector<BaseEntity*> Cor3d::getSkeletonList()
    {
        return _skeletons.getData();
    }

    RenderingOptions* Cor3d::getRenderingOptions() const
    {
        return _renderingOptions;
    }

    void Cor3d::importSkeleton(ifstream& stream)
    {
        Skeleton* skeleton = new Skeleton(_skeletons.entityCount(), "");
        stream >> *skeleton;
        _skeletons.addEntity(skeleton);
        cout << *skeleton << endl;
        emit modelSkeletonAdded(skeleton);
    }

    // implementation of public slots

    void Cor3d::handleViewTranslationChanged(const DCoordinate3& translation)
    {
        _renderingOptions->setTranslation(translation);
        emit modelTranslationChanged(_renderingOptions->getTranslation());
    }

    void Cor3d::handleViewRotationChanged(const DCoordinate3& rotation)
    {
        _renderingOptions->setRotation(rotation);
        emit modelRotationChanged(_renderingOptions->getRotation());
    }

    void Cor3d::handleViewZoomChanged(double zoom)
    {
        _renderingOptions->setZoom(zoom);
        emit modelZoomChanged(_renderingOptions->getZoom());
    }

    void Cor3d::handleViewSkeletonAdded(string name)
    {
        Skeleton* selected = getSelectedSkeleton();

        Skeleton* skeleton = new Skeleton(_skeletons.entityCount(), name);
        skeleton->addRoot();
        if (_skeletons.addEntity(skeleton))
        {
            emit modelSkeletonAdded(skeleton);

            //emit modelSkeletonSelected(skeleton, selected);
        }
        else
        {
            delete skeleton;
        }
    }

    void Cor3d::handleViewSkeletonSelected(const string& name)
    {
        Skeleton* oldSelection = (Skeleton*) _skeletons.getSelectedEntity();
        if (_skeletons.selectEntity(name))
        {
            emit modelSkeletonSelected((Skeleton*) _skeletons.getSelectedEntity(), oldSelection);
        }
    }

    void Cor3d::handleViewSkeletonDeleted(const string& name)
    {
        bool selectionChanged;
        if (_skeletons.deleteEntity(name, selectionChanged))
        {
            if (selectionChanged)
            {
                emit modelSkeletonSelected((Skeleton*) _skeletons.getSelectedEntity(), 0);
            }
            emit modelSkeletonDeleted(name);
        }
    }

    void Cor3d::handle_view_skeleton_exported(const string& file_name)
    {
        ofstream file;
        file.open(file_name.c_str());
        file << *getSelectedSkeleton();
        file.close();
    }

    void Cor3d::handleViewSkeletonRenamed(const string& oldName, const string& newName)
    {
        Skeleton* skeleton = getSkeletonByName(oldName);
        if (skeleton)
        {
            skeleton->setName(newName);
            emit modelSkeletonRenamed(oldName, newName);
        }
    }
}
