#pragma once

#include "Core/TriangulatedMeshes3.h"
#include "Model/BaseEntity.h"
#include "Core/Materials.h"

using namespace cagd;
using namespace cor3d;
using namespace std;

class RenderingOptions {
    bool _render;
    bool _render_model;
    bool _render_joints;
    bool _render_links;

    bool _render_axis;

    unsigned int _model_material;
    unsigned int _joint_material;
    unsigned int _selected_joint_material;
    unsigned int _link_material;

    double model_opacity;

    string _joint_model_file;
    string _link_model_file;

     TriangulatedMesh3   _joint_model;
     TriangulatedMesh3   _link_model;
     TriangulatedMesh3   _cone_model;

     vector<BaseEntity>  _material_names;
     vector<Material*>   _materials;

     bool               is_initialized;
public:
    RenderingOptions()
    {
        _render = true;
        _render_model = true;
        _render_joints  = true;
        _render_links = true;
        _render_axis = true;

        _joint_model_file = "Models/sphere.off";
        _link_model_file = "Models/cone.off";

        _material_names.push_back(BaseEntity(0, "Brass"));
        _material_names.push_back(BaseEntity(1, "Gold"));
        _material_names.push_back(BaseEntity(2, "Silver"));
        _material_names.push_back(BaseEntity(3, "Emerald"));
        _material_names.push_back(BaseEntity(4, "Pearl"));
        _material_names.push_back(BaseEntity(5, "Ruby"));
        _material_names.push_back(BaseEntity(6, "Turquoise"));
        _materials.push_back(&MatFBBrass);
        _materials.push_back(&MatFBGold);
        _materials.push_back(&MatFBSilver);
        _materials.push_back(&MatFBEmerald);
        _materials.push_back(&MatFBPearl);
        _materials.push_back(&MatFBRuby);
        _materials.push_back(&MatFBTurquoise);

        _model_material = 4;
        _joint_material = 2;
        _selected_joint_material = 0;
        _link_material = 1;

        is_initialized = false;
    }

    void initialize()
    {
        if (true)
        {
            is_initialized = true;

            set_joint_model_file(_joint_model_file);
            set_link_model_file(_link_model_file);

            if (_cone_model.LoadFromOFF("Models/cone.off"))
            {
                _cone_model.UpdateVertexBufferObjects();
            }
        }
    }

    bool get_render() const
    {
        return _render;
    }

    bool get_render_model() const
    {
        return _render_model;
    }

    bool get_render_joints() const
    {
        return _render_joints;
    }

    bool get_render_links() const
    {
        return _render_links;
    }

    bool get_render_axis() const
    {
        return _render_axis;
    }

    const TriangulatedMesh3* get_joint_model() const
    {
        return &_joint_model;
    }

    const TriangulatedMesh3* get_link_model() const
    {
        return &_link_model;
    }

    const TriangulatedMesh3* get_cone_model() const
    {
        return &_cone_model;
    }

    const string& get_joint_model_file() const
    {
        return _joint_model_file;
    }

    const string& get_link_model_file() const
    {
        return _link_model_file;
    }

    unsigned int get_model_material() const
    {
        return _model_material;
    }

    unsigned int get_joint_material() const
    {
        return _joint_material;
    }

    unsigned int get_selected_joint_material() const
    {
        return _selected_joint_material;
    }

    unsigned int get_link_material() const
    {
        return _link_material;
    }

    void set_render_model(bool render_model)
    {
        _render_model = render_model;
    }

    void set_render_joints(bool render_joints)
    {
        _render_joints = render_joints;
    }

    void set_render_links(bool render_links)
    {
        _render_links = render_links;
    }

    void set_joint_model_file(const string& joint_model_file)
    {
        if (_joint_model.LoadFromOFF(joint_model_file))
        {
            _joint_model.UpdateVertexBufferObjects();
            _joint_model_file = joint_model_file;
        }
        else
        {
            _joint_model.LoadFromOFF(_joint_model_file);
            _joint_model.UpdateVertexBufferObjects();
        }
    }

    void set_link_model_file(const string& link_model_file)
    {
        if (_link_model.LoadFromOFF(link_model_file))
        {
            _link_model.UpdateVertexBufferObjects();
            _link_model_file = link_model_file;
        }
        else
        {
            _link_model.LoadFromOFF(_link_model_file);
            _link_model.UpdateVertexBufferObjects();
        }
    }

    void set_model_material(unsigned int model_material)
    {
        _model_material = model_material;
    }

    void set_joint_material(unsigned int joint_material)
    {
        _joint_material = joint_material;
    }

    void set_selected_joint_material(unsigned int selected_joint_material)
    {
        _selected_joint_material = selected_joint_material;
    }

    void set_link_material(unsigned int link_material)
    {
        _link_material = link_material;
    }

    const vector<BaseEntity>& get_materials() const
    {
        return _material_names;
    }

    Material* get_material(unsigned int id)
    {
        return _materials[id];
    }
};
