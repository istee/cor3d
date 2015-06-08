#include <sstream>
#include <fstream>
#include <string>

#include "Cor3d.h"
#include "BaseEntity.h"
#include "Skeleton.h"

namespace cor3d {
    Cor3d::Cor3d(): QObject()
    {
        _selected_skeleton_id = -1;
        _rendering_options = new RenderingOptions();

        emit modelRenderingOptionsChanged(_rendering_options);
    }

    string Cor3d::next_name() const
    {
        return cor3d::next_name<Skeleton>("Skeleton ", _skeletons);
    }

    int Cor3d::get_skeleton_id_by_name(const string& name) const
    {
        return get_id_by_name<Skeleton>(name, _skeletons);
    }

    Skeleton* Cor3d::get_skeleton()
    {
        if (is_skeleton_selected())
        {
            return _skeletons[_selected_skeleton_id];
        }
        return 0;
    }

    unsigned int Cor3d::get_selected_skeleton_id() const
    {
        return _selected_skeleton_id;
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
        int skeletonId = get_skeleton_id_by_name(skeletonName);
        if (skeletonId >= 0 && skeletonId < _skeletons.size())
        {
            return _skeletons[skeletonId];
        }
        return 0;
    }

    vector<BaseEntity*> Cor3d::get_skeleton_list()
    {
        return get_base_entities<Skeleton>(_skeletons);
    }

    RenderingOptions* Cor3d::get_rendering_options()
    {
        return _rendering_options;
    }

    bool Cor3d::is_skeleton_id_valid(int skeleton_id)
    {
        if (skeleton_id < 0)
        {
            return false;
        }
        if ((unsigned int)skeleton_id >= _skeletons.size())
        {
            return false;
        }
        return true;
    }

    bool Cor3d::is_skeleton_selected()
    {
        return is_skeleton_id_valid(_selected_skeleton_id);
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

    void Cor3d::handle_view_translation_changed(const DCoordinate3& translation)
    {
        _rendering_options->setTranslation(translation);
        emit model_translation_changed(_rendering_options->getTranslation());
    }

    void Cor3d::handle_view_rotation_changed(const DCoordinate3& rotation)
    {
        _rendering_options->setRotation(rotation);
        emit model_rotation_changed(_rendering_options->getRotation());
    }

    void Cor3d::handle_view_zoom_changed(double zoom)
    {
        _rendering_options->setZoom(zoom);
        emit model_zoom_changed(_rendering_options->getZoom());
    }

    void Cor3d::handleViewSkeletonAdded(string name)
    {
        Skeleton* selected = get_skeleton();

        Skeleton* skeleton = new Skeleton(_skeletons.size(), append_sequence_number<Skeleton>(name, _skeletons));
        skeleton->addRoot();
        _skeletons.push_back(skeleton);
        emit modelSkeletonAdded(skeleton);

        _selected_skeleton_id = skeleton->get_id();
        emit modelSkeletonSelected(skeleton, selected);
    }

    void Cor3d::handle_view_skeleton_selected(int id)
    {
        if (id != _selected_skeleton_id)
        {
            string oldSelected = "", newSelected = "";
            Skeleton* skeleton = get_skeleton();
            if (skeleton)
            {
                oldSelected = skeleton->get_name();
            }

            if (!is_skeleton_id_valid(id))
            {
                _selected_skeleton_id = -1;
            }
            else
            {
                _selected_skeleton_id = id;
                newSelected = get_skeleton()->get_name();
            }

            //emit model_skeleton_selection_changed(oldSelected, newSelected);
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

        Skeleton* oldSelection = getSkeletonById(_selected_skeleton_id);
        string oldSelectionName = "";
        if (oldSelection)
        {
            oldSelectionName = oldSelection->get_name();
        }

        if (newSelectionName != oldSelectionName)
        {
            _selected_skeleton_id = newSelection->get_id();
            emit modelSkeletonSelected(newSelection, oldSelection);
        }
    }

    void Cor3d::handleViewSkeletonDeleted(const string& name)
    {
        unsigned int deleteId = get_skeleton_id_by_name(name);
        Skeleton* deleteSkeleton = _skeletons[deleteId];
        _skeletons.erase(_skeletons.begin() + deleteId);
        for (vector<Skeleton*>::iterator it = _skeletons.begin() + deleteId; it != _skeletons.end(); it++)
        {
            ((BaseEntity*) *it)->decrease_id();
        }

        if (_selected_skeleton_id == deleteId)
        {
            _selected_skeleton_id--;
            emit modelSkeletonSelected(get_skeleton(), 0);
        }

        delete deleteSkeleton;
        emit modelSkeletonDeleted(name);
    }

    void Cor3d::handle_view_skeleton_exported(const string& file_name)
    {
        ofstream file;
        file.open(file_name.c_str());
        file << *get_skeleton();
        file.close();
    }

    void Cor3d::handleViewSkeletonRenamed(const string& oldName, const string& newName)
    {
        ((Skeleton*) _skeletons[get_skeleton_id_by_name(oldName)])->set_name(newName);
        emit modelSkeletonRenamed(oldName, newName);
    }
}
