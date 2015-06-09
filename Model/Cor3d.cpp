#include <sstream>
#include <fstream>
#include <string>

#include "Cor3d.h"
#include "BaseEntity.h"
#include "Skeleton.h"

namespace cor3d {
    Cor3d::Cor3d(): QObject()
    {
        _selectedSkeletonId = -1;
        _renderingOptions = new RenderingOptions();

        emit modelRenderingOptionsChanged(_renderingOptions);
    }

    string Cor3d::next_name() const
    {
        return cor3d::next_name<Skeleton>("Skeleton ", _skeletons);
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
        int skeletonId = get_id_by_name<Skeleton>(skeletonName, _skeletons);
        if (skeletonId >= 0 && skeletonId < _skeletons.size())
        {
            return _skeletons[skeletonId];
        }
        return 0;
    }

    vector<BaseEntity*> Cor3d::getSkeletonList()
    {
        return get_base_entities<Skeleton>(_skeletons);
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

        emit handleViewSkeletonSelected(sk->get_name());
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

        Skeleton* skeleton = new Skeleton(_skeletons.size(), append_sequence_number<Skeleton>(name, _skeletons));
        skeleton->addRoot();
        _skeletons.push_back(skeleton);
        emit modelSkeletonAdded(skeleton);

        _selectedSkeletonId = skeleton->get_id();
        emit modelSkeletonSelected(skeleton, selected);
    }

    void Cor3d::handle_view_skeleton_selected(int id)
    {
        if (id != _selectedSkeletonId)
        {
            string oldSelected = "", newSelected = "";
            Skeleton* skeleton = getSelectedSkeleton();
            if (skeleton)
            {
                oldSelected = skeleton->get_name();
            }

            if (!(id >= 0 && id < _skeletons.size()))
            {
                _selectedSkeletonId = -1;
            }
            else
            {
                _selectedSkeletonId = id;
                newSelected = getSelectedSkeleton()->get_name();
            }

            //emit model_skeleton_selectionChanged(oldSelected, newSelected);
        }
    }

    void Cor3d::handleViewSkeletonSelected(const string& name)
    {
        Skeleton* newSelection = getSkeletonByName(name);
        string newSelectionName = "";
        if (newSelection)
        {
            newSelectionName = newSelection->get_name();
        }

        Skeleton* oldSelection = getSkeletonById(_selectedSkeletonId);
        string oldSelectionName = "";
        if (oldSelection)
        {
            oldSelectionName = oldSelection->get_name();
        }

        if (newSelectionName != oldSelectionName)
        {
            _selectedSkeletonId = newSelection->get_id();
            emit modelSkeletonSelected(newSelection, oldSelection);
        }
    }

    void Cor3d::handleViewSkeletonDeleted(const string& name)
    {
        Skeleton* deleteSkeleton = getSkeletonByName(name);
        if (deleteSkeleton)
        {
            unsigned int deleteId = deleteSkeleton->get_id();
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
            skeleton->set_name(newName);
            emit modelSkeletonRenamed(oldName, newName);
        }
    }
}
