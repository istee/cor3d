#pragma once

#include <string>
#include <vector>

#include "BaseEntity.h"
#include "Core/DCoordinates3.h"

using namespace std;
using namespace cagd;

namespace cor3d{
    class Posture: public BaseEntity {
        vector<DCoordinate3> _jointAbsolutePostureCoordinates;
    public:
        Posture(unsigned int id, string name);
    };
}
