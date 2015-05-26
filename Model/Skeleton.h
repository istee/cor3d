#pragma once

#include <vector>
#include <string>

#include "Joint.h"
#include "Posture.h"
#include "Chain.h"

#include "../Core/DCoordinates3.h"
#include "../Core/TriangulatedMeshes3.h"

#include "GUI/RenderingOptions.h"

using namespace std;
using namespace cagd;

namespace cor3d
{
    //ostream& operator <<(ostream& lhs, const Skeleton& rhs);

    class Skeleton : public QObject, public BaseEntity
    {
        Q_OBJECT

        string                  _model_file;
        TriangulatedMesh3       _model;
        DCoordinate3            _model_offset;
        DCoordinate3            _model_scale;

        vector<Posture>         _postures;
        vector<DCoordinate3>    _current_posture;
        vector<Chain>           _chains;
        vector<Joint>           _joints;
        bool                    _chains_moved;
        int                     _selected_joint;

        bool                    _coordinates_need_update;


    public:
        Skeleton();
        Skeleton(unsigned int id, const string& name);


        //int construct_chains_(int joint_id, int chain_index, int parent_chain_index);
        //void construct_chains();

       void forward_chain(Chain& chain, int joint_id);
        void construct_chains();
        int construct_chains_(int joint_id, int chain_index, int parent_chain_index);

        void clear_chains();


        ///////////////////////////
        // getter methods        //
        ///////////////////////////
        string get_model_file() const;
        DCoordinate3 get_model_offset() const;
        DCoordinate3 get_model_scale() const;
        unsigned int get_joint_count() const;
        vector<BaseEntity> get_joint_list() const;
        vector<BaseEntity> get_possible_parents(unsigned int id) const;

        int get_selected_joint_id() const;
        const string& get_joint_name(int joint_id) const;
        int get_joint_parent(int joint_id) const;
        vector<unsigned int> get_joint_children(int joint_id) const;
        Type get_joint_type(int joint_id) const;
        const DCoordinate3& get_joint_axis(int joint_id) const;
        const DCoordinate3& get_joint_orientation(int joint_id) const;
        double get_joint_length(int joint_id) const;
        const DCoordinate3& get_joint_configuration(int joint_id) const;
        const DCoordinate3& get_joint_coordinates(int joint_id) const;
        const DCoordinate3 get_joint_parent_coordinates(int joint_id) const;

        Joint get_joint(const string& name);
        vector<BaseEntity*> get_joint_list2();

        ///////////////////////////
        // setter methods        //
        ///////////////////////////
        void set_name(const string &name);
        void set_model_file(const string& file_name);
        void set_model_offset(const DCoordinate3& model_offset);
        void set_model_scale(const DCoordinate3& model_scale);

        bool is_joint_selected() const;
        void select_joint(int id);

        string next_joint_name() const;
        bool is_joint_name_reserved(const string& name) const;
        string append_sequence_number(const string& name) const;

        void remove_joint(unsigned int joint_id);

        void update_joint_coordinates();
        void render(RenderingOptions* rendering_options, bool glLoad = false);
        void render_joints(RenderingOptions* rendering_options, bool glLoad = false) const;
        void render_links(RenderingOptions* rendering_options, bool glLoad = false) const;
        void render_axis(RenderingOptions* rendering_options, bool glLoad = false) const;
        void render_chains(RenderingOptions* rendering_options, bool glLoad = false) const;


    private:
        void update_joint_coordinates_(unsigned int joint_id, const DCoordinate3& parent_coordinates);
        bool validate_joint_index_(int joint_id) const;
        void MoveSelected(double x, double y, double z);
        void FABRIK(Chain& chain, DCoordinate3 target, double tolerance);

    public slots:
        void handle_view_joint_added(const string&,int);
        void handle_view_joint_selection_changed(int);
        void handle_view_joint_parent_changed(int);
        void handle_view_joint_type_changed(int);
        void handle_view_joint_orientation_changed(const DCoordinate3&);
        void handle_view_joint_axis_changed(const DCoordinate3&);
        void handle_view_joint_configuration_changed(const DCoordinate3&);
        void handle_view_joint_absolute_position_changed(const DCoordinate3&);
        void handle_view_joint_fabrik_moved(const DCoordinate3&);

    signals:
        void model_joint_list_changed();
        void model_joint_selection_changed();
        void model_joint_data_changed();

    private:
        friend std::ostream& operator <<(std::ostream& lhs, const Skeleton& rhs)
        {
            lhs << "skeleton_name: " << rhs.get_name() << endl;
            bool hasModelFile = "" != rhs.get_model_file();
            lhs << "skeleton_has_model_file: " << hasModelFile << endl;
            if (hasModelFile)
            {
                lhs << "skeleton_model_file: " << rhs.get_model_file() << endl;
                lhs << "skeleton_model_offset: " << rhs.get_model_offset() << endl;
                lhs << "skeleton_model_scale: " <<rhs.get_model_scale() << endl;
            }
            lhs << "skeleton_joint_count: " << rhs.get_joint_count() << endl;
            for (vector<Joint>::const_iterator it = rhs._joints.begin(); it != rhs._joints.end(); it++)
            {
                lhs << *it;
            }
            return lhs;
        }

        friend std::istream& operator >>(std::istream& lhs, Skeleton& rhs)
        {
            string text;
            char name[256];
            int number;
            bool boolean;

            lhs >> text;
            lhs.getline(name, 256);
            rhs.set_name(string(name));
            lhs >> text >> boolean;
            if (boolean)
            {
                lhs >> text >> text;
                rhs.set_model_file(text);
            }
            lhs >> text >> rhs._model_offset;
            lhs >> text >> rhs._model_scale;
            lhs >> text >> number;
            cout << "joint_number: " << number << endl;
            for (int i = 0; i < number; i++)
            {
                Joint joint(i, "", 0);
                lhs >> joint;
                rhs._joints.push_back(joint);
            }
            rhs._coordinates_need_update = true;
            return lhs;
        }

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

    inline int Skeleton::get_selected_joint_id() const
    {
        return _selected_joint;
    }

    inline const string& Skeleton::get_joint_name(int joint_id) const
    {
        return _joints[joint_id].get_name();
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

    inline const DCoordinate3& Skeleton::get_joint_axis(int joint_id) const
    {
        return _joints[joint_id].get_axis();
    }

    inline const DCoordinate3& Skeleton::get_joint_orientation(int joint_id) const
    {
        return _joints[joint_id].get_orientation();
    }

    inline double Skeleton::get_joint_length(int joint_id) const
    {
        return _joints[joint_id].get_length();
    }

    inline const DCoordinate3& Skeleton::get_joint_configuration(int joint_id) const
    {
        return _joints[joint_id].get_configuration();
    }

    inline const DCoordinate3& Skeleton::get_joint_coordinates(int joint_id) const
    {
        return _joints[joint_id].get_coordinates();
    }

    inline const DCoordinate3 Skeleton::get_joint_parent_coordinates(int joint_id) const
    {
        if (!validate_joint_index_(joint_id))
        {
            return DCoordinate3();
        }
        int parent_id = get_joint_parent(joint_id);
        if (!validate_joint_index_(parent_id))
        {
            return DCoordinate3();
        }
        return _joints[parent_id].get_coordinates();
    }

    inline void Skeleton::set_name(const string &name)
    {
        BaseEntity::set_name(name);
        //emit model_joint_list_changed();
    }

    inline void Skeleton::set_model_offset(const DCoordinate3& model_offset)
    {
        _model_offset = model_offset;
        //emit model_joint_data_changed();
    }

    inline void Skeleton::set_model_scale(const DCoordinate3& model_scale)
    {
        _model_scale = model_scale;
        //emit model_joint_data_changed();
    }


//    inline void Skeleton::set_joint_length(int joint_id, double length)
//    {
//        _joints[joint_id].set_length(length);
//    }

    inline bool Skeleton::is_joint_selected() const
    {
        return _selected_joint >= 0;
    }




}

