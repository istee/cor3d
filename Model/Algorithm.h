#pragma once

#include "GUI/RenderingOptions.h"
#include "BaseEntityCollection.h"
#include "Joint.h"
#include "Chain.h"

namespace cor3d {
    class Algorithm
    {
        BaseEntityCollection&   _joints;
        vector<DCoordinate3>&   _initialJointAbsoluteCoordinates;
        vector<DCoordinate3>&   _currentJointAbsoluteCoordinates;
        bool                    _isActive;
        int                     _editRootJoint;
        int                     _currentRootJoint;
        int                     _lockedJoint;
        int                     _selectedJoint;

    public:
        Algorithm(BaseEntityCollection& joints, vector<DCoordinate3>& initialJointAbsoulteCoordinates, vector<DCoordinate3>& currentJointAbsoulteCoordinates);
        bool moveToTarget(const DCoordinate3 target);
        void renderChains(RenderingOptions* rendering_options, bool glLoad) const;
    protected:
        virtual bool specificMoveToTarget(const DCoordinate3 target) = 0;
        vector<Chain>           _chains;
        bool                    _loggingEnabled;
        bool                    _parallelProcessingEnabled;
    private:
        void clearChains();
        int _constructChains(int jointId, int chainIndex, int parentChainIndex);
        void constructChains(unsigned int selectedJoint);
        void forwardChain(Chain& chain, int joint_id);
        void finalizeMove();
    };

}

