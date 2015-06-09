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

        friend std::ostream& operator <<(std::ostream& lhs, const Skeleton& rhs);
        friend std::istream& operator >>(std::istream& lhs, Skeleton& rhs);

        string                  _model_file;
        TriangulatedMesh3       _model;
        DCoordinate3            _model_offset;
        DCoordinate3            _model_scale;

        vector<Posture*>        _postures;
        vector<Joint*>          _joints;
        int                     _selectedJoint;
        int                     _selectedPosture;


    public:
        Skeleton();
        Skeleton(unsigned int id, const string& name);


        void addRoot();

        void addJoint(const string& parentName, const string& jointName);

        void addPosture(const string& name);
        void deletePosture(const string& name);
        void renamePosture(const string& oldName, const string& newName);


        ///////////////////////////
        // getter methods        //
        ///////////////////////////
        string get_model_file() const;
        DCoordinate3 get_model_offset() const;
        DCoordinate3 get_model_scale() const;
        unsigned int get_joint_count() const;
        vector<BaseEntity*> get_joint_list() const;
        vector<BaseEntity*> get_possible_parents(unsigned int id) const;

        int get_selectedJoint_id() const;
        unsigned int getJointIdByName(const string& name) const;

        Joint* get_joint(unsigned int id) const;
        Joint* get_joint(const string& name) const;
        Joint* get_parent_joint(const string& name) const;
        Joint* get_selectedJoint() const;

        Posture* selectedPosture() const;


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

        //void update_joint_coordinates();
        void render(RenderingOptions* rendering_options, bool glLoad = false);
        void render_joints(RenderingOptions* rendering_options, bool glLoad = false) const;
        void render_links(RenderingOptions* rendering_options, bool glLoad = false) const;
        void render_axis(RenderingOptions* rendering_options, bool glLoad = false) const;

        string nextAutoPostureName() const;
        Posture* getPostureByName(const string& name) const;
        Posture* getPostureById(int id);
        unsigned int postureCount() const;


    private:
        //void update_joint_coordinates_(unsigned int joint_id, const DCoordinate3& parent_coordinates);
        bool validate_joint_index_(int joint_id) const;
        void deleteJoint(unsigned int jointId);
        void prepareDeleteJoints(unsigned int jointId, vector<unsigned int>& result);
        void handle_view_joint_CoordinatesChanged_(unsigned int jointId);

    public slots:

        void handleViewJointAdded(const string& name, const string& parentName);
        void handleViewJointDeleted(const string&);
        void handleViewJointRenamed(const string&, const string&);
        void handleViewJointSelected(const string&);

        void handle_view_joint_selectionChanged(int);

        void handleViewJointAbsoluteCoordinatesChanged(const string& name, const DCoordinate3& absoluteCoordinates);
        void handleViewJointRelativeCoordinatesChanged(const string& name, const DCoordinate3& relativeCoordinates);
        void handleViewJointScaleChanged(const string& name, const DCoordinate3& scale);

        void handle_view_joint_rotation_axis_changed(const string&, const DCoordinate3& rotation_axis);
        void handle_view_joint_rotation_constraint_changed(const string&, const DCoordinate3& rotation_constraint);

        void handle_view_joint_parent_changed(int);
        void handle_view_joint_type_changed(int);
        void handle_view_joint_orientation_changed(const DCoordinate3&);
        void handle_view_joint_axis_changed(const DCoordinate3&);
        void handle_view_joint_configuration_changed(const DCoordinate3&);
        void handle_view_joint_absolute_position_changed(const DCoordinate3&);

        void handleViewPostureAdded(const string&);
        void handleViewPostureDeleted(const string&);
        void handleViewPostureRenamed(const string&, const string&);
        void handleViewPostureSelected(const string&);

        void handleViewSkeletonModelChanged(const string&);
        void handleViewSkeletonModelScaleChanged(const DCoordinate3&);
        void handleViewSkeletonModelOffsetChanged(const DCoordinate3&);

    signals:
        void modelSkeletonDataChanged(Skeleton* skeleton);

        void model_joint_selectionChanged();

        void modelJointAdded(Skeleton* skeleton, Joint* joint, const string& parentName);
        void modelJointRenamed(const string& oldName, const string& newName);
        void modelJointDeleted(const string& name);
        void modelJointSelected(const string& name);
        void modelJointParentChanged(const string& name, const string& oldParentName, const string& newParentName);
        void modelJointDataChanged(Joint* joint);

        void modelPostureAdded(Skeleton* skeleton, Posture* posture);
        void modelPostureDeleted(Skeleton* skeleton, const string& postureName);
        void modelPostureRenamed(const string& oldPostureName, const string& newPostureName);
        void modelPostureSelected(Skeleton* skeleton, Posture* posture);
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

    inline int Skeleton::get_selectedJoint_id() const
    {
        return _selectedJoint;
    }

    inline void Skeleton::set_name(const string &name)
    {
        BaseEntity::set_name(name);
        //emit model_joint_list_changed();
    }

    inline void Skeleton::set_model_offset(const DCoordinate3& model_offset)
    {
        _model_offset = model_offset;
        emit modelSkeletonDataChanged(this);
    }

    inline void Skeleton::set_model_scale(const DCoordinate3& model_scale)
    {
        _model_scale = model_scale;
        emit modelSkeletonDataChanged(this);
    }


//    inline void Skeleton::set_joint_length(int joint_id, double length)
//    {
//        _joints[joint_id].set_length(length);
//    }

    inline bool Skeleton::is_joint_selected() const
    {
        return _selectedJoint >= 0;
    }

    inline Posture* Skeleton::selectedPosture() const
    {
        if (_selectedPosture >=0 && _selectedPosture < _postures.size())
        {
            return _postures[_selectedPosture];
        }

        return 0;
    }


}

