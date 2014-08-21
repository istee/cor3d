#pragma once

#include <string>

#include "BaseEntity.h"

using namespace std;

namespace cor3d
{
    class ISkeleton: public BaseEntity
    {
    public:
        ISkeleton(unsigned int id, string name): BaseEntity(id, name){}
        int set_model(string file);
        virtual ~ISkeleton() {}
    };
}
