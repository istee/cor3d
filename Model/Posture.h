#pragma once

#include <string>
#include <vector>

#include "BaseEntity.h"
#include "Core/DCoordinates3.h"
#include "Model/Chain.h"
#include "Model/Joint.h"
#include "GUI/RenderingOptions.h"

using namespace std;
using namespace cagd;

namespace cor3d{
    class Posture: public QObject, public BaseEntity {
        Q_OBJECT

        vector<DCoordinate3>    _jointAbsolutePostureCoordinates;
        vector<Chain>           _chains;
        vector<Joint*>          _joints;

    public:
        Posture(unsigned int id, string name, vector<Joint*>& joints);
        void constructChains(unsigned int selectedJoint);
        void clearChains();
        void MoveSelected(double x, double y, double z);
        void FinalizeMove();
        void render_chains(RenderingOptions* rendering_options, bool glLoad = false) const;
        void renderPosture(RenderingOptions* renderingOptions, bool glLoad = false) const;
        void renderPostureJoints(RenderingOptions* renderingOptions, bool glLoad = false) const;
        void renderPostureLinks(RenderingOptions* renderingOptions, bool glLoad = false) const;
    private:
        void FABRIK(Chain& chain, DCoordinate3 target, double tolerance);
        void SimpleForwardFABRIK(Chain *chain, DCoordinate3 target, double tolerance);
        void forward_chain(Chain& chain, int joint_id);
        int construct_chains_(int joint_id, int chain_index, int parent_chain_index);
        Joint* get_joint(unsigned int) const;

    public slots:
        void handle_view_joint_fabrik_moved(const DCoordinate3&);
    };
}
