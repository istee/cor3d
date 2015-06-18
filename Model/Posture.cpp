#include "Posture.h"

namespace cor3d
{
    Posture::Posture(unsigned int id, string name, BaseEntityCollection& joints): QObject(), BaseEntity(id, name), _joints(joints)
    {
        _isEdited = false;
        _postureAlgorithmType = FABRIK;
        _lastSelectedJoint = -1;
        for (unsigned int i = 0; i < joints.entityCount(); i++)
        {
            Joint* joint = static_cast<Joint*>(_joints[i]);
            _jointAbsolutePostureCoordinates.push_back(joint->get_coordinates());
            _jointAbsoluteInitialPostureCoordinates.push_back(joint->get_coordinates());
        }

        _algorithm = new Ccd(_joints, _jointAbsoluteInitialPostureCoordinates, _jointAbsolutePostureCoordinates);
    }

    ostream& operator <<(ostream& lhs, const Posture& rhs)
    {
        lhs << "posture_name:" << endl << rhs.getName() << endl;
        lhs << "posture_id: " << rhs.getId() << endl;
        lhs << "joint_count " << rhs._jointAbsolutePostureCoordinates.size() << endl;
        for (unsigned int i = 0; i < rhs._jointAbsolutePostureCoordinates.size(); i++)
        {
            lhs << rhs._jointAbsoluteInitialPostureCoordinates[i] << " ";
        }
        lhs << endl;
        return lhs;
    }

    istream& operator >>(istream& lhs, Posture& rhs)
    {
        string text;
        char name[256];
        int number;
        DCoordinate3 coordinates;
        lhs >> text;
        lhs.getline(name, 256);
        lhs.getline(name, 256);
        rhs.setName(name);
        cout << "t: " << text << " " << name << endl;
        lhs >> text >> rhs._id;
        lhs >> text >> number;
        cout << "number " << number << endl;
        rhs._jointAbsolutePostureCoordinates.clear();
        rhs._jointAbsoluteInitialPostureCoordinates.clear();
        for (unsigned int i = 0; i < number; i++)
        {
            lhs >> coordinates;
            rhs._jointAbsoluteInitialPostureCoordinates.push_back(coordinates);
            rhs._jointAbsolutePostureCoordinates.push_back(coordinates);
        }
        cout << rhs << endl;
        return lhs;
    }

    unsigned int Posture::getAlgorithmType() const
    {
        return _postureAlgorithmType;
    }

    //getter functions
    bool Posture::isEdited() const
    {
        return _isEdited;
    }

    DCoordinate3& Posture::getTargetCoordinate()
    {
        if (_joints.getSelectedEntity() && _joints.getSelectedEntity()->getId() != _lastSelectedJoint)
        {
            _lastSelectedJoint = _joints.getSelectedEntity()->getId();
            _target = static_cast<Joint*>(_joints.getSelectedEntity())->get_coordinates();
        }
        return _target;
    }

    const DCoordinate3& Posture::getAbsolutePostureCoordinate(unsigned int jointId) const
    {
        return _jointAbsolutePostureCoordinates[jointId];
    }

    void Posture::MoveSelected(const DCoordinate3& target)
    {
        if (_joints.getSelectedEntity())
        {

            _target = target;
            _algorithm->moveToTarget(target);
            emit modelPostureDataChanged(this, "root");
        }
    }

    void Posture::renderPosture(RenderingOptions* renderingOptions, bool glLoad) const
    {
        renderPostureJoints(renderingOptions, glLoad);
        renderPostureLinks(renderingOptions, true);
        _algorithm->renderChains(renderingOptions, glLoad);
    }

    void Posture::renderPostureJoints(RenderingOptions* renderingOptions, bool glLoad) const
    {
        const TriangulatedMesh3* joint_model = renderingOptions->getJointMesh();

        if (renderingOptions->isRenderJoints() && joint_model)
        {
            renderingOptions->getMaterial(renderingOptions->getJointMaterial())->Apply();

            for(unsigned int i = 0; i < _jointAbsolutePostureCoordinates.size(); i++)
            {
                Joint* joint = (Joint*) _joints[i];
                DCoordinate3 absoluteCoordinate = _jointAbsolutePostureCoordinates[i];
                glPointSize(1.0);
                glPushMatrix();
                glTranslated(absoluteCoordinate.x(), absoluteCoordinate.y(), absoluteCoordinate.z());
                glScalef(joint->get_scale().x() / 10, joint->get_scale().y() / 10, joint->get_scale().z() / 10);
                if (glLoad)
                {
                    glLoadName(joint->getId() + 6);
                }
                joint_model->Render();
                glPopMatrix();
            }
        }
    }

    void Posture::renderPostureLinks(RenderingOptions* renderingOptions, bool glLoad) const
    {
        const TriangulatedMesh3* link_model = renderingOptions->getLinkMesh();

        if (renderingOptions->isRenderLinks() && link_model && _joints.entityCount() > 1)
        {
            renderingOptions->getMaterial(renderingOptions->getLinkMaterial())->Apply();

            for(unsigned int i = 1; i < _jointAbsoluteInitialPostureCoordinates.size(); i++)
            {
                Joint* joint = (Joint*) _joints[i];
                DCoordinate3 start = _jointAbsoluteInitialPostureCoordinates[joint->get_parent()];
                DCoordinate3 end = _jointAbsoluteInitialPostureCoordinates[joint->getId()];
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

                DCoordinate3 jointScale = getJointById(joint->get_parent())->get_scale();
                double scale = min(jointScale.x(), min(jointScale.y(), jointScale.z())) / 10.0;

                glPushMatrix();
                    glMultMatrixf(matrix);
                    glScalef(scale, scale, length);
                    link_model->Render();
                glPopMatrix();
            }
        }
    }

    Joint* Posture::getJointById(unsigned int index) const
    {
        return static_cast<Joint*>(_joints[index]);
    }

    void Posture::handleViewChangesAccepted()
    {
        _isEdited = false;
        emit modelPostureIsEdited(this, _isEdited);
        for (unsigned int i = 0; i < _jointAbsolutePostureCoordinates.size(); i++)
        {
            _jointAbsoluteInitialPostureCoordinates[i] = _jointAbsolutePostureCoordinates[i];
        }
        emit modelPostureDataChanged(this, _joints[0]->getName());
    }

    void Posture::handleViewChangesCanceled()
    {
        _isEdited = false;
        emit modelPostureIsEdited(this, _isEdited);
        for (unsigned int i = 0; i < _jointAbsolutePostureCoordinates.size(); i++)
        {
            _jointAbsolutePostureCoordinates[i] = _jointAbsoluteInitialPostureCoordinates[i];
        }
        emit modelPostureDataChanged(this, _joints[0]->getName());
    }

    void Posture::handleViewPostureAlgorithmTypeSelected(const string& algorithmName)
    {
        cout << "algorithm changed " << algorithmName << endl;
        if ("FABRIK" == algorithmName)// && FABRIK =! _postureAlgorithmType)
        {
            _postureAlgorithmType = FABRIK;
        }
        if ("RIGID" == algorithmName)// && RIGID =! _postureAlgorithmType)
        {
            _postureAlgorithmType = RIGID;
        }
    }
}
