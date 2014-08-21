#pragma once

#include <string>
#include <vector>

#include "BaseEntity.h"

using namespace std;

namespace cor3d{
    class Posture: BaseEntity {
        vector<double> _joint_configuration;
    public:
        Posture(unsigned int id, string name, vector<double> joint_configuration): BaseEntity(id, name)
        {
            _joint_configuration = joint_configuration;
        }

        void set_joint_value(unsigned int id, double value)
        {
            _joint_configuration[id] = value;
        }
    };
}
