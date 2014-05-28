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
            int                 _id;
            DCoordinate3        *_position;
            DCoordinate3        _scale;
            //Link                *_prev_link;
            std::vector<Link *> _links; // eredetileg (hibásan) pointer volt
            const TriangulatedMesh3 *_ptr_sphere;


            Joint(unsigned int id = 0, DCoordinate3 *position = 0, const TriangulatedMesh3 *sphere = 0): _id(id), _position(position), _ptr_sphere(sphere)
            {
                _scale = DCoordinate3(0.2, 0.2, 0.2);
            }

            Joint(const Joint& joint): _id(joint._id), _position(joint._position), _links(joint._links) {}


            Joint& operator =(const Joint& joint)
            {
                if (this != &joint)
                {
                    _id         = joint._id;
                    _position   = joint._position;
                    _links      = joint._links;
                }
                return *this;
            }

            bool operator==(const Joint& other) {
              return _id == other._id;
            }

            bool operator!=(const Joint& other) {
              return !(*this == other);
            }

            void AddNextLink(Link *link)
            {
                _links.push_back(link);
            }

            bool Render() const;
        };

        class Link
        {
        public:
            unsigned int            _id;
            Joint                   *_start;
            Joint                   *_end;

            DCoordinate3            _scale;

            const TriangulatedMesh3 *_ptr_cone;

            Link(unsigned int id, Joint *start = 0, Joint *end = 0, const TriangulatedMesh3 *cone = 0): _id(id), _start(start), _end(end), _ptr_cone(cone)
            {
                DCoordinate3 k_prime = (*_end->_position) - (*_start->_position);
                float length = k_prime.length();
                _scale = DCoordinate3(0.1, 0.1, length);
            }

            bool Render() const;

            Link(const Link& link): _id(link._id), _start(link._start), _end(link._end) {}

            Link& operator =(const Link& link)
            {
                if (this != &link)
                {
                    _id     = link._id;
                    _start  = link._start;
                    _end    = link._end;
                }
                return *this;
            }

            bool operator==(const Link& other) {
              return _id == other._id;
            }

            bool operator!=(const Link& other) {
              return !(*this == other);
            }
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
        unsigned int                _link_count;
        unsigned int                _joint_count;
        std::vector<DCoordinate3>   _vertices;
        Link                        *_root;

        TriangulatedMesh3            _sphere, _cone;

        void RenderLinks_(Link *link, unsigned int parent_id) const;
        void RenderJoints_(Joint *joint, unsigned int parent_link_id) const;
        void AddLink_(Joint *joint, unsigned int parent_id, unsigned int start_index, DCoordinate3 *end_coordinate);

    public:

        Skeleton(DCoordinate3 *coord1, DCoordinate3 *coord2);


        bool AddLink(unsigned int _start_index, DCoordinate3 *end_coordinate);

        bool EraseLink(unsigned int chain_index, unsigned int link_index);


        // a vertices tömb elemeit térítik vissza érték, illetve referencia szerint

        DCoordinate3  operator [](unsigned int index) const;
        DCoordinate3& operator [](unsigned int index);


        void RenderLinks() const;
        void RenderJoints() const;
    };
}
