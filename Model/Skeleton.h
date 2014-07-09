#pragma once

#include "../Core/DCoordinates3.h"
#include "../Core/TriangulatedMeshes3.h"

#include <vector>

namespace cagd
{
    class BaseEntity
    {     
    public:
        unsigned int _id;

        BaseEntity(unsigned int id)
        {
            _id = id;
        }
    };

    class Skeleton : public BaseEntity
    {
    public:
        enum AlgorithmType{InverseKinematic, ForwardKinematic, SimpleKinematic};

    protected:

        // forward inner class declarations
        class Joint;
        class Link;
        class Chain;

        class Joint : public BaseEntity
        {
        public:
            DCoordinate3        *_position;
            DCoordinate3        _scale;
            TriangulatedMesh3   *_mesh;
            int                 _prev_link;
            std::vector<int>    _next_links;

            Joint(unsigned int id, DCoordinate3 *position, TriangulatedMesh3 *mesh, int prev_link = -1): BaseEntity(id), _position(position), _mesh(mesh)
            {
                _prev_link = prev_link;
                _scale = DCoordinate3(0.1, 0.1, 0.1);
            }

            Joint(const Joint& joint):
                BaseEntity(joint),
                _position(joint._position),
                _scale(joint._scale),
                _mesh(joint._mesh),
                _prev_link(joint._prev_link),
                _next_links(joint._next_links)
            {}

            Joint& operator =(const Joint& joint)
            {
                if (this != &joint)
                {
                    this->_id   = joint._id;
                    _position   = joint._position;
                    _scale      = joint._scale;
                    _mesh       = joint._mesh;
                    _prev_link  = joint._prev_link;
                    _next_links = joint._next_links;
                }
                return *this;
            }

            DCoordinate3* Position() const
            {
                return _position;
            }

//            bool operator==(const Joint& other) {
//              return _id == other._id;
//            }

//            bool operator!=(const Joint& other) {
//              return !(*this == other);
//            }

            void AddNextLink(int link)
            {
                _next_links.push_back(link);
            }

            void SetPreviousLink(int prev_link)
            {
                _prev_link = prev_link;
            }

            void Render() const;

            friend std::ostream& operator <<(std::ostream& lhs, const Joint& rhs)
            {
                lhs << "Joint " << rhs._id << std::endl;
                lhs << "position: " << *rhs._position << std::endl;
                lhs << "scale: " << rhs._scale << std::endl;
                lhs << "previous link: " << rhs._prev_link << std::endl << "next links: ";
                for(std::vector<int>::const_iterator it = rhs._next_links.begin(); it != rhs._next_links.end(); ++it)
                {
                    lhs << *it << " ";
                }
                lhs << std::endl;
                return lhs;
            }
        };

        class Link : public BaseEntity
        {
        public:
            int                     _start_index;
            int                     _end_index;
            DCoordinate3            _scale;
            TriangulatedMesh3       *_mesh;

            Link(unsigned int id, int start_index, int end_index, TriangulatedMesh3 *mesh, double length = 0.1):
                    BaseEntity(id),
                    _start_index(start_index),
                    _end_index(end_index),
                    _mesh(mesh)
            {
                _scale = DCoordinate3(0.1, 0.1, length);
            }

            Link(const Link& link):
                BaseEntity(link),
                _start_index(link._start_index),
                _end_index(link._end_index),
                _scale(link._scale),
                _mesh(link._mesh)
            {}

            Link& operator =(const Link& link)
            {
                if (this != &link)
                {
                    _start_index    = link._start_index;
                    _end_index      = link._end_index;
                    _scale          = link._scale;
                    _mesh           = link._mesh;
                }
                return *this;
            }

            int StartIndex() const
            {
                return _start_index;
            }

            int EndIndex() const
            {
                return _end_index;
            }

            bool Render(DCoordinate3 *start, DCoordinate3 *end) const;

            friend std::ostream& operator <<(std::ostream& lhs, const Link& rhs)
            {
                return lhs << "unimplemented";
            }

////            Link(const Link& link): _id(link._id), _start(link._start), _end(link._end) {}

////            Link& operator =(const Link& link)
////            {
////                if (this != &link)
////                {
////                    _id     = link._id;
////                    _start  = link._start;
////                    _end    = link._end;
////                }
////                return *this;
////            }

////            bool operator==(const Link& other) {
////              return _id == other._id;
////            }

////            bool operator!=(const Link& other) {
////              return !(*this == other);
////            }
        };

        class Chain
        {
        public:
            int                     _id;
            int                     _parent_id;
            std::vector<Joint>      _joints;

            Chain(int id, int parent_id)
            {
                _id         = id;
                _parent_id  = parent_id;
            }

            friend std::ostream& operator <<(std::ostream& lhs, const Chain& rhs)
            {
                lhs << "Chain " << rhs._id << std::endl;
                lhs << "Parent chain " << rhs._parent_id << std::endl;
                for (int i = 0; i < rhs._joints.size(); i++)
                {
                    lhs << rhs._joints[i];
                }

                return lhs;
            }
        };

    protected:
        TriangulatedMesh3           *_link_mesh, *_joint_mesh;
        TriangulatedMesh3           _mesh;

        std::vector<Link>           _links;
        std::vector<Joint>          _joints;

        int                         _selected;
        std::vector<Chain>          _chains;
        bool                        _chains_moved;

        bool                        _render_mesh, _render_links, _render_joints;

        unsigned int Consruct_Chains(Joint *start, int index, int parent_index, int branch_link_index = -1);
        void FABRIK(Chain *chain, DCoordinate3 target, double tolerance);
        void SimpleForwardFABRIK(Chain *chain, DCoordinate3 target, double tolerance);

    public:

//        Joint* GetJoint(unsigned int joint_id) const;
//        Joint* GetJoint_(Joint *joint, unsigned int parent_link_id, unsigned int joint_id) const;


        Skeleton(unsigned int id, double x, double y, double z, TriangulatedMesh3 mesh, TriangulatedMesh3 *joint_mesh, TriangulatedMesh3 *link_mesh, bool render_mesh = true, bool render_links = true, bool render_joints = true);

        bool GetRenderMesh();
        void SetRenderMesh(bool value);
        bool GetRenderLinks();
        void SetRenderLinks(bool value);
        bool GetRenderJoints();
        void SetRenderJoints(bool value);

        bool FirstPreviousBranch(int start_joint_id, int &previous_branch_joint_id, int &branch_link_index, int &chain_length) const;
        bool FirstNextBranch(int start_joint_id, int start_branch_link_index, int &next_branch_joint_id, int &chain_length) const;

        void SetSelected(int selected_id);
        DCoordinate3* GetSelectedPosition() const;
        void MoveSelected(double x, double y, double z);

        void Render(bool glLoad) const;
        void RenderLinks() const;
        void RenderJoints(bool glLoad, int offset = 0) const;
        void RenderChains() const;

        bool AddLink(unsigned int _start_index, double x, double y, double z);


//        // a vertices tömb elemeit térítik vissza érték, illetve referencia szerint

//        DCoordinate3  operator [](unsigned int index) const;
//        DCoordinate3& operator [](unsigned int index);

//        void RenderSelected() const;

        unsigned int JointCount() const;

        friend std::ostream& operator <<(std::ostream& lhs, const Skeleton& rhs)
        {
            lhs << "Joints: " << std::endl;
            for (int i = 0; i < rhs._joints.size(); i++)
            {
                lhs << rhs._joints[i] << std::endl;
            }

            lhs << "Chains: " << std::endl;
            for (int i = 0; i < rhs._chains.size(); i++)
            {
                lhs << rhs._chains[i] << std::endl;
            }

            int previous_branch_joint_id, branch_link_index, chain_length;
            bool b;
            lhs << "First previous branch: " << std::endl;
            for (unsigned int i = 0; i < rhs._joints.size(); i++)
            {
                b = rhs.FirstPreviousBranch(i, previous_branch_joint_id, branch_link_index, chain_length);
                lhs << "id:" << i << ", " << b <<  ", branch: " << previous_branch_joint_id << ", link:" << branch_link_index << ", length: " << chain_length << std::endl;
            }

            int next_branch_joint_id;
            lhs << "First next: " << std::endl;
            for (unsigned int i = 0; i < rhs._joints.size(); i++)
            {
                for (unsigned int j = 0; j < rhs._joints[i]._next_links.size(); j++)
                {
                    b = rhs.FirstNextBranch(11, 0, next_branch_joint_id, chain_length);
                    lhs << "id:" << i << ", " << b <<  ", link index: " << j << ", next branch:" << next_branch_joint_id << ", length: " << chain_length << std::endl;
                }
            }

            return lhs;
        }
    };
}
