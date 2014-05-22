#pragma once

#include "../Core/DCoordinates3.h"
#include <vector>
namespace cagd
{
    class Skeleton
    {
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
            //Link                *_prev_link;
            std::vector<Link *> _links; // eredetileg (hibásan) pointer volt


            Joint(unsigned int id = 0, DCoordinate3 *position = 0): _id(id), _position(position) {}

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

            void AddNextLink(Link *link)
            {
                _links.push_back(link);
            }
        };

        class Link
        {
        public:
            unsigned int    _id;
            Joint           *_start;
            Joint           *_end;
            //Chain *_chain;

            Link(unsigned int id, Joint *start = 0, Joint *end = 0): _id(id), _start(start), _end(end) {}

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
        //std::vector<Chain>          _chains;
        Link                        *_root;

        void RenderLinks_(Link *link, unsigned int parent_id) const;
        void AddLink_(Joint *joint, unsigned int parent_id, unsigned int start_index, DCoordinate3 *end_coordinate);

    public:

        Skeleton(DCoordinate3 *coord1, DCoordinate3 *coord2)
        {
            _link_count = 0;
            _joint_count = 0;
            Joint *j1 = new Joint(++_joint_count, coord1);
            Joint *j2 = new Joint(++_joint_count, coord2);
            _root = new Link(++_link_count, j1, j2);

        }

        //Skeleton(unsigned int isolated_vertex_count = 0, unsigned int chain_count = 0): _vertices(isolated_vertex_count), _chains(chain_count) {}


        // vedd ki: bool SetChainLength(unsigned int chain_index, unsigned int link_count);


        //bool AddLink(unsigned int chain_index, unsigned int start_index, unsigned int end_index);

        bool AddLink(unsigned int _start_index, DCoordinate3 *end_coordinate);

        bool EraseLink(unsigned int chain_index, unsigned int link_index);


        // a vertices tömb elemeit térítik vissza érték, illetve referencia szerint

        DCoordinate3  operator [](unsigned int index) const;
        DCoordinate3& operator [](unsigned int index);


        bool RenderLinks() const;
    };


    inline bool Skeleton::Link::Render() const
    {
        if (_start && _end && _start->_position && _end->_position)
        {
            glBegin(GL_LINES);
                glVertex3dv(&(*_start->_position)[0]);
                glVertex3dv(&(*_end->_position)[0]);
            glEnd();
            glPointSize(5.0);
            glBegin(GL_POINTS);
                glVertex3dv(&(*_start->_position)[0]);
                glVertex3dv(&(*_end->_position)[0]);
            glEnd();
            glPointSize(1.0);
            return true;
        }
        return false;
    }

    inline void Skeleton::RenderLinks_(Link *link, unsigned int last_joint_id) const
    {
        link->Render();
        if (link->_start->_id != last_joint_id) {
            for (int i = 0; i < link->_start->_links.size(); i++){
                if (link->_start->_links[i]->_id != link->_id)
                {
                    RenderLinks_(link->_start->_links[i], link->_start->_id);
                }
            }
        }
        if (link->_end->_id != last_joint_id) {
            for (int i = 0; i < link->_end->_links.size(); i++){
                if (link->_end->_links[i]->_id != link->_id)
                {
                    RenderLinks_(link->_end->_links[i], link->_end->_id);
                }
            }
        }
    }

    inline bool Skeleton::RenderLinks() const
    {
        /*
        for (unsigned int i = 0; i < _chains.size(); ++i)
        {
            for (unsigned int j = 0; j < _chains[i]._links.size(); ++j)
            {
                if (!_chains[i]._links[j].Render())
                {
                    return false;
                }
            }
        }
        */

        RenderLinks_(_root, 0);
        return true;
    }


    inline DCoordinate3 Skeleton::operator [](unsigned int index) const
    {
        return _vertices[index];
    }

    inline DCoordinate3& Skeleton::operator [](unsigned int index)
    {
        return _vertices[index];
    }

    /*
    inline bool Skeleton::AddLink(unsigned int chain_index, unsigned int start_index, unsigned int end_index)
    {
        return _chains[chain_index].AddLink(start_index, end_index);
    }
    */

    inline void Skeleton::AddLink_(Joint *joint, unsigned int parent_id, unsigned int start_index, DCoordinate3 *end_coordinate)
    {
        if (joint->_id == start_index)
        {
            Joint *end_joint = new Joint(++_joint_count, end_coordinate);
            Link *link = new Link(++_link_count, joint, end_joint);
            joint->AddNextLink(link);
        }
        else
        {
            for (int i = 0; i < joint->_links.size(); i++){
                if (joint->_links[i]->_id != parent_id)
                {
                    if (joint->_links[i]->_start == joint)
                    {
                        AddLink_(joint->_links[i]->_end, joint->_links[i]->_id, start_index, end_coordinate);
                    }
                    else
                    {
                        AddLink_(joint->_links[i]->_start, joint->_links[i]->_id, start_index, end_coordinate);
                    }
                }
            }
        }
    }


    inline bool Skeleton::AddLink(unsigned int start_index, DCoordinate3 *end_coordinate)
    {
        AddLink_(_root->_start, 1, start_index, end_coordinate);
        AddLink_(_root->_end, 1, start_index, end_coordinate);
        /*
        unsigned int new_id = _vertices.size();
        _vertices[new_id] = end_coordinate;
        if (_root && _root._id == start_index)
        {
            _root.AddNextLink(new Link());
        }
        */
        return false;
    }

    inline bool EraseLink(unsigned int chain_index, unsigned int link_index)
    {
        return false;
    }

}
