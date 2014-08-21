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
        Skeleton skeleton = Skeleton(_skeletons.size() + 1, name);
        _skeletons.push_back(skeleton);
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

    void Cor3d::select_skeleton(int id)
    {
        if (id > _skeletons.size())
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
}
