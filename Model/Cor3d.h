#pragma once

#include <string>
#include <vector>
<<<<<<< HEAD
#include <QObject>
=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa

#include "Skeleton.h"

using namespace std;

namespace cor3d {
    class Cor3d {
        vector<Skeleton>    _skeletons;
        int                 _selected_skeleton;
<<<<<<< HEAD
        TriangulatedMesh3   _joint_model;
        TriangulatedMesh3   _link_model;

        bool check_skeleton_id_boundaries(int skeleton_id);
    public:
        Cor3d();
        vector<BaseEntity> get_skeleton_list() const;
        unsigned int create_skeleton(const string& name);

        Skeleton get_skeleton_by_name(const string& name) const;
        int get_skeleton_id_by_name(const string& name) const;
        Skeleton get_skeleton_by_id(int id) const;
        Skeleton get_selected_skeleton() const;

        unsigned int get_skeleton_count() const
        {
            return _skeletons.size();
        }

        bool is_skeleton_selected() const
        {
            return _selected_skeleton >= 0;
        }

        bool is_skeleton_name_reserved(const string& name) const;

        void set_skeleton(const Skeleton& skeleton);

        void remove_selected_skeleton();

        void select_skeleton(int id);
=======

        Cor3d() {}
        Cor3d(Cor3d const&);
        void operator=(Cor3d const&);
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
        void select_skeleton(int id);
        int get_selected_skeleton();


>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
    };
}
