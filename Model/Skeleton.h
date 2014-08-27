#pragma once

#include <vector>
#include <string>

#include "Model/ISkeleton.h"
#include "Joint.h"
#include "Posture.h"

#include "../Core/DCoordinates3.h"
#include "../Core/TriangulatedMeshes3.h"

#include "GUI/RenderingOptions.h"

using namespace std;
using namespace cagd;

namespace cor3d
{
    class Skeleton : public BaseEntity
    {
        string              _model_file;
        TriangulatedMesh3   _model;
        DCoordinate3        _model_offset;
        DCoordinate3        _model_scale;
        vector<Joint>       _joints;
        vector<Posture>     _postures;
        int                 _selected_joint;

    public:
        Skeleton(unsigned int id, string name): BaseEntity(id, name)
        {
            _model_scale = DCoordinate3(1.0, 1.0, 1.0);
            _selected_joint = -1;
        }

        ///////////////////////////
        // getter methods        //
        ///////////////////////////
        string get_model_file() const;
        DCoordinate3 get_model_offset() const;
        DCoordinate3 get_model_scale() const;
        unsigned int get_joint_count() const;
        vector<BaseEntity> get_joint_list() const;
        vector<BaseEntity> get_possible_parents(unsigned int id) const;

        int get_joint_parent(int joint_id) const;
        vector<unsigned int> get_joint_children(int joint_id) const;
        Type get_joint_type(int joint_id) const;
        DCoordinate3 get_joint_axis(int joint_id) const;
        double get_joint_length(int joint_id) const;
        double get_joint_initial_value(int joint_id) const;
        double get_joint_upper_limit(int joint_id) const;
        double get_joint_lower_limit(int joint_id) const;

        ///////////////////////////
        // setter methods        //
        ///////////////////////////
        int set_model_file(const string& file_name);
        void set_model_offset(const DCoordinate3& model_offset);
        void set_model_scale(const DCoordinate3& model_scale);

        void set_joint_parent(int joint_id, int parent_id);
        void set_joint_type(int joint_id, Type type);
        void set_joint_axis(int joint_id, const DCoordinate3& axis);
        void set_joint_length(int joint_id, double length);
        void set_joint_initial_value(int joint_id, double initial_value);
        void set_joint_upper_limit(int joint_id, double upper_limit);
        void set_joint_lower_limit(int joint_id, double lower_limit);

        bool is_joint_selected() const;
        bool is_joint_name_reserved(const string& name) const;
        void select_joint(int id);

        int add_joint(const string& name, int parent_id);
        int remove_joint(unsigned int joint_id);

        void render(RenderingOptions rendering_options, bool glLoad = false) const;

    };

    inline string Skeleton::get_model_file() const
    {
        return _model_file;
    }

    inline DCoordinate3 Skeleton::get_model_offset() const
    {
        return _model_offset;
    }

    inline DCoordinate3 Skeleton::get_model_scale() const
    {
        return _model_scale;
    }

    inline unsigned int Skeleton::get_joint_count() const
    {
        return _joints.size();
    }

    inline int Skeleton::get_joint_parent(int joint_id) const
    {
        return _joints[joint_id].get_parent();
    }

    inline vector<unsigned int> Skeleton::get_joint_children(int joint_id) const
    {
        return _joints[joint_id].get_children();
    }

    inline Type Skeleton::get_joint_type(int joint_id) const
    {
        return _joints[joint_id].get_type();
    }

    inline DCoordinate3 Skeleton::get_joint_axis(int joint_id) const
    {
        return _joints[joint_id].get_axis();
    }

    inline double Skeleton::get_joint_length(int joint_id) const
    {
        return _joints[joint_id].get_length();
    }

    inline double Skeleton::get_joint_initial_value(int joint_id) const
    {
        return _joints[joint_id].get_initial_value();
    }

    inline double Skeleton::get_joint_upper_limit(int joint_id) const
    {
        return _joints[joint_id].get_upper_limit();
    }

    inline double Skeleton::get_joint_lower_limit(int joint_id) const
    {
        return _joints[joint_id].get_lower_limit();
    }

    inline void Skeleton::set_model_offset(const DCoordinate3& model_offset)
    {
        _model_offset = model_offset;
    }

    inline void Skeleton::set_model_scale(const DCoordinate3& model_scale)
    {
        _model_scale = model_scale;
    }

    inline void Skeleton::set_joint_parent(int joint_id, int parent_id)
    {
        _joints[_joints[joint_id].get_parent()].remove_child(joint_id);
        _joints[joint_id].set_parent(parent_id);
        _joints[parent_id].add_child(joint_id);
    }

    inline void Skeleton::set_joint_type(int joint_id, Type type)
    {
        _joints[joint_id].set_type(type);
    }

    inline void Skeleton::set_joint_axis(int joint_id, const DCoordinate3& axis)
    {
        _joints[joint_id].set_axis(axis);
    }

    inline void Skeleton::set_joint_length(int joint_id, double length)
    {
        _joints[joint_id].set_length(length);
    }

    inline void Skeleton::set_joint_initial_value(int joint_id, double initial_value)
    {
        _joints[joint_id].set_initial_value(initial_value);
    }

    inline void Skeleton::set_joint_upper_limit(int joint_id, double upper_limit)
    {
        _joints[joint_id].set_upper_limit(upper_limit);
    }

    inline void Skeleton::set_joint_lower_limit(int joint_id, double lower_limit)
    {
        _joints[joint_id].set_lower_limit(lower_limit);
    }

    inline bool Skeleton::is_joint_selected() const
    {
        return _selected_joint >= 0;
    }
}
