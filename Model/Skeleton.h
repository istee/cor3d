#pragma once

#include <vector>
#include <string>

#include "Model/ISkeleton.h"
#include "Joint.h"
#include "Posture.h"

#include "../Core/DCoordinates3.h"
#include "../Core/TriangulatedMeshes3.h"

<<<<<<< HEAD
#include "GUI/RenderingOptions.h"

=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
using namespace std;
using namespace cagd;

namespace cor3d
{
<<<<<<< HEAD
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
=======
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa

    inline string Skeleton::get_model_file() const
    {
<<<<<<< HEAD
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
=======
    public:
        Skeleton(unsigned int id, string name): BaseEntity(id, name) {}
        int set_model(string file);
        void set_model_offset(double x, double y, double z);
        unsigned int add_joint();

        string get_model_file();
        double get_model_x();
        double get_model_y();
        double get_model_z();


        void select_joint(int id);


    private:
        string              _model_file;
        TriangulatedMesh3   _model;
        DCoordinate3        _model_offset;
        vector<Joint>       _joints;
        vector<Posture>     _postures;
        int                 _selected_joint;


//        enum AlgorithmType{InverseKinematic, ForwardKinematic, SimpleKinematic};
//    protected:

//        // forward inner class declarations
//        class Joint;
//        class Link;
//        class Chain;

//        class Joint : public BaseEntity
//        {
//            enum Type{ROTATIONAL, TRANSLATIONAL};

//        public:
//            DCoordinate3        *_position; // p_j = s_j
//            DCoordinate3        _scale;
//            TriangulatedMesh3   *_mesh;
//            int                 _prev_link;
//            std::vector<int>    _next_links;

//            DCoordinate3        *_unit_axis; // v_j
//            double              *_theta;     // theta_j
//            Type                 _type;      // page 5
//            std::vector<int>     _dependent_end_effector_list;

//            Joint(unsigned int id, DCoordinate3 *position, TriangulatedMesh3 *mesh, int prev_link = -1): BaseEntity(id), _position(position), _mesh(mesh)
//            {
//                _prev_link = prev_link;
//                _scale = DCoordinate3(0.1, 0.1, 0.1);
//            }

//            Joint(const Joint& joint):
//                BaseEntity(joint),
//                _position(joint._position),
//                _scale(joint._scale),
//                _mesh(joint._mesh),
//                _prev_link(joint._prev_link),
//                _next_links(joint._next_links)
//            {}

//            Joint& operator =(const Joint& joint)
//            {
//                if (this != &joint)
//                {
//                    this->_id   = joint._id;
//                    _position   = joint._position;
//                    _scale      = joint._scale;
//                    _mesh       = joint._mesh;
//                    _prev_link  = joint._prev_link;
//                    _next_links = joint._next_links;
//                }
//                return *this;
//            }

//            DCoordinate3* Position() const
//            {
//                return _position;
//            }

////            bool operator==(const Joint& other) {
////              return _id == other._id;
////            }

////            bool operator!=(const Joint& other) {
////              return !(*this == other);
////            }

//            void AddNextLink(int link)
//            {
//                _next_links.push_back(link);
//            }

//            void SetPreviousLink(int prev_link)
//            {
//                _prev_link = prev_link;
//            }

//            void Render() const;

//            friend std::ostream& operator <<(std::ostream& lhs, const Joint& rhs)
//            {
//                lhs << "Joint " << rhs._id << std::endl;
//                lhs << "position: " << *rhs._position << std::endl;
//                lhs << "scale: " << rhs._scale << std::endl;
//                lhs << "previous link: " << rhs._prev_link << std::endl << "next links: ";
//                for(std::vector<int>::const_iterator it = rhs._next_links.begin(); it != rhs._next_links.end(); ++it)
//                {
//                    lhs << *it << " ";
//                }
//                lhs << std::endl;
//                return lhs;
//            }
//        };

//        class Link : public BaseEntity
//        {
//        public:
//            int                     _start_index;
//            int                     _end_index;
//            DCoordinate3            _scale;
//            TriangulatedMesh3       *_mesh;

//            Link(unsigned int id, int start_index, int end_index, TriangulatedMesh3 *mesh, double length = 0.1):
//                    BaseEntity(id),
//                    _start_index(start_index),
//                    _end_index(end_index),
//                    _mesh(mesh)
//            {
//                _scale = DCoordinate3(0.1, 0.1, length);
//            }

//            Link(const Link& link):
//                BaseEntity(link),
//                _start_index(link._start_index),
//                _end_index(link._end_index),
//                _scale(link._scale),
//                _mesh(link._mesh)
//            {}

//            Link& operator =(const Link& link)
//            {
//                if (this != &link)
//                {
//                    _start_index    = link._start_index;
//                    _end_index      = link._end_index;
//                    _scale          = link._scale;
//                    _mesh           = link._mesh;
//                }
//                return *this;
//            }

//            int StartIndex() const
//            {
//                return _start_index;
//            }

//            int EndIndex() const
//            {
//                return _end_index;
//            }

//            bool Render(DCoordinate3 *start, DCoordinate3 *end) const;

//            friend std::ostream& operator <<(std::ostream& lhs, const Link& rhs)
//            {
//                return lhs << "unimplemented";
//            }

//////            Link(const Link& link): _id(link._id), _start(link._start), _end(link._end) {}

//////            Link& operator =(const Link& link)
//////            {
//////                if (this != &link)
//////                {
//////                    _id     = link._id;
//////                    _start  = link._start;
//////                    _end    = link._end;
//////                }
//////                return *this;
//////            }

//////            bool operator==(const Link& other) {
//////              return _id == other._id;
//////            }

//////            bool operator!=(const Link& other) {
//////              return !(*this == other);
//////            }
//        };

//        class Chain
//        {
//        public:
//            int                     _id;
//            int                     _parent_id;
//            bool                    _forward;
//            std::vector<Joint>      _joints;

//            Chain(int id, int parent_id, bool forward)
//            {
//                _id         = id;
//                _parent_id  = parent_id;
//                _forward    = forward;
//            }

//            DCoordinate3 GetChainStart()
//            {
//                return _forward ? *_joints[0]._position : *_joints[_joints.size() - 1]._position;
//            }

//            DCoordinate3 GetChainEnding()
//            {
//                return _forward ? *_joints[_joints.size() - 1]._position : *_joints[0]._position;
//            }

//            friend std::ostream& operator <<(std::ostream& lhs, const Chain& rhs)
//            {
//                lhs << "Chain " << rhs._id << std::endl;
//                lhs << "Parent chain " << rhs._parent_id << std::endl;
//                for (int i = 0; i < rhs._joints.size(); i++)
//                {
//                    lhs << rhs._joints[i];
//                }

//                return lhs;
//            }
//        };

//    protected:
//        TriangulatedMesh3           *_link_mesh, *_joint_mesh;
//        TriangulatedMesh3           _mesh;

//        std::vector<Link>           _links;
//        std::vector<Joint>          _joints;

//        int                         _selected;
//        std::vector<Chain>          _chains;
//        bool                        _chains_moved;

//        bool                        _render_mesh, _render_links, _render_joints;

//        unsigned int ConstructChains(int joint_index, int chain_index, int chain_parent_index, int branch_link_index = -1);
//        void FABRIK(Chain *chain, DCoordinate3 target, double tolerance/**/);
//        void SimpleForwardFABRIK(Chain *chain, DCoordinate3 target, double tolerance);

//        // calculates the Jacobian matrix based on formulas given in page 5 (you will have to decompose the resulted vectors to coordinates)
//        // store the Jacobian in a templated matrix with template parameter double
//        // implement the algorithm presented in Section 3

//        void JacobianTransposeAsInerse(Chain *chain, const DCoordinate3& target, double tolerance);

//    public:

////        Joint* GetJoint(unsigned int joint_id) const;
////        Joint* GetJoint_(Joint *joint, unsigned int parent_link_id, unsigned int joint_id) const;


//        Skeleton(unsigned int id, double x, double y, double z, TriangulatedMesh3 mesh, TriangulatedMesh3 *joint_mesh, TriangulatedMesh3 *link_mesh, bool render_mesh = true, bool render_links = true, bool render_joints = true);

//        bool GetRenderMesh();
//        void SetRenderMesh(bool value);
//        bool GetRenderLinks();
//        void SetRenderLinks(bool value);
//        bool GetRenderJoints();
//        void SetRenderJoints(bool value);

//        bool FirstPreviousBranch(int start_joint_id, int &previous_branch_joint_id, int &branch_link_index, int &chain_length) const;
//        bool FirstNextBranch(int start_joint_id, int start_branch_link_index, int &next_branch_joint_id, int &chain_length) const;
//        void ForwardChain(unsigned int start_joint_id, unsigned int branch_link_index, unsigned int end_joint_id, Chain &chain) const;
//        void BackwardChain(unsigned int start_joint_id, unsigned int end_joint_id, Chain &chain) const;

//        void SetSelected(int selected_id);
//        DCoordinate3* GetSelectedPosition() const;
//        void MoveSelected(double x, double y, double z);
//        void FinalizeMove();

//        void Render(bool glLoad) const;
//        void RenderLinks() const;
//        void RenderJoints(bool glLoad, int offset = 0) const;
//        void RenderChains() const;

//        bool AddLink(unsigned int _start_index, double x, double y, double z);


////        // a vertices tömb elemeit térítik vissza érték, illetve referencia szerint

////        DCoordinate3  operator [](unsigned int index) const;
////        DCoordinate3& operator [](unsigned int index);

////        void RenderSelected() const;

//        unsigned int JointCount() const;

//        friend std::ostream& operator <<(std::ostream& lhs, const Skeleton& rhs)
//        {
//            lhs << "Joints: " << std::endl;
//            for (int i = 0; i < rhs._joints.size(); i++)
//            {
//                lhs << rhs._joints[i] << std::endl;
//            }

//            lhs << "Chains: " << std::endl;
//            for (int i = 0; i < rhs._chains.size(); i++)
//            {
//                lhs << rhs._chains[i] << std::endl;
//            }

////            int previous_branch_joint_id, branch_link_index, chain_length;
////            bool b;
////            lhs << "First previous branch: " << std::endl;
////            for (unsigned int i = 0; i < rhs._joints.size(); i++)
////            {
////                b = rhs.FirstPreviousBranch(i, previous_branch_joint_id, branch_link_index, chain_length);
////                lhs << "id:" << i << ", " << b <<  ", branch: " << previous_branch_joint_id << ", link:" << branch_link_index << ", length: " << chain_length << std::endl;
////            }

////            int next_branch_joint_id;
////            lhs << "First next: " << std::endl;
////            for (unsigned int i = 0; i < rhs._joints.size(); i++)
////            {
////                for (unsigned int j = 0; j < rhs._joints[i]._next_links.size(); j++)
////                {
////                    b = rhs.FirstNextBranch(11, 0, next_branch_joint_id, chain_length);
////                    lhs << "id:" << i << ", " << b <<  ", link index: " << j << ", next branch:" << next_branch_joint_id << ", length: " << chain_length << std::endl;
////                }
////            }

//            return lhs;
//        }
    };
>>>>>>> 02c1ac8644f385b7fac8a4d9a287600b2a0f14aa
}
