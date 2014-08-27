#include "Cor3d.h"
#include "BaseEntity.h"
#include "ISkeleton.h"
#include "Skeleton.h"

namespace cor3d {
    Cor3d::Cor3d()
    {
        _selected_skeleton = -1;
        //_joint_model.LoadFromOFF("Models/sphere.off");
        //_joint_model.UpdateVertexBufferObjects();
        //_link_model.LoadFromOFF("Models/cone.off");
        //_link_model.UpdateVertexBufferObjects();
    }

    vector<BaseEntity> Cor3d::get_skeleton_list() const
    {
        vector<BaseEntity> skeleton_list = vector<BaseEntity>();
        for (std::vector<Skeleton>::const_iterator it = _skeletons.begin(); it != _skeletons.end(); it++)
        {
            skeleton_list.push_back((BaseEntity) *it);
        }

        return skeleton_list;
    }

    unsigned int Cor3d::create_skeleton(const string& name)
    {
        Skeleton skeleton = Skeleton(_skeletons.size(), name);
        _skeletons.push_back(skeleton);
        return skeleton.get_id();
    }

    Skeleton Cor3d::get_skeleton_by_name(const string& name) const
    {
        for (std::vector<Skeleton>::const_iterator it = _skeletons.begin(); it != _skeletons.end(); it++)
        {
            if (it->get_name() == name)
            {
                return (Skeleton) *it;
            }
        }
    }

    int Cor3d::get_skeleton_id_by_name(const string& name) const
    {
        for (std::vector<Skeleton>::const_iterator it = _skeletons.begin(); it != _skeletons.end(); it++)
        {
            if (it->get_name() == name)
            {
                return ((BaseEntity) *it).get_id();
            }
        }

        return -1;
    }

    Skeleton Cor3d::get_skeleton_by_id(int id) const
    {
        for (std::vector<Skeleton>::const_iterator it = _skeletons.begin(); it != _skeletons.end(); it++)
        {
            if (it->get_id() == id)
            {
                return (Skeleton) *it;
            }
        }
    }

    Skeleton Cor3d::get_selected_skeleton() const
    {
        if (_selected_skeleton >= 0)
        {
            return _skeletons[_selected_skeleton];
        }
        throw _selected_skeleton;
    }

    bool Cor3d::is_skeleton_name_reserved(const string& name) const
    {
        for (std::vector<Skeleton>::const_iterator it = _skeletons.begin(); it != _skeletons.end(); it++)
        {
            if (it->get_name() == name)
            {
                return true;
            }
        }
        return false;
    }

    void Cor3d::set_skeleton(const Skeleton& skeleton)
    {
        _skeletons[skeleton.get_id()] = skeleton;
    }

    void Cor3d::remove_selected_skeleton()
    {
        // TODO remove
//        cout << _selected_skeleton << endl;
//        _skeletons.erase(&_skeletons[_selected_skeleton]);
//        for (vector<Skeleton>::iterator it = _skeletons.begin() + _selected_skeleton; it != _skeletons.end(); it++)
//        {
//            ((BaseEntity) *it).decrease_id();
//        }
        _selected_skeleton = -1;
    }

    void Cor3d::select_skeleton(int id)
    {
        if (id > _skeletons.size() + 1)
        {
            _selected_skeleton = -1;
        }
        else
        {
            _selected_skeleton = id;
            _skeletons[_selected_skeleton].select_joint(-1);
        }
    }

    bool Cor3d::check_skeleton_id_boundaries(int skeleton_id)
    {
        if (skeleton_id < 0)
        {
            return false;
        }
        if (skeleton_id >= _skeletons.size())
        {
            return false;
        }
        return true;
    }
}
