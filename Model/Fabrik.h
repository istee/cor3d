#pragma once

#include "Algorithm.h"

namespace cor3d {
    class Fabrik : public Algorithm
    {
    public:
        Fabrik(BaseEntityCollection& joints, vector<DCoordinate3>& initialJointAbsoulteCoordinates, vector<DCoordinate3>& currentJointAbsoulteCoordinates);
    protected:
        virtual bool specificMoveToTarget(const DCoordinate3 target);
        void fabrik(Chain& chain, DCoordinate3 target, double tolerance);

        class FabrikChain{
            Chain*              _chain;
            DCoordinate3        _target;
            double              _tolerance;

        public:
            FabrikChain(Chain* chain, DCoordinate3 target, double tolerance);
            void simpleForwardFabrik();
        };

    private:
        void parallelProcessFabrik(double tolerance);
    };
}
