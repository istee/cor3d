#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <QObject>

#include <iostream>

using namespace std;

namespace cor3d {
    class BaseEntity;

    class BaseEntity {
    protected:
        unsigned int    _id;
        string          _name;

    public:
        BaseEntity()
        {
            _id = -1;
            _name = "";
        }

        BaseEntity(unsigned int id, string name)
        {
            _id     = id;
            _name   = name;
        }

        // getter methods
        unsigned int getId() const
        {
            return _id;
        }

        const string& getName() const
        {
            return _name;
        }

        // setter methods
        virtual void setName(const string& name)
        {
            _name = name;
        }

        void decrease_id()
        {
            _id--;
        }

        //template <class BaseEntitySubclass>
        //friend bool isNameReserved(const string& name, const vector<BaseEntitySubclass*>& derived_entities);

        virtual ~BaseEntity()
        {

        }
    };

    /*
    template <class BaseEntitySubclass>
    bool isNameReserved(const string& name, const vector<BaseEntitySubclass*>& derived_entities)
    {
        for (typename vector<BaseEntitySubclass*>::const_iterator it = derived_entities.begin(); it != derived_entities.end(); it++)
        {
            if (((BaseEntity*) (*it))->_name == name)
            {
                return true;
            }
        }
        return false;
    }

    template <class BaseEntitySubclass>
    string appendSequenceNumber(const string& name, const vector<BaseEntitySubclass*>& derived_entities)
    {
        unsigned int nr = 2;
        string new_name = name;
        while(isNameReserved(new_name, derived_entities))
        {
            stringstream ss;
            ss << name << "_" << nr++;
            new_name = ss.str();
        }
        return new_name;
    }

    template <class BaseEntitySubclass>
    string nextName(const string& prefix, const vector<BaseEntitySubclass*>& derived_entities)
    {
        stringstream ss;
        ss << prefix << (derived_entities.size() + 1);
        return cor3d::appendSequenceNumber<BaseEntitySubclass>(ss.str(), derived_entities);
    }

    template <class BaseEntitySubclass>
    int getIdByName(const string& name, const vector<BaseEntitySubclass*>& derived_entities)
    {
        for (typename vector<BaseEntitySubclass*>::const_iterator it = derived_entities.begin(); it != derived_entities.end(); it++)
        {
            if (((BaseEntity*) (*it))->getName() == name)
            {
                return ((BaseEntity*) (*it))->getId();
            }
        }
        return -1;
    }

    template <class BaseEntitySubclass>
    vector<BaseEntity*> getBaseEntities(const vector<BaseEntitySubclass*>& derived_entities)
    {
        vector<BaseEntity*> base_entities;
        for (typename vector<BaseEntitySubclass*>::const_iterator it = derived_entities.begin(); it != derived_entities.end(); it++)
        {
            base_entities.push_back((BaseEntity*) (*it));
        }
        return base_entities;
    }
    */
}
