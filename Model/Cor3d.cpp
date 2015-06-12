#include <sstream>
#include <fstream>
#include <string>

#include "Cor3d.h"
#include "BaseEntity.h"
#include "Skeleton.h"
#include "BaseEntityCollection.h"

namespace cor3d {
    Cor3d::Cor3d(): QObject()
    {
        _selectedSkeletonId = -1;
        _renderingOptions = new RenderingOptions();

        emit modelRenderingOptionsChanged(_renderingOptions);

        //_baseEntitys = BaseEntityCollection<Skeleton>();
        //BaseEntityCollection<Skeleton> b = BaseEntityCollection<Skeleton>();
    }

    string Cor3d::nextName() const
    {
        return cor3d::nextName<Skeleton>("Skeleton ", _skeletons);
    }

    Skeleton* Cor3d::getSelectedSkeleton()
    {
        if (_selectedSkeletonId >= 0 && _selectedSkeletonId < _skeletons.size())
        {
            return _skeletons[_selectedSkeletonId];
        }
        return 0;
    }

    Skeleton* Cor3d::getSkeletonById(unsigned int skeletonId)
    {
        if (skeletonId >= 0 && skeletonId < _skeletons.size())
        {
            return _skeletons[skeletonId];
        }
        return 0;
    }

    Skeleton* Cor3d::getSkeletonByName(const string& skeletonName)
    {
        int skeletonId = getIdByName<Skeleton>(skeletonName, _skeletons);
        if (skeletonId >= 0 && skeletonId < _skeletons.size())
        {
            return _skeletons[skeletonId];
        }
        return 0;
    }

    vector<BaseEntity*> Cor3d::getSkeletonSideWidget()
    {
        return getBaseEntities<Skeleton>(_skeletons);
    }

    RenderingOptions* Cor3d::getRenderingOptions() const
    {
        return _renderingOptions;
    }

    void Cor3d::importSkeleton(ifstream& stream)
    {
        Skeleton* sk = new Skeleton(_skeletons.size(), "asd");
        stream >> *sk;
        _skeletons.push_back(sk);
        emit modelSkeletonAdded(sk);

        emit handleViewSkeletonSelected(sk->getName());
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

        Skeleton* skeleton = new Skeleton(_skeletons.size(), appendSequenceNumber<Skeleton>(name, _skeletons));
        skeleton->addRoot();
        _skeletons.push_back(skeleton);
        emit modelSkeletonAdded(skeleton);

        _selectedSkeletonId = skeleton->getId();
        emit modelSkeletonSelected(skeleton, selected);
    }

    void Cor3d::handleViewSkeletonSelected(const string& name)
    {
        Skeleton* newSelection = getSkeletonByName(name);
        string newSelectionName = "";
        if (newSelection)
        {
            newSelectionName = newSelection->getName();
        }

        Skeleton* oldSelection = getSkeletonById(_selectedSkeletonId);
        string oldSelectionName = "";
        if (oldSelection)
        {
            oldSelectionName = oldSelection->getName();
        }

        if (newSelectionName != oldSelectionName)
        {
            _selectedSkeletonId = newSelection->getId();
            emit modelSkeletonSelected(newSelection, oldSelection);
        }
    }

    void Cor3d::handleViewSkeletonDeleted(const string& name)
    {
        Skeleton* deleteSkeleton = getSkeletonByName(name);
        if (deleteSkeleton)
        {
            unsigned int deleteId = deleteSkeleton->getId();
            _skeletons.erase(_skeletons.begin() + deleteId);
            for (vector<Skeleton*>::iterator it = _skeletons.begin() + deleteId; it != _skeletons.end(); it++)
            {
                ((BaseEntity*) *it)->decrease_id();
            }

            if (_selectedSkeletonId == deleteId)
            {
                _selectedSkeletonId--;
                emit modelSkeletonSelected(getSelectedSkeleton(), 0);
            }

            delete deleteSkeleton;
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
