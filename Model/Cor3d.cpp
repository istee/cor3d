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

    unsigned int Cor3d::get_selected_skeleton_id() const
    {
        return _selected_skeleton_id;
    }

    Skeleton* Cor3d::getSkeletonById(unsigned int skeletonId)
    {
        if (skeletonId >= 0 && skeletonId < _skeletons.size())
        {
            return _skeletons[skeletonId];
        }
        return 0;
    }

    Skeleton* Cor3d::getSkeletonByName(const string& skeletonName)
    {
        int skeletonId = get_skeleton_id_by_name(skeletonName);
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
        Skeleton* sk = new Skeleton(_skeletons.size(), "asd");
        stream >> *sk;
        cout << *sk << endl << endl;
        _skeletons.push_back(sk);
        emit model_skeleton_added(sk->get_name());
    }

    // implementation of public slots

    void Cor3d::handle_view_translation_changed(const DCoordinate3& translation)
    {
        _rendering_options->setTranslation(translation);
        emit model_translation_changed(_rendering_options->getTranslation());
    }

    void Cor3d::handle_view_rotation_changed(const DCoordinate3& rotation)
    {
        _rendering_options->setRotation(rotation);
        emit model_rotation_changed(_rendering_options->getRotation());
    }

    void Cor3d::handle_view_zoom_changed(double zoom)
    {
        _rendering_options->setZoom(zoom);
        emit model_zoom_changed(_rendering_options->getZoom());
    }

    void Cor3d::handle_view_skeleton_added(string name)
    {
        Skeleton* skeleton = new Skeleton(_skeletons.size(), append_sequence_number<Skeleton>(name, _skeletons));
        skeleton->addRoot();
        _skeletons.push_back(skeleton);
        emit model_skeleton_added(skeleton->get_name());

        handle_view_skeleton_selected(skeleton->get_id());
    }

    void Cor3d::handle_view_skeleton_selected(int id)
    {
        if (id != _selected_skeleton_id)
        {
            string oldSelected = "", newSelected = "";
            Skeleton* skeleton = get_skeleton();
            if (skeleton)
            {
                oldSelected = skeleton->get_name();
            }

            if (!is_skeleton_id_valid(id))
            {
                _selected_skeleton_id = -1;
            }
            else
            {
                _selected_skeleton_id = id;
                newSelected = get_skeleton()->get_name();
            }

            cout << "emit " << oldSelected << " " << newSelected << endl;
            emit model_skeleton_selection_changed(oldSelected, newSelected);
        }
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
        emit model_skeleton_deleted(name);
    }

    void Cor3d::handle_view_skeleton_exported(const string& file_name)
    {
        ofstream file;
        file.open(file_name.c_str());
        file << *get_skeleton();
        file.close();
    }

    void Cor3d::handle_view_skeleton_renamed(const string& oldName, const string& newName)
    {
        ((Skeleton*) _skeletons[get_skeleton_id_by_name(oldName)])->set_name(newName);
        emit model_skeleton_renamed(oldName, newName);
    }

    void Cor3d::handle_view_skeleton_model_changed(const string& skeletonName, const string& file_name)
    {
        ((Skeleton*) _skeletons[get_skeleton_id_by_name(skeletonName)])->set_model_file(file_name);
        emit model_skeleton_model_data_changed(skeletonName);
    }

    void Cor3d::handle_view_skeleton_model_scale_changed(const string& skeletonName, const DCoordinate3& model_scale)
    {
        ((Skeleton*) _skeletons[get_skeleton_id_by_name(skeletonName)])->set_model_scale(model_scale);
        emit model_skeleton_model_data_changed(skeletonName);
    }

    void Cor3d::handle_view_skeleton_model_offset_changed(const string& skeletonName, const DCoordinate3& model_offset)
    {
        ((Skeleton*) _skeletons[get_skeleton_id_by_name(skeletonName)])->set_model_offset(model_offset);
        emit model_skeleton_model_data_changed(skeletonName);
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
