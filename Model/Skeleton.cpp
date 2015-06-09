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

        lhs >> text;
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
        return lhs;
    }

    Skeleton::Skeleton(): QObject(), BaseEntity()
    {
        _model_scale = DCoordinate3(1.0, 1.0, 1.0);
        _model_offset = DCoordinate3(0, 0, 0);
        _selectedJoint = -1;
        _selectedPosture = -1;
    }

    Skeleton::Skeleton(unsigned int id, const string& name): QObject(), BaseEntity(id, name)
    {
        _model_scale = DCoordinate3(1.0, 1.0, 1.0);
        _model_offset = DCoordinate3(0, 0, 0);
        _selectedJoint = -1;
        _selectedPosture = -1;
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
            Joint* joint = new Joint(_joints.size(), jointName, parentId, parent->get_coordinates());
            joint->set_coordinate(parent->get_coordinates());
            joint->set_axis(parent->get_axis());
            joint->set_orientation(parent->get_orientation());
            _joints.push_back(joint);
            parent->add_child(joint->get_id());
            emit modelJointAdded(this, joint, parentName);
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

    Joint* Skeleton::get_selectedJoint() const
    {
        if (_selectedJoint >= 0 && _selectedJoint < _joints.size())
        {
            return _joints[_selectedJoint];
        }

        return 0;
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

/*
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


    */

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
        render_joints(rendering_options, glLoad);

        render_links(rendering_options);

        render_axis(rendering_options);

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



    void Skeleton::render_axis(RenderingOptions* rendering_options, bool glLoad) const
    {
        if (is_joint_selected())
        {
            int joint_id = get_selectedJoint_id();
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

                DCoordinate3 jointScale = get_joint(((Joint*)*it)->get_parent())->get_scale();
                double scale = min(jointScale.x(), min(jointScale.y(), jointScale.z())) / 10.0;

                glPushMatrix();
                    glMultMatrixf(matrix);
                    glScalef(scale, scale, length);
                    link_model->Render();
                glPopMatrix();
            }
        }
    }

    // implementation of public slots

    void Skeleton::handleViewJointAdded(const string& name, const string& parentName)
    {
        Joint* parentJoint = get_joint(parentName);
        if (parentJoint)
        {
            Joint* joint = new Joint(_joints.size(), name, parentJoint->get_id(), parentJoint->get_coordinates());
            _joints.push_back(joint);
            parentJoint->add_child(joint->get_id());
            emit modelJointAdded(this, joint, parentName);

            _selectedJoint = joint->get_id();

            emit modelJointSelected(name);

            emit model_joint_selectionChanged();
        }
    }

    void Skeleton::handle_view_joint_selectionChanged(int joint_id)
    {
        if ((unsigned int) joint_id > _joints.size())
        {
            _selectedJoint = -1;
            emit modelJointSelected("");
        }
        else
        {
            _selectedJoint = joint_id;
            emit modelJointSelected(_joints[_selectedJoint]->get_name());
        }
    }

    void Skeleton::handleViewJointSelected(const string& jointName)
    {
        _selectedJoint = getJointIdByName(jointName);
        emit modelJointSelected(jointName);
    }

    void Skeleton::handleViewJointRenamed(const string& oldName, const string& newName)
    {
        Joint* joint = get_joint(getJointIdByName(oldName));
        if (joint)
        {
            joint->set_name(newName);
            emit modelJointRenamed(oldName, newName);
        }
    }

    void Skeleton::handleViewJointDeleted(const string& jointName)
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


        emit modelJointDeleted(jointName);
    }

    void Skeleton::handle_view_joint_CoordinatesChanged_(unsigned int jointId)
    {
        /*
        vector<unsigned int> children = get_joint(jointId)->get_children();
        for (unsigned int i = 0; i < children.size(); i++)
        {
            emit (model_joint_data_changed(get_joint(children[i])->get_name()));
            handle_view_joint_CoordinatesChanged_(children[i]);
        }
        */
    }

    void Skeleton::handleViewJointAbsoluteCoordinatesChanged(const string& name, const DCoordinate3& absoluteCoordinates)
    {
        Joint* joint = get_joint(getJointIdByName(name));
        Joint* parent = get_joint(joint->get_parent());
        if (joint)
        {
            joint->set_coordinate(absoluteCoordinates);
            joint->set_orientation(absoluteCoordinates - parent->get_coordinates());
            emit modelJointDataChanged(joint);

            handle_view_joint_CoordinatesChanged_(joint->get_id());
        }
    }

    void Skeleton::handleViewJointRelativeCoordinatesChanged(const string& name, const DCoordinate3& relativeCoordinates)
    {
        Joint* joint = get_joint(getJointIdByName(name));
        Joint* parent = get_joint(joint->get_parent());
        if (joint)
        {
            DCoordinate3 newAbsoluteCoordinates = relativeCoordinates;
            newAbsoluteCoordinates += parent->get_coordinates();
            joint->set_coordinate(newAbsoluteCoordinates);
            joint->set_orientation(relativeCoordinates);
            emit modelJointDataChanged(joint);

            handle_view_joint_CoordinatesChanged_(joint->get_id());
        }
    }

    void Skeleton::handle_view_joint_rotation_axis_changed(const string&, const DCoordinate3& rotation_axis)
    {

    }

    void Skeleton::handle_view_joint_rotation_constraint_changed(const string&, const DCoordinate3& rotation_constraint)
    {

    }

    void Skeleton::handleViewJointScaleChanged(const string& name, const DCoordinate3& scale)
    {
        Joint* joint = get_joint(getJointIdByName(name));
        if (joint)
        {
            joint->set_scale(scale);
            emit modelJointDataChanged(joint);
        }
    }

    void Skeleton::handle_view_joint_parent_changed(int parent_id)
    {
        //_joints[_joints[_selectedJoint].get_parent()].remove_child(_selectedJoint);
        //_joints[_selectedJoint].set_parent(parent_id);
        //_joints[parent_id].add_child(_selectedJoint);
        //emit model_joint_data_changed();
    }

    void Skeleton::handle_view_joint_type_changed(int type)
    {
        //_joints[_selectedJoint].set_type((Type) type);
        //emit model_joint_data_changed();
    }

    void Skeleton::handle_view_joint_orientation_changed(const DCoordinate3& orientation)
    {
        //_joints[_selectedJoint].set_orientation(orientation);
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
        //_joints[_selectedJoint].set_configuration(configuration);
        //emit model_joint_data_changed();
    }

    void Skeleton::handle_view_joint_absolute_position_changed(const DCoordinate3& coordinates)
    {
        _joints[_selectedJoint]->set_coordinate(coordinates);
        //emit model_joint_data_changed(_joints[_selectedJoint]->get_name());
    }



    void Skeleton::handleViewPostureAdded(const string& name)
    {
        addPosture(name);

        Posture* posture = getPostureByName(name);
        if (posture)
        {
            _selectedPosture = posture->get_id();
            emit modelPostureSelected(this, posture);
        }
    }

    void Skeleton::handleViewPostureDeleted(const string& name)
    {
        deletePosture(name);

        if (_postures.size() == _selectedPosture)
        {
            _selectedPosture--;
            Posture* posture = getPostureById(_selectedPosture);
            emit modelPostureSelected(this, posture);
        }
    }

    void Skeleton::handleViewPostureRenamed(const string& oldName, const string& newName)
    {
        renamePosture(oldName, newName);
    }

    void handleViewPostureSelected(const string&)
    {

    }

    void Skeleton::addPosture(const string& name)
    {
        Posture* posture = new Posture(_postures.size(), name, _joints);
        _postures.push_back(posture);

        emit modelPostureAdded(this, posture);
    }

    void Skeleton::deletePosture(const string& name)
    {
        Posture* posture = getPostureByName(name);
        if (posture)
        {
            unsigned int postureId = posture->get_id();
            delete _postures[postureId];
            _postures.erase(_postures.begin() + postureId);
            for (vector<Posture*>::iterator it = _postures.begin() + postureId; it != _postures.end(); it++)
            {
                ((BaseEntity*) *it)->decrease_id();
            }

            emit modelPostureDeleted(this, name);
        }
    }

    void Skeleton::renamePosture(const string& oldName, const string& newName)
    {
        cout << "renamePosture" << oldName << " " << newName << endl;
        Posture* posture = getPostureByName(oldName);
        posture->set_name(newName);

        emit modelPostureRenamed(oldName, newName);
    }

    string Skeleton::nextAutoPostureName() const
    {
        stringstream ss;
        ss << "Posture " << (_postures.size() + 1);
        string name = ss.str();
        name = append_sequence_number(name);
        return name;
    }

    void Skeleton::handleViewPostureSelected(const string& name)
    {
        Posture* posture = getPostureByName(name);
        if (posture)
        {
            _selectedPosture = posture->get_id();
            emit modelPostureSelected(this, posture);
        }
        else
        {
            emit modelPostureSelected(this, 0);
        }
    }

    Posture* Skeleton::getPostureByName(const string& name) const
    {
        int id = get_id_by_name<Posture>(name, _postures);
        if (id >= 0 && id < _postures.size())
        {
            return _postures[id];
        }

        return 0;
    }

    void Skeleton::handleViewSkeletonModelChanged(const string& fileName)
    {
        set_model_file(fileName);
        emit modelSkeletonDataChanged(this);
    }

    void Skeleton::handleViewSkeletonModelScaleChanged(const DCoordinate3& scale)
    {
        set_model_scale(scale);
        emit modelSkeletonDataChanged(this);
    }

    void Skeleton::handleViewSkeletonModelOffsetChanged(const DCoordinate3& offset)
    {
        set_model_offset(offset);
        emit modelSkeletonDataChanged(this);
    }

    Posture* Skeleton::getPostureById(int id)
    {
        if (id >= 0 && id < _postures.size())
        {
            return _postures[id];
        }

        return 0;
    }

    unsigned int Skeleton::postureCount() const
    {
        return _postures.size();
    }
}
