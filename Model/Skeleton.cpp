#include "Skeleton.h"

using namespace cagd;
using namespace std;

Skeleton::Skeleton(DCoordinate3 *coord1, DCoordinate3 *coord2)
{
    _sphere.LoadFromOFF("Models/sphere.off");
    _sphere.UpdateVertexBufferObjects();

    _cone.LoadFromOFF("Models/cone.off");
    _cone.UpdateVertexBufferObjects();

    _link_count = 0;
    _joint_count = 0;
    Joint *j1 = new Joint(++_joint_count, coord1, &_sphere);
    Joint *j2 = new Joint(++_joint_count, coord2, &_sphere);
    _root = new Link(++_link_count, j1, j2, &_cone);


}

bool Skeleton::Link::Render() const
{
    if (_start && _end && _start->_position && _end->_position)
    {
        DCoordinate3 k_prime = (*_end->_position) - (*_start->_position);

        float length = k_prime.length();

        k_prime /= length;

        DCoordinate3 j_prime =  k_prime;
        j_prime ^= DCoordinate3(1.0, 0.0, 0.0);

        DCoordinate3 i_prime = j_prime;
        i_prime ^= k_prime;

        DCoordinate3 trans = (*_start->_position);

        float matrix[16];

        matrix[0] = i_prime[0];
        matrix[1] = i_prime[1];
        matrix[2] = i_prime[2];
        matrix[3] = 0.0;

        matrix[4] = j_prime[0];
        matrix[5] = j_prime[1];
        matrix[6] = j_prime[2];
        matrix[7] = 0.0;

        matrix[ 8] = k_prime[0];
        matrix[ 9] = k_prime[1];
        matrix[10] = k_prime[2];
        matrix[11] = 0.0;

        matrix[12] = trans[0];
        matrix[13] = trans[1];
        matrix[14] = trans[2];
        matrix[15] = 1.0;

        glPushMatrix();
            glMultMatrixf(matrix);
            //cout << "Rendering link " << _id << "scale x: " << _scale.x() << ", y: " << _scale.x() << ", z: " <<_scale.z() <<"\n";
            glScalef(_scale.x(), _scale.y(), _scale.z());

            if (_ptr_cone)
                _ptr_cone->Render();

        glPopMatrix();

        return true;
    }
    return false;
}

void Skeleton::RenderLinks_(Link *link, unsigned int last_joint_id) const
{
    link->Render();
    //cout << "Link " << link->_id << " rendered\n";
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

void Skeleton::RenderLinks() const
{
    //cout << "Started rendering links\n";
    RenderLinks_(_root, 0);
    //cout << "Stopped rendering links\n";
}

bool Skeleton::Joint::Render() const
{
    if (_position)
    {
        glPointSize(1.0);
        glPushMatrix();
            glTranslated(_position->x(), _position->y(), _position->z());
            glScalef(_scale.x(), _scale.y(), _scale.z());

            if (_ptr_sphere)
                _ptr_sphere->Render();

        glPopMatrix();

        return true;
    }
    return false;
}

void Skeleton::RenderJoints_(Joint *joint, unsigned int parent_link_id) const
{
    joint->Render();
    //cout << "Joint " << joint->_id << " rendered\n";
    for (int i = 0; i < joint->_links.size(); i++){
        if (joint->_links[i]->_id != parent_link_id)
        {
            if (joint->_links[i]->_start == joint)
                RenderJoints_(joint->_links[i]->_end, joint->_links[i]->_id);
            else
                RenderJoints_(joint->_links[i]->_start, joint->_links[i]->_id);
        }
    }
}

void Skeleton::RenderJoints() const
{
    //cout << "Started rendering joints\n";
    RenderJoints_(_root->_start, _root->_id);
    RenderJoints_(_root->_end, _root->_id);
    //cout << "Stopped rendering joints\n";
}

DCoordinate3 Skeleton::operator [](unsigned int index) const
{
    return _vertices[index];
}

DCoordinate3& Skeleton::operator [](unsigned int index)
{
    return _vertices[index];
}

void Skeleton::AddLink_(Joint *joint, unsigned int parent_id, unsigned int start_index, DCoordinate3 *end_coordinate)
{
    if (joint->_id == start_index)
    {
        Joint *end_joint = new Joint(++_joint_count, end_coordinate, &_sphere);
        Link *link = new Link(++_link_count, joint, end_joint, &_cone);
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


bool Skeleton::AddLink(unsigned int start_index, DCoordinate3 *end_coordinate)
{
    AddLink_(_root->_start, 1, start_index, end_coordinate);
    AddLink_(_root->_end, 1, start_index, end_coordinate);

    return false;
}

bool Skeleton::EraseLink(unsigned int chain_index, unsigned int link_index)
{
    return false;
}
