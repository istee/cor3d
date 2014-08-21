#pragma once

#include <string>
#include <vector>

#include "Skeleton.h"

using namespace std;

namespace cor3d {
    class Cor3d {
        vector<Skeleton>    _skeletons;
        int                 _selected_skeleton;

        Cor3d() {}
        Cor3d(Cor3d const&);
        void operator=(Cor3d const&);
        bool check_skeleton_id_boundaries(int skeleton_id);
    public:
        static Cor3d& getInstance()
        {
            static Cor3d instance;
            return instance;
        }

        const vector<BaseEntity> get_skeleton_list();
        unsigned int create_skeleton(string name);

        int get_skeleton_id_by_name(string name) const;
        string get_skeleton_name_by_id(int id);

        string get_skeleton_model_file(unsigned int skeleton_id);
        double get_skeleton_model_x(unsigned int skeleton_id);
        double get_skeleton_model_y(unsigned int skeleton_id);
        double get_skeleton_model_z(unsigned int skeleton_id);

        int set_skeleton_name(int skeleton_id, string name);
        int set_skeleton_model_file(int skeleton_id, string file_name);
        int set_skeleton_model_x(int skeleton_id, double x);
        int set_skeleton_model_y(int skeleton_id, double y);
        int set_skeleton_model_z(int skeleton_id, double z);

        void select_skeleton(int id);
        int get_selected_skeleton();


    };
}
