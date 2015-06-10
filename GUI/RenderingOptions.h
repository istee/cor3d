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
    bool _renderJoints;
    bool _renderLinks;

    bool _render_axis;

    unsigned int _model_material;
    unsigned int _joint_material;
    unsigned int _selectedJoint_material;
    unsigned int _link_material;

    double model_opacity;

    string _joint_meshFile;
    string _link_meshFile;

    TriangulatedMesh3   _joint_model;
    TriangulatedMesh3   _link_model;
    TriangulatedMesh3   _cone_model;

    vector<BaseEntity>  _material_names;
    vector<Material*>   _materials;

    bool               is_initialized;

    DCoordinate3        _translation;
    DCoordinate3        _rotation;
    double              _zoom;

public:
    RenderingOptions()
    {
        _render = true;
        _render_model = true;
        _renderJoints  = true;
        _renderLinks = true;
        _render_axis = true;

        _joint_meshFile = "Models/sphere.off";
        _link_meshFile = "Models/cone.off";

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
        _selectedJoint_material = 0;
        _link_material = 1;

        is_initialized = false;

        _translation = DCoordinate3(0.0, 0.0, 0.0);
        _rotation = DCoordinate3(0.0, 0.0, 0.0);
        _zoom = 1.0;
    }

    void initialize()
    {
        if (true)
        {
            is_initialized = true;

            set_joint_meshFile(_joint_meshFile);
            set_link_meshFile(_link_meshFile);

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

    bool get_renderJoints() const
    {
        return _renderJoints;
    }

    bool get_renderLinks() const
    {
        return _renderLinks;
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

    const string& get_joint_meshFile() const
    {
        return _joint_meshFile;
    }

    const string& get_link_meshFile() const
    {
        return _link_meshFile;
    }

    unsigned int get_model_material() const
    {
        return _model_material;
    }

    unsigned int get_joint_material() const
    {
        return _joint_material;
    }

    unsigned int get_selectedJoint_material() const
    {
        return _selectedJoint_material;
    }

    unsigned int get_link_material() const
    {
        return _link_material;
    }

    DCoordinate3 getTranslation() const
    {
        return _translation;
    }

    DCoordinate3 getRotation() const
    {
        return _rotation;
    }

    double getZoom() const
    {
        return _zoom;
    }

    void set_render_model(bool render_model)
    {
        _render_model = render_model;
    }

    void set_renderJoints(bool renderJoints)
    {
        _renderJoints = renderJoints;
    }

    void set_renderLinks(bool renderLinks)
    {
        _renderLinks = renderLinks;
    }

    void set_joint_meshFile(const string& joint_meshFile)
    {
        if (_joint_model.LoadFromOFF(joint_meshFile))
        {
            _joint_model.UpdateVertexBufferObjects();
            _joint_meshFile = joint_meshFile;
        }
        else
        {
            _joint_model.LoadFromOFF(_joint_meshFile);
            _joint_model.UpdateVertexBufferObjects();
        }
    }

    void set_link_meshFile(const string& link_meshFile)
    {
        if (_link_model.LoadFromOFF(link_meshFile))
        {
            _link_model.UpdateVertexBufferObjects();
            _link_meshFile = link_meshFile;
        }
        else
        {
            _link_model.LoadFromOFF(_link_meshFile);
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

    void set_selectedJoint_material(unsigned int selected_joint_material)
    {
        _selectedJoint_material = selected_joint_material;
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

    void setTranslation(DCoordinate3 translation)
    {
        _translation = translation;
    }

    void setRotation(DCoordinate3 rotaion)
    {
        _rotation = rotaion;
    }

    void setZoom(double zoom)
    {
        _zoom = zoom;
    }
};
