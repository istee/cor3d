#include "Skeleton.h"
#include "../Core/Constants.h"

#include <cstdlib>

using namespace cagd;
using namespace std;

Skeleton::Skeleton(unsigned int id, double x, double y, double z, TriangulatedMesh3 *link_mesh, TriangulatedMesh3 *joint_mesh)
{
    _id = id;
    _link_count = 0;
    _joint_count = 0;
    _index_count = 0;

    _link_mesh = link_mesh;
    _joint_mesh = joint_mesh;

    _render_mesh = false;
    _render_links = true;
    _render_joints = true;

    _joints.push_back(Joint(new DCoordinate3(x, y, z), _joint_mesh));
}

bool Skeleton::AddLink(unsigned int start_index, double x, double y, double z)
{
    bool inserted = false;
    if (start_index < _joints.size())
    {
        int end_index = _joints.size();
        int link_index = _links.size();
        _joints.push_back(Joint(new DCoordinate3(x, y, z), _joint_mesh, link_index));
        _links.push_back(Link(start_index, end_index, _link_mesh));
        _joints[start_index].SetPreviousLink(link_index);
        inserted = true;
    }

    return inserted;
}

void Skeleton::Render(bool glLoad) const
{
    if (_render_mesh)
    {
        _mesh.Render();
    }
    if (_render_links)
    {
        RenderLinks();
    }
    if (_render_joints)
    {
        RenderJoints(glLoad);
    }
}

void Skeleton::RenderLinks() const
{
    for(std::vector<Link>::const_iterator it = _links.begin(); it != _links.end(); ++it) {
        DCoordinate3 *s = (_joints[it->StartIndex()]).Position();
        DCoordinate3 *e = (_joints[it->EndIndex()]).Position();
        it->Render(s, e);
    }
}

void Skeleton::RenderJoints(bool glLoad) const
{
    for(std::vector<Joint>::const_iterator it = _joints.begin(); it != _joints.end(); ++it) {
        it->Render();
    }
}

bool Skeleton::Link::Render(DCoordinate3 *start, DCoordinate3 *end) const
{
    if (start && end)
    {
        DCoordinate3 k_prime = *end - *start;

        float length = k_prime.length();

        k_prime /= length;

        DCoordinate3 j_prime;

        while (j_prime.length() < EPS)
        {
            j_prime =  k_prime;
            j_prime ^= DCoordinate3((double)rand() / (double)RAND_MAX , (double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX);
        }

        DCoordinate3 i_prime = j_prime;
        i_prime ^= k_prime;

        DCoordinate3 trans = *start;

        float matrix[16];

        k_prime.normalize();
        j_prime.normalize();
        i_prime.normalize();

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
            glScalef(_scale.x(), _scale.y(), length);
            _mesh->Render();
        glPopMatrix();

        return true;
    }
    return false;
}

void Skeleton::Joint::Render() const
{
    glPushMatrix();
        glTranslated(_position->x(), _position->y(), _position->z());
        glScalef(0.1, 0.1, 0.1);
        _mesh->Render();
    glPopMatrix();
}

//void Skeleton::RenderJoints_(Joint *joint, unsigned int parent_link_id, bool glLoad) const
//{
//    if (_selected->_id != joint->_id)
//    {
//        if (glLoad)
//        {
//            glLoadName(joint->_id);
//        }
//        joint->Render();
//    }
//    //cout << "Joint " << joint->_id << " rendered\n";
//    for (int i = 0; i < joint->_links.size(); i++){
//        if (joint->_links[i]->_id != parent_link_id)
//        {
//            if (joint->_links[i]->_start == joint)
//                RenderJoints_(joint->_links[i]->_end, joint->_links[i]->_id, glLoad);
//            else
//                RenderJoints_(joint->_links[i]->_start, joint->_links[i]->_id, glLoad);
//        }
//    }
//}

//void Skeleton::RenderJoints(bool glLoad) const
//{
//    RenderJoints_(_root->_start, _root->_id, glLoad);
//    RenderJoints_(_root->_end, _root->_id, glLoad);
//}

//Skeleton::Joint * Skeleton::GetJoint_(Joint *joint, unsigned int parent_link_id, unsigned int joint_id) const
//{
//    if (joint_id == joint->_id)
//    {
//        return joint;
//    }
//    else {
//        for (int i = 0; i < joint->_links.size(); i++){
//            cout << "in for i = " << i << endl;
//            if (joint->_links[i]->_id != parent_link_id)
//            {
//                Joint* id = 0;
//                if (joint->_links[i]->_start == joint)
//                    id = GetJoint_(joint->_links[i]->_end, joint->_links[i]->_id, joint_id);
//                else
//                    id = GetJoint_(joint->_links[i]->_start, joint->_links[i]->_id, joint_id);
//                if (id)
//                    return id;
//            }
//        }
//        return 0;
//    }
//}

//Skeleton::Joint * Skeleton::GetJoint(unsigned int joint_id) const
//{
//    Joint *joint = 0;
//    joint = GetJoint_(_root->_start, _root->_id, joint_id);
//    if (joint)
//    {
//        return joint;
//    }
//    else
//    {
//        return GetJoint_(_root->_end, _root->_id, joint_id);
//    }
//}

//void Skeleton::RenderSelected() const
//{
//    _selected->Render();
//}

//DCoordinate3 Skeleton::operator [](unsigned int index) const
//{
//    return _vertices[index];
//}

//DCoordinate3& Skeleton::operator [](unsigned int index)
//{
//    return _vertices[index];
//}

bool Skeleton::AddLink_(Joint *joint, unsigned int start_index, DCoordinate3 end_coordinate)
{
//    bool inserted = false;
//    cout << joint << " " << joint->_id << endl;
//    if (joint->_id == start_index)
//    {
//        cout << "hozzaadas" << endl;
//        Joint end_joint = Joint(++_index_count, &end_coordinate, _joint_mesh);
//        Link link = Link(++_index_count, joint, &end_joint, _link_mesh);
//        joint->AddNextLink(&link);
//        end_joint.SetPreviousLink(&link);
//        _vertices.push_back(end_coordinate);
//        _joints.push_back(end_joint);
//        _links.push_back(link);
//        _joint_count++;
//        _link_count++;
//        inserted = true;
//    }
//    else
//    {
//        for (unsigned int i = 0; i < joint->_next_links.size(); i++){
//            inserted = inserted | AddLink_(joint->_next_links[i]->_end, start_index, end_coordinate);
//        }
//    }
//    return inserted;
    return false;
}

//bool Skeleton::EraseLink(unsigned int chain_index, unsigned int link_index)
//{
//    return false;
//}

//void Skeleton::SetSelected(unsigned int selected_id)
//{
//    _selected = GetJoint(selected_id);
//    std::cout<<_selected<<std::endl;
//}

//unsigned int Skeleton::JointCount() const
//{
//    return _joint_count;
//}

//DCoordinate3* Skeleton::GetSelectedPosition() const
//{
//    if (_selected)
//    {
//        return (_selected->_position);
//    }
//    return 0;
//}

