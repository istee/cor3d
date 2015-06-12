#include "Skeleton.h"

#include <sstream>

#include "Core/Materials.h"
#include "Model/Joint.h"

namespace cor3d {

    std::ostream& operator <<(std::ostream& lhs, const Skeleton& rhs)
    {
        lhs << "skeleton_name: " << rhs.getName() << endl;
        bool hasModelFile = "" != rhs.getMeshFile();
        lhs << "skeleton_has_meshFile: " << hasModelFile << endl;
        if (hasModelFile)
        {
            lhs << "skeleton_meshFile: " << rhs.getMeshFile() << endl;
            lhs << "skeleton_meshOffset: " << rhs.getMeshOffset() << endl;
            lhs << "skeleton_meshScale: " <<rhs.getMeshScale() << endl;
        }
        lhs << "skeleton_joint_count: " << rhs.getJointCount() << endl;
        for (vector<Joint*>::const_iterator it = rhs._joints.begin(); it != rhs._joints.end(); it++)
        {
            lhs << **it;
        }
        lhs << "skeleton_posture_count: " << rhs.getPostureCount() << endl;
        for (vector<Posture*>::const_iterator it = rhs._postures.begin(); it != rhs._postures.end(); it++)
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
        rhs.setName(string(name));
        lhs >> text >> boolean;
        if (boolean)
        {
            lhs >> text >> text;
            rhs.setMeshFile(text);
            lhs >> text >> rhs._meshOffset;
            lhs >> text >> rhs._meshScale;
        }
        lhs >> text >> number;
        for (int i = 0; i < number; i++)
        {
            Joint* joint = new Joint(i, "", 0);
            lhs >> *joint;
            rhs._joints.push_back(joint);
        }
        lhs >> text >> number;
        for (int i = 0; i < number; i++)
        {
            Posture* posture = new Posture(rhs._joints);
            lhs >> *posture;
            rhs._postures.push_back(posture);
        }
        return lhs;
    }

    string Skeleton::getMeshFile() const
    {
        return _meshFile;
    }
    DCoordinate3 Skeleton::getMeshOffset() const
    {
        return _meshOffset;
    }
    DCoordinate3 Skeleton::getMeshScale() const
    {
        return _meshScale;
    }
    unsigned int Skeleton::getJointCount() const
    {
        return _joints.size();
    }
    void Skeleton::setMeshOffset(const DCoordinate3& model_offset)
    {
        _meshOffset = model_offset;
        emit modelSkeletonDataChanged(this);
    }
    void Skeleton::setMeshScale(const DCoordinate3& model_scale)
    {
        _meshScale = model_scale;
        emit modelSkeletonDataChanged(this);
    }
    Posture* Skeleton::getSelectedPosture() const
    {
        if (_selectedPosture >=0 && _selectedPosture < _postures.size())
        {
            return _postures[_selectedPosture];
        }
        return 0;
    }

    Skeleton::Skeleton(): QObject(), BaseEntity()
    {
        _meshScale = DCoordinate3(1.0, 1.0, 1.0);
        _meshOffset = DCoordinate3(0, 0, 0);
        _selectedJoint = -1;
        _selectedPosture = -1;
    }

    Skeleton::Skeleton(unsigned int id, const string& name): QObject(), BaseEntity(id, name)
    {
        _meshScale = DCoordinate3(1.0, 1.0, 1.0);
        _meshOffset = DCoordinate3(0, 0, 0);
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

    void Skeleton::addJoint(const string& parentName, const string& jointName)
    {
        Joint* parent = getJointByName(parentName);
        if (parent)
        {
            Joint* joint = new Joint(_joints.size(), jointName, parent->getId(), parent->get_coordinates());
            joint->set_coordinate(parent->get_coordinates());
            joint->set_scale(parent->get_scale());
            joint->set_axis(parent->get_axis());
            joint->set_orientation(parent->get_orientation());
            _joints.push_back(joint);
            parent->add_child(joint->getId());
            emit modelJointAdded(this, joint, parentName);
        }
    }

    void Skeleton::selectJoint(const string& jointName)
    {
        Joint* joint = getJointByName(jointName);
        if (joint)
        {
            _selectedJoint = joint->getId();
            for (unsigned int i = 0; i < _postures.size(); i++)
            {
                getPostureById(i)->selectJoint(_selectedJoint);
            }
            emit modelJointSelected(jointName);
        }
    }

    Joint* Skeleton::getJointById(unsigned int id) const
    {
        return _joints[id];
    }

    Joint* Skeleton::getJointByName(const string& name) const
    {
        int jointId = getIdByName<Joint>(name, _joints);
        if (jointId >= 0 && jointId < _joints.size())
        {
            return _joints[jointId];
        }

        return 0;
    }

    Joint* Skeleton::getSelectedJoint() const
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

        Joint* parent = getJointById(getJointById(jointId)->get_parent());
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

                    Joint* parent = getJointById(j->get_parent());
                    parent->remove_child(j->getId() + 1);
                    parent->add_child(j->getId());
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

    vector<BaseEntity*> Skeleton::getJointList() const
    {
        vector<BaseEntity*> joint_list = vector<BaseEntity*>();
        for (std::vector<Joint*>::const_iterator it = _joints.begin(); it != _joints.end(); it++)
        {
            joint_list.push_back((BaseEntity*) *it);
        }

        return joint_list;
    }

    vector<BaseEntity*> Skeleton::getPossibleParents(unsigned int id) const
    {

        vector<BaseEntity*> possible_parents;
        if (_joints.size() > 0 && id != getJointById(0)->getId())
        {
            vector<unsigned int> possible_parent_ids;
            possible_parent_ids.push_back(getJointById(0)->getId());
            int limit = 0;
            while (possible_parent_ids.size() > 0 && limit < 8)
            {
                limit++;
                vector<unsigned int> new_possible_parent_ids;
                for (vector<unsigned int>::iterator it = possible_parent_ids.begin(); it != possible_parent_ids.end(); it++)
                {
                    if (id != *it)
                    {
                        possible_parents.push_back((getJointById(*it)));
                        vector<unsigned int> children_ids = getJointById(*it)->get_children();
                        for (vector<unsigned int>::iterator jt = children_ids.begin(); jt != children_ids.end(); jt++)
                        {
                            possible_parents.push_back(getJointById(*jt));
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


    void Skeleton::setMeshFile(const string& file)
    {
        if (_model.LoadFromOFF(file))
        {
            _model.UpdateVertexBufferObjects();
            _meshFile = file;
            //emit data_changed(getId());
        }
        else
        {
            _model.LoadFromOFF(_meshFile);
            _model.UpdateVertexBufferObjects();
        }
    }

    string Skeleton::nextAutoJointName() const
    {
        return nextName<Joint>("Joint ", _joints);
    }

    void Skeleton::render(RenderingOptions* rendering_options, bool glLoad)
    {
        renderJoints(rendering_options, glLoad);

        renderLinks(rendering_options);

        render_axis(rendering_options);

        if (rendering_options->get_render_model() && !_meshFile.empty())
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glDepthMask(GL_FALSE);
            rendering_options->get_material(rendering_options->get_model_material())->Apply();
            glPushMatrix();
            glTranslated(_meshOffset.x(), _meshOffset.y(), _meshOffset.z());
            glScaled(_meshScale.x(), _meshScale.y(), _meshScale.z());
            _model.Render();
            glPopMatrix();
            glDepthMask(GL_TRUE);
            glDisable(GL_BLEND);
        }
    }

    void Skeleton::renderJoints(RenderingOptions* rendering_options, bool glLoad) const
    {
        const TriangulatedMesh3* joint_model = rendering_options->get_joint_model();

        if (rendering_options->get_renderJoints() && joint_model)
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
                    glLoadName((*it)->getId() + 6);
                }
                joint_model->Render();
                glPopMatrix();
            }
        }
    }



    void Skeleton::render_axis(RenderingOptions* rendering_options, bool glLoad) const
    {
        if (getSelectedJoint())
        {
            int joint_id = getSelectedJoint()->getId();
            if (rendering_options->get_render_axis())
            {
                DCoordinate3 axis = getJointById(joint_id)->get_axis();
                if (axis.length() > 0)
                {
                    DCoordinate3 parent_position = getJointById(getJointById(joint_id)->get_parent())->get_coordinates();
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

    void Skeleton::renderLinks(RenderingOptions* rendering_options, bool glLoad) const
    {
        const TriangulatedMesh3* link_model = rendering_options->get_link_model();

        if (rendering_options->get_renderLinks() && link_model &&_joints.size() > 1)
        {
            rendering_options->get_material(rendering_options->get_link_material())->Apply();

            for(vector<Joint*>::const_iterator it = ++_joints.begin(); it != _joints.end(); it++)
            {
                DCoordinate3 start = getJointById(((Joint*)*it)->get_parent())->get_coordinates();
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

                DCoordinate3 jointScale = getJointById(((Joint*)*it)->get_parent())->get_scale();
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
        Joint* parentJoint = getJointByName(parentName);
        if (parentJoint)
        {
            Joint* joint = new Joint(_joints.size(), name, parentJoint->getId(), parentJoint->get_coordinates());
            _joints.push_back(joint);
            parentJoint->add_child(joint->getId());
            emit modelJointAdded(this, joint, parentName);

            _selectedJoint = joint->getId();

            emit modelJointSelected(name);
        }
    }

    void Skeleton::handleViewJointSelected(int joint_id)
    {
        if ((unsigned int) joint_id > _joints.size())
        {
            _selectedJoint = -1;
            emit modelJointSelected("");
        }
        else
        {
            _selectedJoint = joint_id;
            emit modelJointSelected(_joints[_selectedJoint]->getName());
        }
        for (unsigned int i = 0; i < _postures.size(); i++)
        {
            getPostureById(i)->selectJoint(joint_id);
        }
    }

    void Skeleton::handleViewJointSelected(const string& jointName)
    {
        selectJoint(jointName);
    }

    void Skeleton::handleViewJointRenamed(const string& oldName, const string& newName)
    {
        Joint* joint = getJointByName(oldName);
        if (joint)
        {
            joint->setName(newName);
            emit modelJointRenamed(oldName, newName);
        }
    }

    void Skeleton::handleViewJointDeleted(const string& jointName)
    {
        Joint* joint = getJointByName(jointName);

        cout << "initial: " << endl;
        for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++)
        {
            Joint* j = *it;
            cout << "id: " << j->getId() << ", name: " << j->getName() << ", parent: " << j->get_parent() << ", children: ";
            for (unsigned int i = 0; i < j->get_children().size(); i++)
            {
                cout << j->get_children()[i] << " ";
            }
            cout  << endl;
        }

        cout << endl;
        deleteJoint(joint->getId());

        cout << "final: " << endl;
        for (vector<Joint*>::iterator it = _joints.begin(); it != _joints.end(); it++)
        {
            Joint* j = *it;
            cout << "id: " << j->getId() << ", name: " << j->getName() << ", parent: " << j->get_parent() << ", children: ";
            for (unsigned int i = 0; i < j->get_children().size(); i++)
            {
                cout << j->get_children()[i] << " ";
            }
            cout  << endl;
        }


        emit modelJointDeleted(jointName);
    }

    void Skeleton::handleViewJointAbsoluteCoordinatesChanged(const string& name, const DCoordinate3& absoluteCoordinates)
    {
        Joint* joint = getJointByName(name);
        Joint* parent = getJointById(joint->get_parent());
        if (joint)
        {
            joint->set_coordinate(absoluteCoordinates);
            joint->set_orientation(absoluteCoordinates - parent->get_coordinates());
            emit modelJointDataChanged(joint);
        }
    }

    void Skeleton::handleViewSelectedJointAbsoluteCoordinatesChanged(const DCoordinate3 absoluteCoordiantes)
    {
        Joint* selected = getSelectedJoint();
        if (selected)
        {
            handleViewJointAbsoluteCoordinatesChanged(selected->getName(), absoluteCoordiantes);
        }
    }

    void Skeleton::handleViewJointRelativeCoordinatesChanged(const string& name, const DCoordinate3& relativeCoordinates)
    {
        Joint* joint = getJointByName(name);
        Joint* parent = getJointById(joint->get_parent());
        if (joint)
        {
            DCoordinate3 newAbsoluteCoordinates = relativeCoordinates;
            newAbsoluteCoordinates += parent->get_coordinates();
            joint->set_coordinate(newAbsoluteCoordinates);
            joint->set_orientation(relativeCoordinates);
            emit modelJointDataChanged(joint);
        }
    }

    void Skeleton::handleViewJointScaleChanged(const string& name, const DCoordinate3& scale)
    {
        Joint* joint = getJointByName(name);
        if (joint)
        {
            joint->set_scale(scale);
            emit modelJointDataChanged(joint);
        }
    }

    void Skeleton::handleViewPostureAdded(const string& name)
    {
        addPosture(name);
        Posture* previous = getSelectedPosture();
        Posture* posture = getPostureByName(name);
        if (posture)
        {
            _selectedPosture = posture->getId();
            emit modelPostureSelected(this, posture, previous);
        }
    }

    void Skeleton::handleViewPostureDeleted(const string& name)
    {
        deletePosture(name);

        if (_postures.size() == _selectedPosture)
        {
            _selectedPosture--;
            Posture* posture = getPostureById(_selectedPosture);
            emit modelPostureSelected(this, posture, 0);
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
        posture->selectJoint(_selectedJoint);
        _postures.push_back(posture);

        emit modelPostureAdded(this, posture);
    }

    void Skeleton::deletePosture(const string& name)
    {
        Posture* posture = getPostureByName(name);
        if (posture)
        {
            unsigned int postureId = posture->getId();
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
        posture->setName(newName);

        emit modelPostureRenamed(oldName, newName);
    }

    string Skeleton::nextAutoPostureName() const
    {
        return nextName<Posture>("Posture ", _postures);
    }

    void Skeleton::handleViewPostureSelected(const string& name)
    {
        Posture* previous = getSelectedPosture();
        Posture* posture = getPostureByName(name);
        if (posture)
        {
            _selectedPosture = posture->getId();
            emit modelPostureSelected(this, posture, previous);
        }
        else
        {
            emit modelPostureSelected(this, 0, previous);
        }
    }

    Posture* Skeleton::getPostureByName(const string& name) const
    {
        int id = getIdByName<Posture>(name, _postures);
        if (id >= 0 && id < _postures.size())
        {
            return _postures[id];
        }

        return 0;
    }

    void Skeleton::handleViewPostureJointAbsoluteCoordinatesChanged(const DCoordinate3 absoluteCoordinates)
    {
        Posture* posture = getSelectedPosture();
        if (posture)
        {
            posture->MoveSelected(absoluteCoordinates);
            emit modelPostureDataChanged(posture);
        }
    }

    void Skeleton::handleViewPostureJointAbsoluteCoordinatesChanged(const string& jointName, const DCoordinate3 absoluteCoordinates)
    {
        cout << "hello 2 " << endl;
        Posture* posture = getSelectedPosture();
        if (posture)
        {
            Joint* joint = getSelectedJoint();
            if (joint->getName() != jointName)
            {
                selectJoint(jointName);
            }

            cout << "move " << jointName << " " << absoluteCoordinates << endl;

            posture->MoveSelected(absoluteCoordinates);
            emit modelPostureDataChanged(posture);
        }
    }

    void Skeleton::handleViewSkeletonModelChanged(const string& fileName)
    {
        setMeshFile(fileName);
        emit modelSkeletonDataChanged(this);
    }

    void Skeleton::handleViewSkeletonModelScaleChanged(const DCoordinate3& scale)
    {
        setMeshScale(scale);
        emit modelSkeletonDataChanged(this);
    }

    void Skeleton::handleViewSkeletonModelOffsetChanged(const DCoordinate3& offset)
    {
        setMeshOffset(offset);
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

    unsigned int Skeleton::getPostureCount() const
    {
        return _postures.size();
    }
}
