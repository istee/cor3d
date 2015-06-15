#pragma once

#include "Core/TriangulatedMeshes3.h"
#include "Model/BaseEntity.h"
#include "Core/Materials.h"

#include <QObject>

using namespace cagd;
using namespace cor3d;
using namespace std;

class RenderingOptions: public QObject {
    Q_OBJECT

    bool                _renderSkeletonMesh;
    bool                _renderJoints;
    bool                _renderLinks;

    unsigned int        _skeletonMaterial;
    unsigned int        _linkMaterial;
    unsigned int        _jointMaterial;
    unsigned int        _selectedJointMaterial;


    double              _skeletonMeshOpacity;

    string              _jointMeshFile;
    string              _linkMeshFile;

    TriangulatedMesh3   _jointMesh;
    TriangulatedMesh3   _linkMesh;
    TriangulatedMesh3   _coneMesh;

    vector<BaseEntity>  _materialNames;
    vector<Material*>   _materials;

    bool                _isInitialized;

    DCoordinate3        _translation;
    DCoordinate3        _rotation;
    double              _zoom;

signals:
    void renderingOptionsChanged();

public:
    RenderingOptions(): QObject()
    {
        blockSignals(true);

        _renderSkeletonMesh = true;
        _renderJoints  = true;
        _renderLinks = true;

        _jointMeshFile = "Models/sphere.off";
        _linkMeshFile = "Models/cone.off";

        _materialNames.push_back(BaseEntity(0, "Brass"));
        _materialNames.push_back(BaseEntity(1, "Gold"));
        _materialNames.push_back(BaseEntity(2, "Silver"));
        _materialNames.push_back(BaseEntity(3, "Emerald"));
        _materialNames.push_back(BaseEntity(4, "Pearl"));
        _materialNames.push_back(BaseEntity(5, "Ruby"));
        _materialNames.push_back(BaseEntity(6, "Turquoise"));
        _materialNames.push_back(BaseEntity(7, "Jade"));
        _materialNames.push_back(BaseEntity(8, "Obsidian"));
        _materialNames.push_back(BaseEntity(9, "Bronze"));
        _materialNames.push_back(BaseEntity(10, "Chrome"));
        _materialNames.push_back(BaseEntity(11, "Copper"));
        _materialNames.push_back(BaseEntity(12, "Plastic Black"));
        _materialNames.push_back(BaseEntity(13, "Plastic Cyan"));
        _materialNames.push_back(BaseEntity(14, "Plastic Green"));
        _materialNames.push_back(BaseEntity(15, "Plastic Red"));
        _materialNames.push_back(BaseEntity(16, "Plastic White"));
        _materialNames.push_back(BaseEntity(17, "Plastic Yellow"));
        _materialNames.push_back(BaseEntity(18, "Rubber Black"));
        _materialNames.push_back(BaseEntity(19, "Rubber Cyan"));
        _materialNames.push_back(BaseEntity(20, "Rubber Green"));
        _materialNames.push_back(BaseEntity(21, "Rubber Red"));
        _materialNames.push_back(BaseEntity(22, "Rubber White"));
        _materialNames.push_back(BaseEntity(23, "Rubber Yellow"));
        _materials.push_back(&MatFBBrass);
        _materials.push_back(&MatFBGold);
        _materials.push_back(&MatFBSilver);
        _materials.push_back(&MatFBEmerald);
        _materials.push_back(&MatFBPearl);
        _materials.push_back(&MatFBRuby);
        _materials.push_back(&MatFBTurquoise);
        _materials.push_back(&MatFBJade);
        _materials.push_back(&MatFBObsidian);
        _materials.push_back(&MatFBBronze);
        _materials.push_back(&MatFBChrome);
        _materials.push_back(&MatFBCopper);
        _materials.push_back(&MatPlasticBlack);
        _materials.push_back(&MatPlasticCyan);
        _materials.push_back(&MatPlasticGreen);
        _materials.push_back(&MatPlasticRed);
        _materials.push_back(&MatPlasticWhite);
        _materials.push_back(&MatPlasticYellow);
        _materials.push_back(&MatRubberBlack);
        _materials.push_back(&MatRubberCyan);
        _materials.push_back(&MatRubberGreen);
        _materials.push_back(&MatRubberRed);
        _materials.push_back(&MatRubberWhite);
        _materials.push_back(&MatRubberYellow);

        _isInitialized = false;

        _translation = DCoordinate3(0.0, 0.0, 0.0);
        _rotation = DCoordinate3(0.0, 0.0, 0.0);
        _zoom = 1.0;

        restoreDefaultValues();

        blockSignals(false);
    }

    void initialize()
    {
        if (true)
        {
            blockSignals(true);

            _isInitialized = true;

            setJointMeshFile(_jointMeshFile);
            setLinkMeshFile(_linkMeshFile);

            if (_coneMesh.LoadFromOFF("Models/cone.off"))
            {
                _coneMesh.UpdateVertexBufferObjects();
            }

            blockSignals(false);
        }
    }

    bool restoreDefaultValues()
    {
        _skeletonMaterial = 7;
        _jointMaterial = 2;
        _selectedJointMaterial = 0;
        _linkMaterial = 1;
        emit renderingOptionsChanged();
    }

    bool isRenderSkeletonMesh() const
    {
        return _renderSkeletonMesh;
    }

    bool isRenderJoints() const
    {
        return _renderJoints;
    }

    bool isRenderLinks() const
    {
        return _renderLinks;
    }

    const TriangulatedMesh3* getLinkMesh() const
    {
        return &_linkMesh;
    }

    const TriangulatedMesh3* getJointMesh() const
    {
        return &_jointMesh;
    }

    const TriangulatedMesh3* getConeMesh() const
    {
        return &_coneMesh;
    }

    const string& getJointMeshFile() const
    {
        return _jointMeshFile;
    }

    const string& getLinkMeshFile() const
    {
        return _linkMeshFile;
    }

    unsigned int getSkeletonMaterial() const
    {
        return _skeletonMaterial;
    }

    unsigned int getJointMaterial() const
    {
        return _jointMaterial;
    }

    unsigned int getSelectedJointMaterial() const
    {
        return _selectedJointMaterial;
    }

    unsigned int getLinkMaterial() const
    {
        return _linkMaterial;
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

    void enableRenderSkeletonMesh(bool renderMesh)
    {
        _renderSkeletonMesh = renderMesh;
        emit renderingOptionsChanged();
    }

    void enableRenderJoints(bool renderJoints)
    {
        _renderJoints = renderJoints;
        emit renderingOptionsChanged();
    }

    void setRenderLinks(bool renderLinks)
    {
        _renderLinks = renderLinks;
        emit renderingOptionsChanged();
    }

    void setJointMeshFile(const string& joint_meshFile)
    {
        if (_jointMesh.LoadFromOFF(joint_meshFile))
        {
            _jointMesh.UpdateVertexBufferObjects();
            _jointMeshFile = joint_meshFile;
            emit renderingOptionsChanged();
        }
        else
        {
            _jointMesh.LoadFromOFF(_jointMeshFile);
            _jointMesh.UpdateVertexBufferObjects();
        }
    }

    void setLinkMeshFile(const string& link_meshFile)
    {
        if (_linkMesh.LoadFromOFF(link_meshFile))
        {
            _linkMesh.UpdateVertexBufferObjects();
            _linkMeshFile = link_meshFile;
            emit renderingOptionsChanged();
        }
        else
        {
            _linkMesh.LoadFromOFF(_linkMeshFile);
            _linkMesh.UpdateVertexBufferObjects();
        }
    }

    void setSkeletonMaterial(unsigned int model_material)
    {
        _skeletonMaterial = model_material;
        emit renderingOptionsChanged();
    }

    void setJointMaterial(unsigned int joint_material)
    {
        _jointMaterial = joint_material;
        emit renderingOptionsChanged();
    }

    void setSelectedJointMaterial(unsigned int selected_jointMaterial)
    {
        _selectedJointMaterial = selected_jointMaterial;
        emit renderingOptionsChanged();
    }

    void setLinkMaterial(unsigned int link_material)
    {
        _linkMaterial = link_material;
        emit renderingOptionsChanged();
    }

    const vector<BaseEntity>& getMaterials() const
    {
        return _materialNames;
    }

    Material* getMaterial(unsigned int id) const
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
