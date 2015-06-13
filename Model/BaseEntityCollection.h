#pragma once

#include <vector>

#include "BaseEntity.h"

using namespace std;

namespace cor3d {
    class BaseEntityCollection {
    protected:
        string            _entityPrefix;
        vector<BaseEntity*>     _data;
        BaseEntity*             _selected;
    public:
        BaseEntityCollection(const string& entityPrefix);
        ~BaseEntityCollection();
        string nextAutoName() const;
        bool isNameReserved(const string& name) const;

        unsigned int entityCount() const;

        bool addEntity(BaseEntity* entity);
        bool deleteEntity(const string& entityName, bool& selectionChanged);
        bool selectEntity(const string& entityName);

        BaseEntity* getSelectedEntity() const;
        const vector<BaseEntity*> getData() const;
        BaseEntity* operator [](int id) const;
        BaseEntity* operator [](const string& name) const;
    private:
        string appendSequenceNumber(const string& name) const;
    };
}
