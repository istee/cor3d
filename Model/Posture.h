#pragma once

#include <string>
#include <vector>

#include "Algorithm.h"
#include "BaseEntity.h"
#include "Core/DCoordinates3.h"
#include "Model/Chain.h"
#include "Model/Joint.h"
#include "GUI/RenderingOptions.h"
#include "BaseEntityCollection.h"
#include "Fabrik.h"
#include "Ccd.h"

using namespace std;
using namespace cagd;

namespace cor3d{
    enum PostureAlgorithmType { FABRIK, RIGID };

    class Posture: public QObject, public BaseEntity {
        friend ostream& operator <<(ostream& lhs, const Posture& rhs);
        friend istream& operator >>(istream& lhs, Posture& rhs);

        Q_OBJECT

        vector<DCoordinate3>    _jointAbsolutePostureCoordinates;
        vector<DCoordinate3>    _jointAbsoluteInitialPostureCoordinates;
        vector<Chain>           _chains;
        BaseEntityCollection&   _joints;
        PostureAlgorithmType    _postureAlgorithmType;

        bool                    _isEdited;

        Algorithm*              _algorithm;

        DCoordinate3            _target;
        int                     _lastSelectedJoint;

    public:
        //getter functions
        unsigned int getAlgorithmType() const;
        const DCoordinate3& getAbsolutePostureCoordinate(unsigned int jointId) const;
        DCoordinate3& getTargetCoordinate();
        Posture(unsigned int id, string name, BaseEntityCollection& joints);
        void MoveSelected(const DCoordinate3& target);
        bool isEdited() const;
        void renderPosture(RenderingOptions* renderingOptions, bool glLoad = false) const;
        void renderPostureJoints(RenderingOptions* renderingOptions, bool glLoad = false) const;
        void renderPostureLinks(RenderingOptions* renderingOptions, bool glLoad = false) const;

    signals:
        void modelPostureIsEdited(Posture*, bool);
        void modelPostureDataChanged(Posture*, const string& rootJointName);

    private:
        Joint* getJointById(unsigned int) const;

    public slots:
        void handleViewChangesAccepted();
        void handleViewChangesCanceled();
        void handleViewPostureAlgorithmTypeSelected(const string& algorithmName);
    };
}
