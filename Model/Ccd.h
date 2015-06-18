#pragma once

#include "Algorithm.h"

namespace cor3d {
    class Ccd : public Algorithm
    {
    public:
        Ccd(BaseEntityCollection& joints, vector<DCoordinate3>& initialJointAbsoulteCoordinates, vector<DCoordinate3>& currentJointAbsoulteCoordinates);
    protected:
        virtual bool specificMoveToTarget(const DCoordinate3 target);
        void ccdAlgorithm(Chain& chain, DCoordinate3 target, double tolerance);
    };
}
