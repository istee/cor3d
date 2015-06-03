#include "Skeleton.h"

#include <sstream>

#include "Core/Materials.h"
#include "Model/Joint.h"

namespace cor3d {

    std::ostream& operator <<(std::ostream& lhs, const Skeleton& rhs)
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
        for (vector<Joint*>::const_iterator it = rhs._joints.begin(); it != rhs._joints.end(); it++)
        {
            lhs << **it;
        }
        return lhs;
    }

    std::istream& operator >>(std::istream& lhs, Skeleton& rhs)
    {
        string text;
        char name[256];
        int number;
        bool boolean;

        lhs >> text >> std::skipws;
        lhs.getline(name, 256);
        rhs.set_name(string(name));
        lhs >> text >> boolean;
        if (boolean)
        {
            lhs >> text >> text;
            rhs.set_model_file(text);
            lhs >> text >> rhs._model_offset;
            lhs >> text >> rhs._model_scale;
        }
        lhs >> text >> number;
        for (int i = 0; i < number; i++)
        {
            Joint* joint = new Joint(i, "", 0);
            lhs >> *joint;
            rhs._joints.push_back(joint);
        }
        rhs._coordinates_need_update = true;
        return lhs;
    }

    Skeleton::Skeleton(): QObject(), BaseEntity()
    {
        _model_scale = DCoordinate3(1.0, 1.0, 1.0);
        _model_offset = DCoordinate3(0, 0, 0);
        _selected_joint = -1;
        _coordinates_need_update = false;
    }

    Skeleton::Skeleton(unsigned int id, const string& name): QObject(), BaseEntity(id, name)
    {
        _model_scale = DCoordinate3(1.0, 1.0, 1.0);
        _model_offset = DCoordinate3(0, 0, 0);
        _selected_joint = -1;
        _coordinates_need_update = false;
    }

    void Skeleton::addRoot()
    {
        if (_joints.size() == 0)
        {
            _joints.push_back(new Joint(0, "root", -1));
        }
    }

    unsigned int Skeleton::getJointIdByName(const string& name) const
    {
        return get_id_by_name<Joint>(name, _joints);
    }

    void Skeleton::addJoint(const string& parentName, const string& jointName)
    {
        unsigned int parentId = getJointIdByName(parentName);
        Joint* parent = get_joint(parentId);
        if (parent)
        {
            Joint* joint = new Joint(_joints.size(), jointName, parentId);
            joint->set_coordinate(parent->get_coordinates());
            joint->set_axis(parent->get_axis());
            joint->set_orientation(parent->get_orientation());
            _joints.push_back(joint);
            parent->add_child(joint->get_id());
            emit model_joint_added(joint->get_name());
        }
    }

    Joint* Skeleton::get_joint(unsigned int id) const
    {
        return _joints[id];
    }

    Joint* Skeleton::get_joint(const string& name) const
    {
        int id = getJointIdByName(name);
        if (validate_joint_index_(id))
        {
            return _joints[id];
        }

        return 0;
    }

    Joint* Skeleton::get_parent_joint(const string& name) const
    {
        int parentId = get_joint(name)->get_parent();
        if (validate_joint_index_(parentId))
        {
            return _joints[parentId];
        }

        return 0;
    }

    Joint* Skeleton::get_selected_joint() const
    {
        if (_selected_joint >= 0 && _selected_joint < _joints.size())
        {
            return _joints[_selected_joint];
        }

        return 0;
    }

    int Skeleton::construct_chains_(int joint_id, int chain_index, int parent_chain_index)
    {

        Chain chain = Chain(chain_index, parent_chain_index, false);
        chain.add_joint_to_front(get_joint(get_joint(joint_id)->get_parent())->get_coordinates());
        while(get_joint(joint_id)->get_children().size() == 1)
        {
            chain.add_joint_to_front(get_joint(joint_id)->get_coordinates());
            joint_id = get_joint(joint_id)->get_children()[0];
        }
        chain.add_joint_to_front(get_joint(joint_id)->get_coordinates());
        _chains.push_back(chain);
        vector<unsigned int> children = get_joint(joint_id)->get_children();
        int chain_number = 1;
        for (vector<unsigned int>::iterator it = children.begin(); it != children.end(); it++)
        {
            chain_number += construct_chains_(*it, chain_index + chain_number, chain_index);
        }
        return chain_number;
    }

    void Skeleton::construct_chains()
    {
        update_joint_coordinates();
        if (_selected_joint >= 0)
        {
            Chain chain = Chain(0, -1, true);
            forward_chain(chain, _selected_joint);
            _chains.push_back(chain);
            vector<unsigned int> children = get_joint(_selected_joint)->get_children();
            int chain_number = 1;
            for (vector<unsigned int>::iterator it = children.begin(); it != children.end(); it++)
            {
                chain_number += construct_chains_(*it, chain_number, 0);
            }
        }
    }

    void Skeleton::forward_chain(Chain& chain, int joint_id)
    {
        int index = joint_id;
        while(get_joint(index)->get_parent() != -1 && get_joint(get_joint(index)->get_parent())->get_children().size() == 1)
        {
            index = get_joint(index)->get_parent();
        }
        if (get_joint(index)->get_parent() != -1)
        {
            chain.add_joint(get_joint(get_joint(index)->get_parent())->get_coordinates());
        }
        while (index != joint_id)
        {
            chain.add_joint(get_joint(index)->get_coordinates());
            index = get_joint(index)->get_children()[0];
        }
        chain.add_joint(get_joint(joint_id)->get_coordinates());
    }

    void Skeleton::MoveSelected(double x, double y, double z)
    {
        DCoordinate3 target(x, y, z);
        FABRIK(_chains[0], target, 1e-10);
//        for (unsigned int i = 1; i < _chains.size(); i++)
//        {
//            SimpleForwardFABRIK(&_chains[i], _chains[_chains[i]._parent_id].GetChainEnding(), 1e-10);
//        }
//        for (vector<Chain>::iterator it = _chains.begin(); it != _chains.end(); it++)
//            for(int i = 0; i )
    }
    void Skeleton::FABRIK(Chain& chain, DCoordinate3 target, double tolerance)
        {
            double *lengths = new double[chain.get_chain_size()];
            double total_length = 0.0;
            for (int i = 0; i < chain.get_chain_size() - 1; i++)
            {
                lengths[i] = (chain.get_joint_coordinates(i) - chain.get_joint_coordinates(i + 1)).length();
                total_length += lengths[i];
            }
            double distance = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length();
            if (distance > total_length)
            {
                for (int i = 0; i < chain.get_chain_size() - 1; i++)
                {
                    double r = (target - chain.get_joint_coordinates(i)).length();
                    double lambda = lengths[i] / r;

                    // innen folytatni
                    chain.set_joint_coodinates(DCoordinate3((1 - lambda) * chain.get_joint_coordinates(i) + lambda * target), i + 1);
                }
            }
            else
            {
                DCoordinate3 b = DCoordinate3(chain.get_joint_coordinates(0));
                double dif_A = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length();
                unsigned int iteration_count = 0, max_iteration = 10;
                while (dif_A > tolerance && iteration_count < max_iteration)
                {
                    iteration_count++;
                    chain.set_joint_coodinates(DCoordinate3(target), chain.get_chain_size() - 1);
                    for (int i = chain.get_chain_size() - 2; i >= 0; i--)
                    {
                        double r = (chain.get_joint_coordinates(i + 1) - chain.get_joint_coordinates(i)).length();
                        double lambda = lengths[i] / r;
                        chain.set_joint_coodinates((1 - lambda) * chain.get_joint_coordinates(i + 1) + lambda * chain.get_joint_coordinates(i), i);
                    }
                    chain.set_joint_coodinates(b, 0);
                    for (int i = 0; i < chain.get_chain_size() - 1; i++)
                    {
                        double r = (chain.get_joint_coordinates(i + 1) - chain.get_joint_coordinates(i)).length();
                        double lambda = lengths[i] / r;
                        chain.set_joint_coodinates( DCoordinate3((1 - lambda) * chain.get_joint_coordinates(i) + lambda * chain.get_joint_coordinates(i + 1)), i + 1);
                    }
                    dif_A = (target - chain.get_joint_coordinates(chain.get_chain_size() - 1)).length();
                }
            }
        }

    void Skeleton::clear_chains()
    {
        _chains.clear();
    }

    void Skeleton::deleteJoint(unsigned int jointId)
    {
        vector<unsigned int> deleteJoints = vector<unsigned int>();
        prepareDeleteJoints(jointId, deleteJoints);

        for (unsigned int i = 0; i < deleteJoints.size(); i++)
        {
            cout << " " << deleteJoints[i];
        }
        cout << endl;

        Joint* parent = get_joint(get_joint(jointId)->get_parent());
        parent->remove_child(jointId);

        unsigned offset = 0;
        for (unsigned int i = 0; i < deleteJoints.size(); i++)
        {
            unsigned int newId = deleteJoints[i] - offset;
            delete _joints[newId];
            _joints.erase(_joints.begin() + newId);
            for (vector<Joint*>::iterator it = _joints.begin() + newId; it != _joints.end(); it++)
            {
                Joint* j = *it;
                j->decrease_id();

                if (!count(deleteJoints.begin(), deleteJoints.end(), j->get_parent()))
                {
                    if (j->get_parent() >= newId)
                    {
                        j->set_parent(j->get_parent() - 1);
                    }

                    Joint* parent = get_joint(j->get_parent());
                    parent->remove_child(j->get_id() + 1);
                    parent->add_child(j->get_id());
                }
            }
            offset++;
        }
    }

    void Skeleton::prepareDeleteJoints(unsigned int jointId, vector<unsigned int>& result)
    {
        Joint* joint = _joints[jointId];
        result.push_back(jointId);
        for (unsigned int i = 0; i < joint->get_children().size(); i++)
        {
            prepareDeleteJoints(joint->get_children()[i],  result);
        }
    }

    vector<BaseEntity*> Skeleton::get_joint_list() const
    {
        vector<BaseEntity*> joint_list = vector<BaseEntity*>();
        for (std::vector<Joint*>::const_iterator it = _joints.begin(); it != _joints.end(); it++)
        {
            joint_list.push_back((BaseEntity*) *it);
        }

        return joint_list;
    }

    vector<BaseEntity*> Skeleton::get_possible_parents(unsigned int id) const
    {

        vector<BaseEntity*> possible_parents;
        if (_joints.size() > 0 && id != get_joint(0)->get_id())
        {
            vector<unsigned int> possible_parent_ids;
            possible_parent_ids.push_back(get_joint(0)->get_id());
            int limit = 0;
            while (possible_parent_ids.size() > 0 && limit < 8)
            {
                limit++;
                vector<unsigned int> new_possible_parent_ids;
                for (vector<unsigned int>::iterator it = possible_parent_ids.begin(); it != possible_parent_ids.end(); it++)
                {
                    if (id != *it)
                    {
                        possible_parents.push_back((get_joint(*it)));
                        vector<unsigned int> children_ids = get_joint(*it)->get_children();
                        for (vector<unsigned int>::iterator jt = children_ids.begin(); jt != children_ids.end(); jt++)
                        {
                            possible_parents.push_back(get_joint(*jt));
                            new_possible_parent_ids.push_back(*jt);
                        }
                    }

                }
                possible_parent_ids = new_possible_parent_ids;
                new_possible_parent_ids.clear();
            }
        }
        return possible_parents;
    }


    void Skeleton::set_model_file(const string& file)
    {
        if (_model.LoadFromOFF(file))
        {
            _model.UpdateVertexBufferObjects();
            _model_file = file;
            //emit data_changed(get_id());
        }
        else
        {
            _model.LoadFromOFF(_model_file);
            _model.UpdateVertexBufferObjects();
        }
    }

    string Skeleton::next_joint_name() const
    {
        stringstream ss;
        ss << "Joint " << (_joints.size() + 1);
        string name = ss.str();
        name = append_sequence_number(name);
        return name;
    }

    bool Skeleton::is_joint_name_reserved(const string& name) const
    {
        for (std::vector<Joint*>::const_iterator it = _joints.begin(); it != _joints.end(); it++)
        {
            if (((Joint*)*it)->get_name() == name)
            {
                return true;
            }
        }
        return false;
    }

    string Skeleton::append_sequence_number(const string& name) const
    {
        unsigned int nr = 2;
        string new_name = name;
        while(is_joint_name_reserved(new_name))
        {
            stringstream ss;
            ss << name << "_" << nr++;
            new_name = ss.str();
        }
        return new_name;
    }

    void Skeleton::remove_joint(unsigned int joint_id)
    {

    }

    void Skeleton::update_joint_coordinates_(unsigned int joint_id, const DCoordinate3& parent_coordinates)
    {
        get_joint(joint_id)->update_coordinates(parent_coordinates);
        vector<unsigned int> children_ids = get_joint(joint_id)->get_children();
        const DCoordinate3& joint_coordinates = get_joint(joint_id)->get_coordinates();
        for(vector<unsigned int>::iterator it = children_ids.begin(); it != children_ids.end(); it++)
        {
            update_joint_coordinates_(*it, joint_coordinates);
        }

        get_joint(0)->get_parent();
    }


    void Skeleton::update_joint_coordinates()
    {
        if (_coordinates_need_update)
        {
            update_joint_coordinates_(0, DCoordinate3());
            _coordinates_need_update = false;
        }
    }

    bool Skeleton::validate_joint_index_(int joint_id) const
    {
        if (joint_id < 0)
        {
            return false;
        }
        if ((unsigned int) joint_id >= _joints.size())
        {
            return false;
        }
        return true;
    }

    void Skeleton::render(RenderingOptions* rendering_options, bool glLoad)
    {
        update_joint_coordinates();

        render_joints(rendering_options, glLoad);

        render_links(rendering_options);

        render_axis(rendering_options);

        //    if (_chains_moved)
        //    {
        //        MatFBRuby.Apply();
        //        RenderChains();
        //    }

        if (rendering_options->get_render_model() && !_model_file.empty())
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glDepthMask(GL_FALSE);
            rendering_options->get_material(rendering_options->get_model_material())->Apply();
            glPushMatrix();
            glTranslated(_model_offset.x(), _model_offset.y(), _model_offset.z());
            glScaled(_model_scale.x(), _model_scale.y(), _model_scale.z());
            _model.Render();
            glPopMatrix();
            glDepthMask(GL_TRUE);
            glDisable(GL_BLEND);
        }
    }

    void Skeleton::render_joints(RenderingOptions* rendering_options, bool glLoad) const
    {
        const TriangulatedMesh3* joint_model = rendering_options->get_joint_model();

        if (rendering_options->get_render_joints() && joint_model)
        {
            rendering_options->get_material(rendering_options->get_joint_material())->Apply();

            for(vector<Joint*>::const_iterator it = _joints.begin(); it != _joints.end(); it++)
            {
                const DCoordinate3& position = (*it)->get_coordinates();
                const DCoordinate3& _scale = (*it)->get_scale();
                glPointSize(1.0);
                glPushMatrix();
                glTranslated(position.x(), position.y(), position.z());
                glScalef(_scale.x() / 10, _scale.y() / 10, _scale.z() / 10);
                if (glLoad)
                {
                    glLoadName((*it)->get_id() + 6);
                }
                joint_model->Render();
                glPopMatrix();
            }
        }
    }

    void Skeleton::render_chains(RenderingOptions* rendering_options, bool glLoad) const
    {
        const TriangulatedMesh3* link_model = rendering_options->get_link_model();
        for(vector<Chain>::const_iterator it = _chains.begin(); it != _chains.end(); it++)
        {
            for (int i = 1; i < (*it).get_chain_size(); i++)
            {
                    DCoordinate3 start =  (*it).get_joint_coordinates(i - 1);
                    DCoordinate3 end = (*it).get_joint_coordinates(i);
                    DCoordinate3 k_prime = end - start;

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

                    matrix[12] = start[0];
                    matrix[13] = start[1];
                    matrix[14] = start[2];
                    matrix[15] = 1.0;

                    glPushMatrix();
                        glMultMatrixf(matrix);
                        glScalef(0.1, 0.1, length);
                        link_model->Render();
                    glPopMatrix();
                }
        }

    }

    void Skeleton::render_axis(RenderingOptions* rendering_options, bool glLoad) const
    {
        if (is_joint_selected())
        {
            int joint_id = get_selected_joint_id();
            if (rendering_options->get_render_axis())
            {
                DCoordinate3 axis = get_joint(joint_id)->get_axis();
                if (axis.length() > 0)
                {
                    DCoordinate3 parent_position = get_joint(get_joint(joint_id)->get_parent())->get_coordinates();
                    DCoordinate3 p1 = parent_position + 1000 * axis;
                    DCoordinate3 p2 = parent_position - 1000 * axis;

                    glDisable(GL_LIGHTING);
                    glLineWidth(2.5);
                    glColor3f(1.0, 0.0, 0.0);
                    glBegin(GL_LINES);
                        glVertex3f(p1.x(), p1.y(), p1.z());
                        glVertex3f(p2.x(), p2.y(), p2.z());
                    glEnd();
                    glEnable(GL_LIGHTING);
                }
            }
        }

//        glPushMatrix();
//        glColor3f(1.0, 1.0, 0.0);
//        glDisable(GL_LIGHTING);

//        glBegin(GL_TRIANGLE_FAN);
//        glVertex3f(0.0, 0.0, 0.0);
//        float radius = 2;

//        for (float angle=1.0f;angle<361.0f;angle+=0.2)
//        {
//            float x2 = sin(angle)*radius;
//            float y2 = cos(angle)*radius;
//            glVertex3f(x2, y2, 0.0);
//        }

//        glEnd();

//        glEnable(GL_LIGHTING);
//        glPopMatrix();
    }

    void Skeleton::render_links(RenderingOptions* rendering_options, bool glLoad) const
    {
        const TriangulatedMesh3* link_model = rendering_options->get_link_model();

        if (rendering_options->get_render_links() && link_model &&_joints.size() > 1)
        {
            rendering_options->get_material(rendering_options->get_link_material())->Apply();

            for(vector<Joint*>::const_iterator it = ++_joints.begin(); it != _joints.end(); it++)
            {
                DCoordinate3 start = get_joint(((Joint*)*it)->get_parent())->get_coordinates();
                DCoordinate3 end = ((Joint*)*it)->get_coordinates();
                DCoordinate3 k_prime = end - start;

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

                matrix[12] = start[0];
                matrix[13] = start[1];
                matrix[14] = start[2];
                matrix[15] = 1.0;

                glPushMatrix();
                    glMultMatrixf(matrix);
                    glScalef(0.1, 0.1, length);
                    link_model->Render();
                glPopMatrix();
            }
        }
    }

    // implementation of public slots
    void Skeleton::handle_view_joint_added(const string& name, int parent_id)
    {
        Joint* joint = new Joint(_joints.size(), name, parent_id);
        _joints.push_back(joint);
        if (parent_id >= 0)
        {
            get_joint(parent_id)->add_child(joint->get_id());
            emit model_joint_list_changed();

            _selected_joint = joint->get_id();
            emit model_joint_selection_changed();
            emit model_joint_selection_changed(joint->get_name());
        }
    }

    void Skeleton::handle_view_joint_selection_changed(int joint_id)
    {
        if ((unsigned int) joint_id > _joints.size())
        {
            _selected_joint = -1;
        }
        else
        {
            _selected_joint = joint_id;
        }
        emit model_joint_selection_changed();
    }

    void Skeleton::handle_view_joint_selection_changed(const string& jointName)
    {
        _selected_joint = getJointIdByName(jointName);
        emit model_joint_selection_changed(jointName);
    }

    void Skeleton::handle_view_joint_renamed(const string& oldName, const string& newName)
    {
        Joint* joint = get_joint(getJointIdByName(oldName));
        if (joint)
        {
            joint->set_name(newName);
            emit model_joint_renamed(oldName, newName);
        }
    }

    void Skeleton::handle_view_joint_deleted(const string& jointName)
    {
        unsigned int offset = 0;
        unsigned int jointId = getJointIdByName(jointName);

        cout << "initial: " << endl;
        for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++)
        {
            Joint* j = *it;
            cout << "id: " << j->get_id() << ", name: " << j->get_name() << ", parent: " << j->get_parent() << ", children: ";
            for (unsigned int i = 0; i < j->get_children().size(); i++)
            {
                cout << j->get_children()[i] << " ";
            }
            cout  << endl;
        }

        cout << endl;
        deleteJoint(jointId);

        cout << "final: " << endl;
        for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++)
        {
            Joint* j = *it;
            cout << "id: " << j->get_id() << ", name: " << j->get_name() << ", parent: " << j->get_parent() << ", children: ";
            for (unsigned int i = 0; i < j->get_children().size(); i++)
            {
                cout << j->get_children()[i] << " ";
            }
            cout  << endl;
        }


        emit model_joint_deleted(jointName);
    }

    void Skeleton::handle_view_joint_coordinates_changed_(unsigned int jointId)
    {
        vector<unsigned int> children = get_joint(jointId)->get_children();
        for (unsigned int i = 0; i < children.size(); i++)
        {
            emit (model_joint_data_changed(get_joint(children[i])->get_name()));
            handle_view_joint_coordinates_changed_(children[i]);
        }
    }

    void Skeleton::handle_view_joint_coordinates_changed(const string& name, const DCoordinate3& coordinates)
    {
        Joint* joint = get_joint(getJointIdByName(name));
        if (joint)
        {
            joint->set_coordinate(coordinates);
            emit (model_joint_data_changed(name));

            handle_view_joint_coordinates_changed_(joint->get_id());
        }
    }

    void Skeleton::handle_view_joint_rotation_axis_changed(const string&, const DCoordinate3& rotation_axis)
    {

    }

    void Skeleton::handle_view_joint_rotation_constraint_changed(const string&, const DCoordinate3& rotation_constraint)
    {

    }

    void Skeleton::handle_view_joint_scale_changed(const string& name, const DCoordinate3& scale)
    {
        Joint* joint = get_joint(getJointIdByName(name));
        if (joint)
        {
            joint->set_scale(scale);
            emit (model_joint_data_changed(name));
        }
    }

    void Skeleton::handle_view_joint_parent_changed(int parent_id)
    {
        //_joints[_joints[_selected_joint].get_parent()].remove_child(_selected_joint);
        //_joints[_selected_joint].set_parent(parent_id);
        //_joints[parent_id].add_child(_selected_joint);
        _coordinates_need_update = true;
        //emit model_joint_data_changed();
    }

    void Skeleton::handle_view_joint_type_changed(int type)
    {
        //_joints[_selected_joint].set_type((Type) type);
        _coordinates_need_update = true;
        //emit model_joint_data_changed();
    }

    void Skeleton::handle_view_joint_orientation_changed(const DCoordinate3& orientation)
    {
        //_joints[_selected_joint].set_orientation(orientation);
        _coordinates_need_update = true;
        //emit model_joint_data_changed();
    }

    void Skeleton::handle_view_joint_axis_changed(const DCoordinate3& axis)
    {
        /*
        Joint* joint = get_joint(getJointIdByName(name));
        if (joint)
        {
            joint->set_axis(axis);
            cout << "model data changed " << name << endl;
            emit (model_joint_data_changed(name));
        }
        */
    }

    void Skeleton::handle_view_joint_configuration_changed(const DCoordinate3& configuration)
    {
        //_joints[_selected_joint].set_configuration(configuration);
        _coordinates_need_update = true;
        //emit model_joint_data_changed();
    }

    void Skeleton::handle_view_joint_absolute_position_changed(const DCoordinate3& coordinates)
    {
        //_joints[_selected_joint].set_orientation(coordinates - _joints[_joints[_selected_joint].get_parent()].get_coordinates());
        _coordinates_need_update = true;
        //emit model_joint_data_changed();
    }

    void Skeleton::handle_view_joint_fabrik_moved(const DCoordinate3& target)
    {
        MoveSelected(target.x(), target.y(), target.z());
    }
}



//using namespace cagd;
//using namespace std;

//Skeleton::Skeleton(unsigned int id, double x, double y, double z, TriangulatedMesh3 mesh, TriangulatedMesh3 *link_mesh, TriangulatedMesh3 *joint_mesh, bool render_mesh, bool render_links, bool render_joints) : BaseEntity(id)
//{
//    _selected = -1;
//    _chains_moved = false;

//    _mesh = mesh;
//    _link_mesh = link_mesh;
//    _joint_mesh = joint_mesh;

//    _render_mesh = render_mesh;
//    _render_links = render_links;
//    _render_joints = render_joints;

//    _joints.push_back(Joint(0, new DCoordinate3(x, y, z), _joint_mesh, -1));
//}

//bool Skeleton::GetRenderMesh()
//{
//    return _render_mesh;
//}

//void Skeleton::SetRenderMesh(bool value)
//{
//    _render_mesh = value;
//}

//bool Skeleton::GetRenderLinks()
//{
//    return _render_links;
//}

//void Skeleton::SetRenderLinks(bool value)
//{
//    _render_links = value;
//}

//bool Skeleton::GetRenderJoints()
//{
//    return _render_joints;
//}

//void Skeleton::SetRenderJoints(bool value)
//{
//    _render_joints = value;
//}

//bool Skeleton::AddLink(unsigned int start_index, double x, double y, double z)
//{
//    bool inserted = false;
//    if (start_index < _joints.size())
//    {
//        int end_index = _joints.size();
//        int link_index = _links.size();
//        _joints.push_back(Joint(end_index, new DCoordinate3(x, y, z), _joint_mesh, link_index));
//        _links.push_back(Link(link_index, start_index, end_index, _link_mesh));
//        _joints[end_index].SetPreviousLink(link_index);
//        _joints[start_index].AddNextLink(link_index);
//        inserted = true;
//    }

//    return inserted;
//}

//void Skeleton::RenderLinks() const
//{
//    for(std::vector<Link>::const_iterator it = _links.begin(); it != _links.end(); ++it)
//    {
//        DCoordinate3 *s = (_joints[it->StartIndex()]).Position();
//        DCoordinate3 *e = (_joints[it->EndIndex()]).Position();
//        it->Render(s, e);
//    }
//}

//void Skeleton::RenderJoints(bool glLoad, int offset) const
//{
//    for(std::vector<Joint>::const_iterator it = _joints.begin(); it != _joints.end(); ++it)
//    {
//        if (it - _joints.begin() != _selected)
//        {
//            if (glLoad)
//            {
//                glLoadName(offset + it - _joints.begin());
//            }

//            it->Render();
//        }
//    }

//    if (_selected >= 0)
//    {
//        MatFBBrass.Apply();
//        if (glLoad)
//        {
//            glLoadName(offset + _selected);
//        }
//        _joints[_selected].Render();
//    }
//}

//void Skeleton::RenderChains() const
//{
//    for (std::vector<Chain>::const_iterator chain_it = _chains.begin(); chain_it != _chains.end(); chain_it++)
//    {
//        for(std::vector<Joint>::const_iterator it = chain_it->_joints.begin(); it != chain_it->_joints.end(); ++it)
//        {
//            it->Render();
//        }
//        Link link = Link(-1, 0, 0, _link_mesh);
//        for(std::vector<Joint>::const_iterator it = ++chain_it->_joints.begin(); it != chain_it->_joints.end(); ++it)
//        {
//            if (chain_it->_forward)
//            {
//                link.Render((it - 1)->_position, it->_position);
//            }
//            else
//            {
//                link.Render(it->_position, (it - 1)->_position);
//            }
//        }
//    }
//}

//bool Skeleton::Link::Render(DCoordinate3 *start, DCoordinate3 *end) const
//{
//    if (start && end)
//    {
//        DCoordinate3 k_prime = *end - *start;

//        float length = k_prime.length();

//        k_prime /= length;

//        DCoordinate3 j_prime;

//        while (j_prime.length() < EPS)
//        {
//            j_prime =  k_prime;
//            j_prime ^= DCoordinate3((double)rand() / (double)RAND_MAX , (double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX);
//        }

//        DCoordinate3 i_prime = j_prime;
//        i_prime ^= k_prime;

//        DCoordinate3 trans = *start;

//        float matrix[16];

//        k_prime.normalize();
//        j_prime.normalize();
//        i_prime.normalize();

//        matrix[0] = i_prime[0];
//        matrix[1] = i_prime[1];
//        matrix[2] = i_prime[2];
//        matrix[3] = 0.0;

//        matrix[4] = j_prime[0];
//        matrix[5] = j_prime[1];
//        matrix[6] = j_prime[2];
//        matrix[7] = 0.0;

//        matrix[ 8] = k_prime[0];
//        matrix[ 9] = k_prime[1];
//        matrix[10] = k_prime[2];
//        matrix[11] = 0.0;

//        matrix[12] = trans[0];
//        matrix[13] = trans[1];
//        matrix[14] = trans[2];
//        matrix[15] = 1.0;

//        glPushMatrix();
//            glMultMatrixf(matrix);
//            glScalef(_scale.x(), _scale.y(), length);
//            _mesh->Render();
//        glPopMatrix();

//        return true;
//    }
//    return false;
//}

//void Skeleton::Joint::Render() const
//{
//    glPushMatrix();
//        glTranslated(_position->x(), _position->y(), _position->z());
//        glScalef(0.1, 0.1, 0.1);
//        _mesh->Render();
//    glPopMatrix();
//}

//bool Skeleton::FirstPreviousBranch(int start_joint_id, int &previous_branch_joint_id, int &branch_link_index, int &chain_length) const
//{
//    const Joint *j = &_joints[start_joint_id];
//    bool branch = false;
//    int after_branch_joint_id;
//    chain_length = 0;

//    while (j->_prev_link >= 0 && !branch)
//    {
//        after_branch_joint_id = j->_id;
//        j = &_joints[_links[j->_prev_link]._start_index];
//        if (j->_next_links.size() > 1)
//        {
//            branch = true;
//            int i = 0;
//            while (i < j->_next_links.size() && _links[j->_next_links[i]]._end_index != after_branch_joint_id)
//            {
//                i++;
//            }
//            branch_link_index = i;
//        }
//        chain_length++;
//    }

//    previous_branch_joint_id = j->_id;

//    return j->_next_links.size() > 1 && j->_id != start_joint_id;
//}

//bool Skeleton::FirstNextBranch(int start_joint_id, int start_branch_link_index, int &next_branch_joint_id, int &chain_length) const
//{
//    if (start_branch_link_index >= _joints[start_joint_id]._next_links.size())
//    {
//        return false;
//    }

//    const Joint *j = &_joints[_links[_joints[start_joint_id]._next_links[start_branch_link_index]]._end_index];
//    chain_length = 1;
//    while (j->_next_links.size() == 1)
//    {
//        j = &_joints[_links[j->_next_links[0]]._end_index];
//        chain_length++;
//    }
//    next_branch_joint_id = j->_id;

//    return true;
//}

//void Skeleton::ForwardChain(unsigned int start_joint_id, unsigned int branch_link_index, unsigned int end_joint_id, Chain &chain) const
//{
//    const Joint *j = &_joints[start_joint_id];
//    chain._joints.push_back(*j);

//    j = &_joints[_links[j->_next_links[branch_link_index]]._end_index];

//    while (j->_next_links.size() > 0 && j->_id != end_joint_id)
//    {
//        chain._joints.push_back(*j);
//        j = &_joints[_links[j->_next_links[0]]._end_index];
//    }

//    chain._joints.push_back(*j);
//}

//void Skeleton::BackwardChain(unsigned int start_joint_id, unsigned int end_joint_id, Chain &chain) const
//{
//    const Joint *j = &_joints[start_joint_id];

//    while (j->_prev_link >= 0 && j->_id != end_joint_id)
//    {
//        chain._joints.push_back(*j);
//        j = &_joints[_links[j->_prev_link]._start_index];
//    }

//    chain._joints.push_back(*j);
//}

//unsigned int Skeleton::ConstructChains(int joint_index, int chain_index, int chain_parent_index, int branch_link_index)
//{
//    if (branch_link_index == -1)
//    {
//        int chain_number = 0;
//        for (int i = 0; i < _joints[joint_index]._next_links.size(); i++)
//        {
//            chain_number += ConstructChains(joint_index, chain_index + chain_number, chain_parent_index, i);
//        }

//        return chain_number;
//    }
//    else
//    {
//        int next_branch_joint_id, chain_length;
//        FirstNextBranch(joint_index, branch_link_index, next_branch_joint_id, chain_length);
//        Chain chain = Chain(chain_index, chain_parent_index, false);
//        BackwardChain(next_branch_joint_id, joint_index, chain);
//        _chains.push_back(chain);
//        ConstructChains(next_branch_joint_id, chain_index + 1, chain_index);

//        return 1;
//    }
//}

//void Skeleton::SetSelected(int selected_id)
//{
//    _chains_moved = false;
//    _chains.clear();
//    _selected = selected_id;

//    if (_selected >= 0)
//    {
//        Chain chain = Chain(0, -1, true);
//        int previous_branch_joint_id, branch_link_index, chain_length;
//        FirstPreviousBranch(_selected, previous_branch_joint_id, branch_link_index, chain_length);
//        ForwardChain(previous_branch_joint_id, branch_link_index, _selected, chain);
//        _chains.push_back(chain);

//        int chain_index = 1;

//        ConstructChains(_selected, chain_index, 0);
//    }
//}

//void Skeleton::MoveSelected(double x, double y, double z)
//{
//    _chains_moved = true;
//    DCoordinate3 target(x, y, z);
//    FABRIK(&_chains[0], target, 1e-10);
//    for (unsigned int i = 1; i < _chains.size(); i++)
//    {
//        SimpleForwardFABRIK(&_chains[i], _chains[_chains[i]._parent_id].GetChainEnding(), 1e-10);
//    }
//}

//void Skeleton::FABRIK(Chain *chain, DCoordinate3 target, double tolerance)
//{
//    double *lengths = new double[chain->_joints.size()];
//    double total_length = 0.0;
//    for (int i = 0; i < chain->_joints.size() - 1; i++)
//    {
//        lengths[i] = (*chain->_joints[i]._position - *chain->_joints[i + 1]._position).length();
//        total_length += lengths[i];
//    }
//    double distance = (target - *chain->_joints[chain->_joints.size() - 1]._position).length();
//    if (distance > total_length)
//    {
//        for (int i = 0; i < chain->_joints.size() - 1; i++)
//        {
//            double r = (target - *chain->_joints[i]._position).length();
//            double lambda = lengths[i] / r;
//            chain->_joints[i + 1]._position = new DCoordinate3((1 - lambda) * *chain->_joints[i]._position + lambda * target);
//        }
//    }
//    else
//    {
//        DCoordinate3 b = DCoordinate3(*chain->_joints[0]._position);
//        double dif_A = (target - *chain->_joints[chain->_joints.size() - 1]._position).length();
//        unsigned int iteration_count = 0, max_iteration = 10;
//        while (dif_A > tolerance && iteration_count < max_iteration)
//        {
//            iteration_count++;
//            chain->_joints[chain->_joints.size() - 1]._position = new DCoordinate3(target);
//            for (int i = chain->_joints.size() - 2; i >= 0; i--)
//            {
//                double r = (*chain->_joints[i + 1]._position - *chain->_joints[i]._position).length();
//                double lambda = lengths[i] / r;
//                chain->_joints[i]._position = new DCoordinate3((1 - lambda) * *chain->_joints[i + 1]._position + lambda * *chain->_joints[i]._position);
//            }
//            chain->_joints[0]._position = new DCoordinate3(b);
//            for (int i = 0; i < chain->_joints.size() - 1; i++)
//            {
//                double r = (*chain->_joints[i + 1]._position - *chain->_joints[i]._position).length();
//                double lambda = lengths[i] / r;
//                chain->_joints[i + 1]._position = new DCoordinate3((1 - lambda) * *chain->_joints[i]._position + lambda * *chain->_joints[i + 1]._position);
//            }
//            dif_A = (target - *chain->_joints[chain->_joints.size() - 1]._position).length();
//        }
//    }
//}

//void Skeleton::SimpleForwardFABRIK(Chain *chain, DCoordinate3 target, double tolerance)
//{
//    double *lengths = new double[chain->_joints.size()];
//    for (int i = 0; i < chain->_joints.size() - 1; i++)
//    {
//        lengths[i] = (*chain->_joints[i]._position - *chain->_joints[i + 1]._position).length();
//    }

//    chain->_joints[chain->_joints.size() - 1]._position = new DCoordinate3(target);
//    for (int i = chain->_joints.size() - 2; i >= 0; i--)
//    {
//        double r = (*chain->_joints[i + 1]._position - *chain->_joints[i]._position).length();
//        double lambda = lengths[i] / r;
//        chain->_joints[i]._position = new DCoordinate3((1 - lambda) * *chain->_joints[i + 1]._position + lambda * *chain->_joints[i]._position);
//    }

//    DCoordinate3 offset = chain->GetChainStart() - target;
//    for (int i = 0; i < chain->_joints.size(); i++)
//    {
//        chain->_joints[i]._position = new DCoordinate3(*chain->_joints[i]._position - offset);
//    }
//}

//void Skeleton::FinalizeMove()
//{
//    for (std::vector<Chain>::const_iterator chain_it = _chains.begin(); chain_it != _chains.end(); chain_it++)
//    {
//        if (chain_it->_forward)
//        {
//            for(std::vector<Joint>::const_iterator it = ++chain_it->_joints.begin(); it != chain_it->_joints.end(); ++it)
//            {
//                _joints[it->_id]._position = it->_position;
//            }
//        }
//        else
//        {
//            for(std::vector<Joint>::const_iterator it = --chain_it->_joints.end(); it >= chain_it->_joints.begin(); --it)
//            {
//                _joints[it->_id]._position = it->_position;
//            }
//        }
//    }
//    SetSelected(_selected);
//}

//DCoordinate3* Skeleton::GetSelectedPosition() const
//{
//    if (_selected >= 0)
//    {
//        if (!_chains_moved)
//        {
//            return (_joints[_selected]._position);
//        }
//        else
//        {
//            return _chains[0]._joints[_chains[0]._joints.size() - 1]._position;
//        }
//    }
//    return 0;
//}

//unsigned int Skeleton::JointCount() const
//{
//    return _joints.size();
//}

