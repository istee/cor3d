#include "Cor3d.h"
#include "BaseEntity.h"
#include "ISkeleton.h"
#include "Skeleton.h"

namespace cor3d {
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
        Skeleton skeleton = Skeleton(_skeletons.size(), name);
        _skeletons.push_back(skeleton);
        return skeleton.get_id();
    }

    int Cor3d::get_skeleton_id_by_name(string name) const
    {
        for (std::vector<Skeleton>::const_iterator it = _skeletons.begin(); it != _skeletons.end(); it++)
        {
            if (it->get_name() == name)
            {
                return it->get_id();
            }
        }
        return -1;
    }

    string Cor3d::get_skeleton_name_by_id(int id)
    {
        for (std::vector<Skeleton>::const_iterator it = _skeletons.begin(); it != _skeletons.end(); it++)
        {
            if (it->get_id() == id)
            {
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
    }

    int Cor3d::set_skeleton_name(int skeleton_id, string name)
    {
        bool ok = check_skeleton_id_boundaries(skeleton_id);
        for (vector<Skeleton>::iterator it = _skeletons.begin(); it != _skeletons.end() && ok; it++)
        {
            if (it->get_name() == name && it->get_id() != skeleton_id)
            {
                ok = false;
            }
        }
        if (ok)
        {
            _skeletons[skeleton_id].set_name(name);
            return 0;
        }

        return -1;
    }

    int Cor3d::set_skeleton_model_file(int skeleton_id, string file_name)
    {
        if(check_skeleton_id_boundaries(skeleton_id))
        {
            return _skeletons[skeleton_id].set_model_file(file_name);
        }

        return -1;
    }

    int Cor3d::set_skeleton_model_x(int skeleton_id, double x)
    {
        if(check_skeleton_id_boundaries(skeleton_id))
        {
            _skeletons[skeleton_id].set_model_x(x);
            return 0;
        }

        return -1;
    }

    int Cor3d::set_skeleton_model_y(int skeleton_id, double y)
    {
        if(check_skeleton_id_boundaries(skeleton_id))
        {
            _skeletons[skeleton_id].set_model_y(y);
            return 0;
        }

        return -1;
    }

    int Cor3d::set_skeleton_model_z(int skeleton_id, double z)
    {
        if(check_skeleton_id_boundaries(skeleton_id))
        {
            _skeletons[skeleton_id].set_model_z(z);
            return 0;
        }

        return -1;
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

    int Cor3d::get_selected_skeleton()
    {
        return _selected_skeleton;
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
