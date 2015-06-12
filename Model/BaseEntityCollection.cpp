#include "BaseEntityCollection.h"

namespace cor3d {
    BaseEntityCollection::BaseEntityCollection(const string& entityPrefix):_entityPrefix(entityPrefix)
    {
        _selected = 0;
    }

    bool BaseEntityCollection::isNameReserved(const string& name) const
    {
        for (vector<BaseEntity*>::const_iterator it = _data.begin(); it != _data.end(); it++)
        {
            if ((*it)->getName() == name)
            {
                return true;
            }
        }
        return false;
    }

    string BaseEntityCollection::appendSequenceNumber(const string& name) const
    {
        unsigned int nr = 2;
        string new_name = name;
        while(isNameReserved(new_name))
        {
            stringstream ss;
            ss << name << "_" << nr++;
            new_name = ss.str();
        }
        return new_name;
    }

    string BaseEntityCollection::nextAutoName() const
    {
        stringstream ss;
        ss << _entityPrefix << (_data.size() + 1);
        return appendSequenceNumber(ss.str());
    }

    unsigned int BaseEntityCollection::entityCount() const
    {
        return _data.size();
    }

    bool BaseEntityCollection::addEntity(BaseEntity* entity)
    {
        if (!isNameReserved(entity->getName()))
        {
            _data.push_back(entity);
            _selected = entity;
            return true;
        }
        return false;
    }

    bool BaseEntityCollection::deleteEntity(const string& entityName, bool& selectionChanged)
    {
        selectionChanged = false;
        BaseEntity* deleteEntity = getEntityByName(entityName);
        if (deleteEntity)
        {

            if (deleteEntity == _selected)
            {
                _selected = 0;
            }

            unsigned int deleteId = deleteEntity->getId();
            delete deleteEntity;
            _data.erase(_data.begin() + deleteId);

            for (vector<BaseEntity*>::iterator it = _data.begin() + deleteEntity->getId(); it != _data.end(); it++)
            {
                (*it)->decrease_id();
            }

            if (!_selected)
            {
                if (_data.size() == deleteId)
                {
                    deleteId--;
                }
                if (deleteId >= 0)
                {
                    _selected = _data[deleteId];
                }
                selectionChanged = true;
            }

            return true;
        }
        return false;
    }

    bool BaseEntityCollection::selectEntity(const string& entityName)
    {
        BaseEntity* newSelection = getEntityByName(entityName);
        if (newSelection)
        {
            if (!_selected)
            {
                _selected = newSelection;
                return true;
            }

            if (_selected != newSelection)
            {
                _selected = newSelection;
                return true;
            }
        }
        return false;
    }

    BaseEntity* BaseEntityCollection::getSelectedEntity() const
    {
        return _selected;
    }

    BaseEntity* BaseEntityCollection::getEntityByName(const string& entityName) const
    {
        for (unsigned int i = 0; i < _data.size(); i++)
        {
            if (_data[i]->getName() == entityName)
            {
                return _data[i];
            }
        }
        return 0;
    }

    BaseEntity* BaseEntityCollection::getEntityById(int entityId) const
    {
        if (entityId >= 0 && entityId < _data.size())
        {
            return _data[entityId];
        }
        return 0;
    }

    const vector<BaseEntity*> BaseEntityCollection::getData() const
    {
        return _data;
    }
}
