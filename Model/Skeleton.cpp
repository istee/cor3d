#include "Skeleton.h"
#include "../Core/Constants.h"
#include "../Core/Materials.h"

#include <cstdlib>

using namespace cagd;
using namespace std;

Skeleton::Skeleton(unsigned int id, double x, double y, double z, TriangulatedMesh3 mesh, TriangulatedMesh3 *link_mesh, TriangulatedMesh3 *joint_mesh, bool render_mesh, bool render_links, bool render_joints) : BaseEntity(id)
{
    _selected = -1;
    _chains_moved = false;

    _mesh = mesh;
    _link_mesh = link_mesh;
    _joint_mesh = joint_mesh;

    _render_mesh = render_mesh;
    _render_links = render_links;
    _render_joints = render_joints;

    _joints.push_back(Joint(0, new DCoordinate3(x, y, z), _joint_mesh, -1));
}

bool Skeleton::GetRenderMesh()
{
    return _render_mesh;
}

void Skeleton::SetRenderMesh(bool value)
{
    _render_mesh = value;
}

bool Skeleton::GetRenderLinks()
{
    return _render_links;
}

void Skeleton::SetRenderLinks(bool value)
{
    _render_links = value;
}

bool Skeleton::GetRenderJoints()
{
    return _render_joints;
}

void Skeleton::SetRenderJoints(bool value)
{
    _render_joints = value;
}

bool Skeleton::AddLink(unsigned int start_index, double x, double y, double z)
{
    bool inserted = false;
    if (start_index < _joints.size())
    {
        int end_index = _joints.size();
        int link_index = _links.size();
        _joints.push_back(Joint(end_index, new DCoordinate3(x, y, z), _joint_mesh, link_index));
        _links.push_back(Link(link_index, start_index, end_index, _link_mesh));
        _joints[end_index].SetPreviousLink(link_index);
        _joints[start_index].AddNextLink(link_index);
        inserted = true;
    }

    return inserted;
}

void Skeleton::Render(bool glLoad) const
{

    if (_render_links)
    {
        MatFBGold.Apply();
        RenderLinks();
    }
    if (_render_joints)
    {
        MatFBSilver.Apply();
        RenderJoints(glLoad);
    }

    MatFBRuby.Apply();
    RenderChains();

    if (_render_mesh)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glDepthMask(GL_FALSE);
        MatFBPearl.Apply();
        _mesh.Render();
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }
}

void Skeleton::RenderLinks() const
{
    for(std::vector<Link>::const_iterator it = _links.begin(); it != _links.end(); ++it)
    {
        DCoordinate3 *s = (_joints[it->StartIndex()]).Position();
        DCoordinate3 *e = (_joints[it->EndIndex()]).Position();
        it->Render(s, e);
    }
}

void Skeleton::RenderJoints(bool glLoad, int offset) const
{
    for(std::vector<Joint>::const_iterator it = _joints.begin(); it != _joints.end(); ++it)
    {
        if (it - _joints.begin() != _selected)
        {
            if (glLoad)
            {
                glLoadName(offset + it - _joints.begin());
            }

            it->Render();
        }
    }

    if (_selected >= 0)
    {
        MatFBBrass.Apply();
        if (glLoad)
        {
            glLoadName(offset + _selected);
        }
        _joints[_selected].Render();
    }
}

void Skeleton::RenderChains() const
{
    for (std::vector<Chain>::const_iterator chain_it = _chains.begin(); chain_it != _chains.end(); chain_it++)
    {
        for(std::vector<Joint>::const_iterator it = chain_it->_joints.begin(); it != chain_it->_joints.end(); ++it)
        {
            it->Render();
            cout << *it;
        }
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

//bool Skeleton::EraseLink(unsigned int chain_index, unsigned int link_index)
//{
//    return false;
//}

unsigned int Skeleton::Consruct_Chains(Joint *start, int index, int parent_index, int branch_link_index)
{
    if (start->_next_links.size() > 0)
    {
        cout << "nem vegpont" << endl;
        if (branch_link_index >= 0)
        {
            cout << "van branch link index" << endl;
            Chain chain = Chain(index, parent_index);
            chain._joints.push_back(*start);
            start = &_joints[_links[start->_next_links[branch_link_index]]._end_index];
            while (start->_next_links.size() == 1)
            {
                chain._joints.push_back(*start);
                start = &_joints[_links[start->_next_links[0]]._end_index];
            }
            chain._joints.push_back(*start);
            _chains.push_back(chain);
            return 1 + Consruct_Chains(start, index + 1, index);
        }
        else
        {
            int index_increase = 0;
            for (int i = 0; i < start->_next_links.size(); i++)
            {
                index_increase += Consruct_Chains(start, index + index_increase, parent_index, i);
            }
        }
    }
    return 0;
}

void Skeleton::SetSelected(int selected_id)
{
    _chains_moved = false;
    _selected = selected_id;
    if (_selected >= 0)
    {
        Joint *j = &_joints[_selected];
        bool junction = false;
        int branch_joint_id;
        int branch_link_index;
        while (j->_prev_link >= 0 && !junction)
        {
            branch_joint_id = j->_id;
            j = &_joints[_links[j->_prev_link]._start_index];
            if (j->_next_links.size() > 1)
            {
                junction = true;
                int i = 0;
                while (i < j->_next_links.size() && _links[j->_next_links[i]]._end_index != branch_joint_id)
                {
                    i++;
                }
                branch_link_index = i;
            }
        }

        Chain chain = Chain(0, -1);
        chain._joints.push_back(*j);
        j = &_joints[_links[j->_next_links[branch_link_index]]._end_index];
        while (j->_id != _selected)
        {
            chain._joints.push_back(*j);
            j = &_joints[_links[j->_next_links[0]]._end_index];
        }
        chain._joints.push_back(*j);
        _chains.push_back(chain);

        Consruct_Chains(j, 1, 0);
    }

    cout << *this;
}

void Skeleton::MoveSelected(double x, double y, double z)
{
    DCoordinate3 target(x, y, z);
    FABRIK(_chains[0], target, 0.01);
}

void Skeleton::FABRIK(Chain chain, DCoordinate3 target, double tolerance)
{
    double *lengths = new double[chain._joints.size()];
    double total_length = 0.0;
    for (int i = 0; i < chain._joints.size() - 1; i++)
    {
        lengths[i] = (*chain._joints[i]._position - *chain._joints[i + 1]._position).length();
        total_length += lengths[i];
        //cout << lengths[i] << ", ";
    }
    double distance = (target - *chain._joints[chain._joints.size() - 1]._position).length();
    //cout << total_length << ", " << distance;
    //cout << endl;
    if (distance > total_length)
    {
        for (int i = 0; i < chain._joints.size() - 1; i++)
        {
            double r = (target - *chain._joints[i]._position).length();
            double lambda = lengths[i] / r;
            chain._joints[i]._position = new DCoordinate3((1 - lambda) * *chain._joints[i]._position + lambda * target);
        }
    }
    else
    {
        DCoordinate3 b = *chain._joints[0]._position;
        double dif_A = (target - *chain._joints[chain._joints.size()]._position).length();
        while (dif_A > tolerance)
        {
            chain._joints[chain._joints.size()]._position = new DCoordinate3(target);
            for (int i = chain._joints.size() - 1; i > 0; i--)
            {
                double r = (*chain._joints[i + 1]._position - *chain._joints[i]._position).length();
                double lambda = lengths[i] / r;
                chain._joints[i]._position = new DCoordinate3((1 - lambda) * *chain._joints[i]._position + lambda * *chain._joints[i + 1]._position);
            }

            chain._joints[0]._position = new DCoordinate3(b);
            for (int i = 0; i < chain._joints.size() - 1; i++)
            {
                double r = (*chain._joints[i + 1]._position - *chain._joints[i]._position).length();
                double lambda = lengths[i] / r;
                chain._joints[i + 1]._position = new DCoordinate3((1 - lambda) * *chain._joints[i]._position + lambda * *chain._joints[i + 1]._position);
            }
            double dif_A = (target - *chain._joints[chain._joints.size()]._position).length();
        }
    }
}

DCoordinate3* Skeleton::GetSelectedPosition() const
{
    if (_selected >= 0)
    {
        return (_joints[_selected]._position);
    }
    return 0;
}

unsigned int Skeleton::JointCount() const
{
    return _joints.size();
}

