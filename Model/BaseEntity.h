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
        unsigned int get_id() const
        {
            return _id;
        }

        const string& get_name() const
        {
            return _name;
        }

        // setter methods
        virtual void set_name(const string& name)
        {
            _name = name;
        }

        void decrease_id()
        {
            _id--;
        }

        template <class BaseEntitySubclass>
        friend bool is_name_reserved(const string& name, const vector<BaseEntitySubclass*>& derived_entities);
    };

    template <class BaseEntitySubclass>
    bool is_name_reserved(const string& name, const vector<BaseEntitySubclass*>& derived_entities)
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
    string append_sequence_number(const string& name, const vector<BaseEntitySubclass*>& derived_entities)
    {
        unsigned int nr = 2;
        string new_name = name;
        while(is_name_reserved(new_name, derived_entities))
        {
            stringstream ss;
            ss << name << "_" << nr++;
            new_name = ss.str();
        }
        return new_name;
    }

    template <class BaseEntitySubclass>
    string next_name(const string& prefix, const vector<BaseEntitySubclass*>& derived_entities)
    {
        stringstream ss;
        ss << prefix << (derived_entities.size() + 1);
        return cor3d::append_sequence_number<BaseEntitySubclass>(ss.str(), derived_entities);
    }

    template <class BaseEntitySubclass>
    int get_id_by_name(const string& name, const vector<BaseEntitySubclass*>& derived_entities)
    {
        for (typename vector<BaseEntitySubclass*>::const_iterator it = derived_entities.begin(); it != derived_entities.end(); it++)
        {
            if (((BaseEntity*) (*it))->get_name() == name)
            {
                return ((BaseEntity*) (*it))->get_id();
            }
        }
        return -1;
    }

    template <class BaseEntitySubclass>
    vector<BaseEntity*> get_base_entities(const vector<BaseEntitySubclass*>& derived_entities)
    {
        vector<BaseEntity*> base_entities;
        for (typename vector<BaseEntitySubclass*>::const_iterator it = derived_entities.begin(); it != derived_entities.end(); it++)
        {
            base_entities.push_back((BaseEntity*) (*it));
        }
        return base_entities;
    }
}
