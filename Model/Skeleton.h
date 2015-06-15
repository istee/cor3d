#pragma once

#include <vector>
#include <string>

#include "Joint.h"
#include "Posture.h"
#include "Chain.h"
#include "BaseEntityCollection.h"

#include "../Core/DCoordinates3.h"
#include "../Core/TriangulatedMeshes3.h"

#include "GUI/RenderingOptions.h"

using namespace std;
using namespace cagd;

namespace cor3d
{
    //ostream& operator <<(ostream& lhs, const Skeleton& rhs);

    class Skeleton : public QObject, public BaseEntity
    {
        Q_OBJECT

        friend std::ostream& operator <<(std::ostream& lhs, const Skeleton& rhs);
        friend std::istream& operator >>(std::istream& lhs, Skeleton& rhs);

        string                  _meshFile;
        TriangulatedMesh3       _model;
        DCoordinate3            _meshOffset;
        DCoordinate3            _meshScale;

        BaseEntityCollection    _postures;
        BaseEntityCollection    _joints;

    public:
        Skeleton(unsigned int id, const string& name);


        void addRoot();

        void addJoint(const string& parentName, const string& jointName);
        void selectJoint(const string& jointName);

        void addPosture(const string& name);
        void deletePosture(const string& name);
        void renamePosture(const string& oldName, const string& newName);


        ///////////////////////////
        // getter methods        //
        ///////////////////////////
        string getMeshFile() const;
        DCoordinate3 getMeshOffset() const;
        DCoordinate3 getMeshScale() const;

        unsigned int getJointCount() const;
        string nextAutoJointName() const;
        vector<BaseEntity*> getJointList() const;
        vector<BaseEntity*> getPossibleParents(unsigned int id) const;
        Joint* getJointById(unsigned int id) const;
        Joint* getJointByName(const string& name) const;
        Joint* getSelectedJoint() const;

        unsigned int getPostureCount() const;
        string nextAutoPostureName() const;
        Posture* getPostureByName(const string& name) const;
        Posture* getPostureById(int id);
        Posture* getSelectedPosture() const;


        ///////////////////////////
        // setter methods        //
        ///////////////////////////
        void setMeshFile(const string& file_name);
        void setMeshOffset(const DCoordinate3& model_offset);
        void setMeshScale(const DCoordinate3& model_scale);

        void render(RenderingOptions* rendering_options, bool glLoad = false);
        void renderJoints(RenderingOptions* rendering_options, bool glLoad = false) const;
        void renderLinks(RenderingOptions* rendering_options, bool glLoad = false) const;
        void render_axis(RenderingOptions* rendering_options, bool glLoad = false) const;

    private:
        void deleteJoint(unsigned int jointId);
        void prepareDeleteJoints(unsigned int jointId, vector<unsigned int>& result);
        void mirrorJoint(Joint* joint, Joint* mirrorParent, const DCoordinate3&);

    public slots:

        void handleViewJointAdded(const string& name, const string& parentName);
        void handleViewJointDeleted(const string&);
        void handleViewJointRenamed(const string&, const string&);
        void handleViewJointSelected(const string&);
        void handleViewJointSelected(int);
        void handleViewJointMirrored(const string&);

        void handleViewJointAbsoluteCoordinatesChanged(const string& name, const DCoordinate3& absoluteCoordinates);
        void handleViewSelectedJointAbsoluteCoordinatesChanged(const DCoordinate3 absoluteCoordiantes);
        void handleViewJointRelativeCoordinatesChanged(const string& name, const DCoordinate3& relativeCoordinates);
        void handleViewJointScaleChanged(const string& name, const DCoordinate3& scale);

        void handleViewPostureAdded(const string&);
        void handleViewPostureDeleted(const string&);
        void handleViewPostureRenamed(const string&, const string&);
        void handleViewPostureSelected(const string&);

        void handleViewPostureJointAbsoluteCoordinatesChanged(const DCoordinate3 absoluteCoordinates);
        void handleViewPostureJointAbsoluteCoordinatesChanged(const string& jointName, const DCoordinate3 absoluteCoordinates);

        void handleViewSkeletonModelChanged(const string&);
        void handleViewSkeletonModelScaleChanged(const DCoordinate3&);
        void handleViewSkeletonModelOffsetChanged(const DCoordinate3&);

    signals:
        void modelSkeletonDataChanged(Skeleton* skeleton);

        void modelJointAdded(Skeleton* skeleton, Joint* joint, const string& parentName);
        void modelJointRenamed(const string& oldName, const string& newName);
        void modelJointDeleted(const string& name);
        void modelJointSelected(const string& name);
        void modelJointParentChanged(const string& name, const string& oldParentName, const string& newParentName);
        void modelJointDataChanged(Joint* joint);

        void modelPostureAdded(Skeleton* skeleton, Posture* posture);
        void modelPostureDeleted(Skeleton* skeleton, const string& postureName);
        void modelPostureRenamed(const string& oldPostureName, const string& newPostureName);
        void modelPostureSelected(Skeleton* skeleton, Posture* selectedPosture, Posture* previousPosture);
        void modelPostureDataChanged(Posture* posture);
    };
}

