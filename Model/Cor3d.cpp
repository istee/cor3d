#include "Cor3d.h"
#include "BaseEntity.h"
#include "ISkeleton.h"
#include "Skeleton.h"

namespace cor3d {
<<<<<<< HEAD
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
=======
    const vector<BaseEntity> Cor3d::get_skeleton_list()
    {
        vector<BaseEntity> skeletonList = vector<BaseEntity>();
        for (std::vector<Skeleton>::iterator it = _skeletons.begin(); it != _skeletons.end(); it++)
        {
            skeletonList.push_back((BaseEntity) *it);
        }

        return skeletonList;
    }

    unsigned int Cor3d::create_skeleton(string name)
    {
        Skeleton skeleton = Skeleton(_skeletons.size() + 1, name);
        _skeletons.push_back(skeleton);
    }

    int Cor3d::get_skeleton_id_by_name(string name) const
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
    {
        for (std::vector<Skeleton>::const_iterator it = _skeletons.begin(); it != _skeletons.end(); it++)
        {
            if (it->get_name() == name)
            {
<<<<<<< HEAD
                return ((BaseEntity) *it).get_id();
            }
        }

        return -1;
    }

    Skeleton Cor3d::get_skeleton_by_id(int id) const
=======
                return it->get_id();
            }
        }
        return -1;
    }

    string Cor3d::get_skeleton_name_by_id(int id)
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
    {
        for (std::vector<Skeleton>::const_iterator it = _skeletons.begin(); it != _skeletons.end(); it++)
        {
            if (it->get_id() == id)
            {
<<<<<<< HEAD
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
=======
                return it->get_name();
            }
        }
        return "";
    }

    string Cor3d::get_skeleton_model_file(unsigned int skeleton_id)
    {
        return _skeletons[skeleton_id].get_model_file();
    }

    double Cor3d::get_skeleton_model_x(unsigned int skeleton_id)
    {
        return _skeletons[skeleton_id].get_model_x();
    }

    double Cor3d::get_skeleton_model_y(unsigned int skeleton_id)
    {
        return _skeletons[skeleton_id].get_model_y();
    }

    double Cor3d::get_skeleton_model_z(unsigned int skeleton_id)
    {
        return _skeletons[skeleton_id].get_model_z();
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
    }

    void Cor3d::select_skeleton(int id)
    {
<<<<<<< HEAD
        if (id > _skeletons.size() + 1)
=======
        if (id > _skeletons.size())
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
        {
            _selected_skeleton = -1;
        }
        else
        {
            _selected_skeleton = id;
            _skeletons[_selected_skeleton].select_joint(-1);
        }
    }

<<<<<<< HEAD
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
=======
    int Cor3d::get_selected_skeleton()
    {
        return _selected_skeleton;
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
    }
}
