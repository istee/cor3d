#include "Skeleton.h"

#include <sstream>

#include "Core/Materials.h"
#include "Model/Joint.h"

namespace cor3d {

    std::ostream& operator <<(std::ostream& lhs, const Skeleton& rhs)
    {
        lhs << "skeleton_name:" << endl << rhs.getName() << endl;
        bool hasModelFile = "" != rhs.getMeshFile();
        lhs << "skeleton_has_meshFile: " << hasModelFile << endl;
        if (hasModelFile)
        {
            lhs << "skeleton_meshFile: " << rhs.getMeshFile() << endl;
            lhs << "skeleton_meshOffset: " << rhs.getMeshOffset() << endl;
            lhs << "skeleton_meshScale: " <<rhs.getMeshScale() << endl;
        }
        lhs << "skeleton_joint_count: " << rhs.getJointCount() << endl;
        for (unsigned int i = 0; i < rhs._joints.entityCount(); i++)
        {
            lhs << *static_cast<Joint*>(rhs._joints[i]);
        }
        lhs << "skeleton_posture_count: " << rhs.getPostureCount() << endl;
        for (unsigned int i = 0; i < rhs._postures.entityCount(); i++)
        {
            lhs << *static_cast<Posture*>(rhs._postures[i]);
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
        cout << "joint number " << number << endl;
        for (int i = 0; i < number; i++)
        {
            Joint* joint = new Joint(i, "joint" + i, 0);
            lhs >> *joint;
            rhs._joints.addEntity(joint);
        }
        lhs >> text >> number;
        for (int i = 0; i < number; i++)
        {
            Posture* posture = new Posture(i, "posture" + i, rhs._joints);
            lhs >> *posture;
            rhs._postures.addEntity(posture);
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
        return _joints.entityCount();
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
        return static_cast<Posture*>(_postures.getSelectedEntity());
    }

    Skeleton::Skeleton(unsigned int id, const string& name): QObject(), BaseEntity(id, name), _joints("Joint"), _postures("Posture")
    {
        _meshScale = DCoordinate3(1.0, 1.0, 1.0);
        _meshOffset = DCoordinate3(0, 0, 0);
    }

    void Skeleton::addRoot()
    {
        if (_joints.entityCount() == 0)
        {
            _joints.addEntity(new Joint(0, "root", -1));
        }
    }

    void Skeleton::addJoint(const string& parentName, const string& jointName)
    {
        Joint* parent = static_cast<Joint*>(_joints[parentName]);
        if (parent)
        {
            Joint* joint = new Joint(_joints.entityCount(), jointName, parent->getId(), parent->get_coordinates());
            joint->set_coordinate(parent->get_coordinates());
            joint->set_scale(parent->get_scale());
            joint->set_axis(parent->get_axis());
            joint->set_orientation(parent->get_orientation());
            _joints.addEntity(joint);
            parent->add_child(joint->getId());
            emit modelJointAdded(this, joint, parentName);
        }
    }

    void Skeleton::selectJoint(const string& jointName)
    {
        if (_joints.selectEntity(jointName))
        {
            Joint* selectedJoint = static_cast<Joint*>(_joints.getSelectedEntity());
            emit modelJointSelected(selectedJoint->getName());
        }
    }

    Joint* Skeleton::getJointById(unsigned int id) const
    {
        return static_cast<Joint*>(_joints[id]);
    }

    Joint* Skeleton::getJointByName(const string& name) const
    {
        return static_cast<Joint*>(_joints[name]);
    }

    Joint* Skeleton::getSelectedJoint() const
    {
        return static_cast<Joint*>(_joints.getSelectedEntity());
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

        bool jointSelectionChanged = false;
        for (unsigned int i = 0; i < deleteJoints.size(); i++)
        {
            bool selectionChanged = false;
            BaseEntity* joint = _joints[deleteJoints[i]];
            _joints.deleteEntity(joint->getName(), selectionChanged);
            jointSelectionChanged = jointSelectionChanged || selectionChanged;
        }
    }

    void Skeleton::prepareDeleteJoints(unsigned int jointId, vector<unsigned int>& result)
    {
        Joint* joint = static_cast<Joint*>(_joints[jointId]);
        result.push_back(jointId);
        for (unsigned int i = 0; i < joint->get_children().size(); i++)
        {
            prepareDeleteJoints(joint->get_children()[i],  result);
        }
    }

    vector<BaseEntity*> Skeleton::getJointList() const
    {
        return _joints.getData();
    }

    vector<BaseEntity*> Skeleton::getPossibleParents(unsigned int id) const
    {

        return vector<BaseEntity*>();
        /*
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
        */
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
        return _joints.nextAutoName();
    }

    void Skeleton::render(RenderingOptions* rendering_options, bool glLoad)
    {
        renderJoints(rendering_options, glLoad);

        renderLinks(rendering_options);

        if (rendering_options->isRenderSkeletonMesh() && !_meshFile.empty())
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glDepthMask(GL_FALSE);
            rendering_options->getMaterial(rendering_options->getSkeletonMaterial())->Apply();
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
        const TriangulatedMesh3* joint_model = rendering_options->getJointMesh();

        if (rendering_options->isRenderJoints() && joint_model)
        {
            rendering_options->getMaterial(rendering_options->getJointMaterial())->Apply();
            for(unsigned int i = 0; i < _joints.entityCount(); i++)
            {
                Joint* joint = static_cast<Joint*>(_joints[i]);
                const DCoordinate3& position = joint->get_coordinates();
                const DCoordinate3& _scale = joint->get_scale();
                glPointSize(1.0);
                glPushMatrix();
                glTranslated(position.x(), position.y(), position.z());
                glScalef(_scale.x() / 10, _scale.y() / 10, _scale.z() / 10);
                if (glLoad)
                {
                    glLoadName(joint->getId() + 6);
                }
                joint_model->Render();
                glPopMatrix();
            }
        }
    }

    void Skeleton::render_axis(RenderingOptions* rendering_options, bool glLoad) const
    {

    }

    void Skeleton::renderLinks(RenderingOptions* rendering_options, bool glLoad) const
    {
        const TriangulatedMesh3* link_model = rendering_options->getLinkMesh();

        if (rendering_options->isRenderLinks() && link_model &&_joints.entityCount() > 1)
        {
            rendering_options->getMaterial(rendering_options->getLinkMaterial())->Apply();

            for(unsigned int i = 1; i < _joints.entityCount(); i++)
            {
                Joint* endJoint = static_cast<Joint*>(_joints[i]);
                Joint* startJoint = static_cast<Joint*>(_joints[endJoint->get_parent()]);
                DCoordinate3 start = startJoint->get_coordinates();
                DCoordinate3 end = endJoint->get_coordinates();
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

                DCoordinate3 jointScale = startJoint->get_scale();
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
            Joint* joint = new Joint(_joints.entityCount(), name, parentJoint->getId(), parentJoint->get_coordinates());
            _joints.addEntity(joint);
            parentJoint->add_child(joint->getId());
            emit modelJointAdded(this, joint, parentName);
/*
            cout << "select elott" << endl;
            handleViewJointSelected(name);
            //emit modelJointSelected(name);
            */
        }
    }

    void Skeleton::handleViewJointSelected(int jointId)
    {
        if (_joints.selectEntity(jointId))
        {
            emit modelJointSelected(_joints.getSelectedEntity()->getName());
        }
        else
        {
            emit modelJointSelected("");
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

        /*
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
        */

        cout << endl;
        deleteJoint(joint->getId());

        /*

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
        */

        emit modelJointDeleted(jointName);
    }

    void Skeleton::mirrorJoint(Joint* mirroredJoint, Joint* mirrorParent, const DCoordinate3& mirrorRootCoordinates)
    {
        unsigned int childCount = mirroredJoint->get_children().size();
        for (unsigned int i = 0; i < childCount; i++)
        {
            Joint* child = static_cast<Joint*>(_joints[mirroredJoint->get_children()[i]]);
            string mirrorName = child->getName() + "_Mirror";
            addJoint(mirrorParent->getName(), mirrorName);
            Joint* mirror = getJointByName(mirrorName);
            mirror->set_scale(child->get_scale());
            DCoordinate3 coordiantes = DCoordinate3(mirrorRootCoordinates);
            mirror->set_coordinate(coordiantes - child->get_coordinates());
            emit modelJointDataChanged(mirror);
            mirrorJoint(child, mirror, mirrorRootCoordinates);
        }
    }

    void Skeleton::handleViewJointMirrored(const string& jointName)
    {
        Joint* joint = getJointByName(jointName);
        if (joint)
        {
            mirrorJoint(joint, joint, joint->get_coordinates());
        }
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
        Posture* posture = new Posture(_postures.entityCount(), name, _joints);
        if (_postures.addEntity(posture))
        {
            emit modelPostureAdded(this, posture);

            //emit modelSkeletonSelected(skeleton, selected);
        }
        else
        {
            delete posture;
        }
    }

    void Skeleton::handleViewPostureDeleted(const string& name)
    {
        bool selectionChanged;
        if (_postures.deleteEntity(name, selectionChanged))
        {
            if (selectionChanged)
            {
                emit modelPostureSelected(this, static_cast<Posture*>(_postures.getSelectedEntity()), 0);
            }
            emit modelPostureDeleted(this, name);
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
        Posture* posture = new Posture(_postures.entityCount(), name, _joints);
        if (_postures.addEntity(posture))
        {
            emit modelPostureAdded(this, posture);
        }
    }

    void Skeleton::deletePosture(const string& name)
    {
        /*
        Posture* posture = getPostureByName(name);
        if (posture)
        {
            unsigned int postureId = posture->getId();
            delete _postures[postureId];
            _postures.erase(_postures.begin() + postureId);
            for (vector<Posture*>::iterator it = _postures.begin() + postureId; it != _postures.end(); it++)
            {
                ((BaseEntity*) *it)->decreaseId();
            }

            emit modelPostureDeleted(this, name);
        }
        */
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
        return _postures.nextAutoName();
    }

    void Skeleton::handleViewPostureSelected(const string& name)
    {
        Posture* oldSelection = (Posture*) _postures.getSelectedEntity();
        if (_postures.selectEntity(name))
        {
            emit modelPostureSelected(this, (Posture*) _postures.getSelectedEntity(), oldSelection);
        }
    }

    Posture* Skeleton::getPostureByName(const string& name) const
    {
        return static_cast<Posture*>(_postures[name]);
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
        return static_cast<Posture*>(_postures[id]);
    }

    unsigned int Skeleton::getPostureCount() const
    {
        return _postures.entityCount();
    }
}
