#include <sstream>
#include <fstream>
#include <string>

#include "Cor3d.h"
#include "BaseEntity.h"
#include "Skeleton.h"

namespace cor3d {
    Cor3d::Cor3d(): QObject()
    {
        _selected_skeleton_id = -1;
        _rendering_options = new RenderingOptions();
    }

    string Cor3d::next_name() const
    {
        return cor3d::next_name<Skeleton>("Skeleton ", _skeletons);
    }

    int Cor3d::get_skeleton_id_by_name(const string& name) const
    {
        return get_id_by_name<Skeleton>(name, _skeletons);
    }

    Skeleton* Cor3d::get_skeleton()
    {
        if (is_skeleton_selected())
        {
            return _skeletons[_selected_skeleton_id];
        }
        return 0;
    }

    Skeleton* Cor3d::getSkeletonById(unsigned int skeletonId)
    {
        if (skeletonId >= 0 && skeletonId < _skeletons.size())
        {
            return _skeletons[skeletonId];
        }
        return 0;
    }

    vector<BaseEntity*> Cor3d::get_skeleton_list()
    {
        return get_base_entities<Skeleton>(_skeletons);
    }

    RenderingOptions* Cor3d::get_rendering_options()
    {
        return _rendering_options;
    }

    bool Cor3d::is_skeleton_id_valid(int skeleton_id)
    {
        if (skeleton_id < 0)
        {
            return false;
        }
        if ((unsigned int)skeleton_id >= _skeletons.size())
        {
            return false;
        }
        return true;
    }

    bool Cor3d::is_skeleton_selected()
    {
        return is_skeleton_id_valid(_selected_skeleton_id);
    }

    void Cor3d::importSkeleton(ifstream& stream)
    {
        Skeleton* sk = new Skeleton(_skeletons.size(), "");
        stream >> *sk;
        _skeletons.push_back(sk);
        emit model_skeleton_list_changed();
    }

    // implementation of public slots

    void Cor3d::handle_view_skeleton_added(string name)
    {
        _skeletons.push_back(new Skeleton(_skeletons.size(), append_sequence_number<Skeleton>(name, _skeletons)));
        emit model_skeleton_list_changed();
    }

    void Cor3d::handle_view_skeleton_imported(const string& file_name)
    {
        ifstream file;
        Skeleton* sk = new Skeleton(_skeletons.size(), "");
        file.open(file_name.c_str());
        file >> *sk;
        _skeletons.push_back(sk);
        file.close();
        emit model_skeleton_list_changed();
    }

    void Cor3d::handle_view_skeleton_selected(int id)
    {
        if (!is_skeleton_id_valid(id))
        {
            _selected_skeleton_id = -1;
        }
        else
        {
            _selected_skeleton_id = id;
        }

        emit model_skeleton_selection_changed();
    }

    void Cor3d::handle_view_skeleton_deleted(const string& name)
    {
        unsigned int deleteId = get_skeleton_id_by_name(name);
        cout << "delete skeleton: " << name << "id: " << deleteId << endl;
        delete _skeletons[deleteId];
        _skeletons.erase(_skeletons.begin() + deleteId);
        for (vector<Skeleton*>::iterator it = _skeletons.begin() + deleteId; it != _skeletons.end(); it++)
        {
            ((BaseEntity*) *it)->decrease_id();
        }

        if (_selected_skeleton_id > _skeletons.size())
        {
            _selected_skeleton_id--;
        }
        emit model_skeleton_list_changed();
    }

    void Cor3d::handle_view_skeleton_exported(const string& file_name)
    {
        ofstream file;
        file.open(file_name.c_str());
        file << *get_skeleton();
        file.close();
    }

    void Cor3d::handle_view_skeleton_name_changed(const string& name)
    {
        get_skeleton()->set_name(append_sequence_number<Skeleton>(name, _skeletons));
        emit model_skeleton_data_changed();
    }

    void Cor3d::handle_view_skeleton_model_changed(const string& file_name)
    {
        get_skeleton()->set_model_file(file_name);
        emit model_skeleton_data_changed();
    }

    void Cor3d::handle_view_skeleton_model_scale_changed(const DCoordinate3& model_scale)
    {
        get_skeleton()->set_model_scale(model_scale);
        emit model_skeleton_data_changed();
    }

    void Cor3d::handle_view_skeleton_model_offset_changed(const DCoordinate3& model_offset)
    {
        get_skeleton()->set_model_offset(model_offset);
        emit model_skeleton_data_changed();
    }

    void Cor3d::handle_view_skeleton_render_toggled(bool on)
    {
        _rendering_options->set_render_model(on);
        emit model_rendering_options_changed();
    }

    void Cor3d::handle_view_skeleton_material_changed(int material_id)
    {
        _rendering_options->set_model_material(material_id);
        emit model_rendering_options_changed();
    }

    void Cor3d::handle_view_joint_render_toggled(bool on)
    {
        _rendering_options->set_render_joints(on);
        emit model_rendering_options_changed();
    }

    void Cor3d::handle_view_joint_model_file_changed(const string& file)
    {
        _rendering_options->set_joint_model_file(file);
        emit model_rendering_options_changed();
    }

    void Cor3d::handle_view_joint_material_changed(int material_id)
    {
        _rendering_options->set_joint_material(material_id);
        emit model_rendering_options_changed();
    }

    void Cor3d::handle_view_selected_joint_material_changed(int material_id)
    {
        _rendering_options->set_selected_joint_material(material_id);
        emit model_rendering_options_changed();
    }

    void Cor3d::handle_view_link_render_toggled(bool on)
    {
        _rendering_options->set_render_links(on);
        emit model_rendering_options_changed();
    }

    void Cor3d::handle_view_link_model_file_changed(const string& file)
    {
        _rendering_options->set_link_model_file(file);
        emit model_rendering_options_changed();
    }

    void Cor3d::handle_view_link_material_changed(int material_id)
    {
        _rendering_options->set_link_material(material_id);
        emit model_rendering_options_changed();
    }

}
