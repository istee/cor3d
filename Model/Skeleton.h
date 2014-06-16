#pragma once

#include "../Core/DCoordinates3.h"
#include "../Core/TriangulatedMeshes3.h"

#include <vector>

namespace cagd
{
    class Skeleton
    {
    public:
        enum AlgorithmType{InverseKinematic, ForwardKinematic, SimpleKinematic};

    protected:

        // forward inner class declarations
        class Joint;
        class Link;
        class Chain;

        class Joint
        {
        public:
            //unsigned int        _id;
            DCoordinate3        *_position;
            DCoordinate3        _scale;
            TriangulatedMesh3   *_mesh;
            int                 _prev_link;
            std::vector<int>    _next_links;

            Joint(DCoordinate3 *position, TriangulatedMesh3 *mesh, int prev_link = -1): _position(position), _mesh(mesh), _prev_link(prev_link)
            {
                _position = position;
                std::cout << "constr pos addr: "<< position << " " << position->x() << " " << position->y() << " " << position->z() <<std::endl;
                std::cout << "constr pos addr: "<< _position << " " << _position->x() << " " << _position->y() << " " << _position->z() <<std::endl;
                _scale = DCoordinate3(0.1, 0.1, 0.1);
            }

            Joint(const Joint& joint):
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

        };

        class Link
        {
        public:
            int                     _start_index;
            int                     _end_index;
            DCoordinate3            _scale;
            TriangulatedMesh3       *_mesh;

            Link(int start_index, int end_index, TriangulatedMesh3 *mesh, double length = 0.1): _start_index(start_index), _end_index(end_index), _mesh(mesh)
            {
                _scale = DCoordinate3(0.1, 0.1, length);
            }

            Link(const Link& link):
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

        /*
        class Chain
        {
        public:
            std::vector<Link>   _links;
            std::vector<Joint>  _joints;

            bool AddLink(unsigned int start_index, unsigned int end_index)
            {
                std::cout << "added: " << start_index << " - " << end_index << "\n";
                return false;
            }
        };
        */

    protected:
        unsigned int                _id;
        unsigned int                _link_count;
        unsigned int                _joint_count;
        unsigned int                _index_count;

        //Joint                       *_root;

        TriangulatedMesh3           *_link_mesh, *_joint_mesh;
        TriangulatedMesh3           _mesh;

        //std::vector<DCoordinate3>   _vertices;
        std::vector<Link>           _links;
        std::vector<Joint>          _joints;

        Joint                       *_selected;

        bool                        _render_mesh, _render_links, _render_joints;

//        void RenderLinks_(Link *link, unsigned int parent_id) const;
//        void RenderJoints_(Joint *joint, unsigned int parent_link_id, bool glLoad) const;
        bool AddLink_(Joint *joint, unsigned int start_index, DCoordinate3 end_coordinate);

    public:

//        Joint* GetJoint(unsigned int joint_id) const;
//        Joint* GetJoint_(Joint *joint, unsigned int parent_link_id, unsigned int joint_id) const;


        Skeleton(unsigned int id, double x, double y, double z, TriangulatedMesh3 *joint_mesh, TriangulatedMesh3 *link_mesh);

        void Render(bool glLoad) const;
        void RenderLinks() const;
        void RenderJoints(bool glLoad) const;

        bool AddLink(unsigned int _start_index, double x, double y, double z);
//        bool EraseLink(unsigned int chain_index, unsigned int link_index);
//        void SetSelected(unsigned int selected_id);

//        DCoordinate3* GetSelectedPosition() const;

//        // a vertices tömb elemeit térítik vissza érték, illetve referencia szerint

//        DCoordinate3  operator [](unsigned int index) const;
//        DCoordinate3& operator [](unsigned int index);

//        void RenderSelected() const;

//        unsigned int JointCount() const;
        friend std::ostream& operator <<(std::ostream& lhs, const Skeleton& rhs)
        {
            return lhs << rhs._id;
        }
    };
}
