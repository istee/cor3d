#pragma once

#include <vector>

#include "BaseEntity.h"

using namespace std;

template<class BaseEntitySubClass>
class BaseEntityCollection {
protected:
    vector<BaseEntitySubClass*>     _data;
    BaseEntitySubClass*             _selected;
public:
    BaseEntityCollection();
};
