#include "RenderingOptionsWidget.h"

using namespace std;
using namespace cor3d;

unsigned int int_to_unsigned(int integer)
{
    return (unsigned int) integer;
}

RenderingOptionsWidget::RenderingOptionsWidget(QWidget *parent): QFrame(parent)
{
    setupUi(this);


    cor3dApp = (Cor3dApplication*) qApp;

    skeleton_color->setLabel("Skeleton color");
    joint_meshFile->setLabel("Joint model");
    joint_meshFile->setCaption("Open OFF model file");
    joint_meshFile->setLabel("OFF Files (*.off)");
    joint_color->setLabel("Joint color");
    joint_selected_color->setLabel("Joint selected color");
    link_meshFile->setLabel("Link model");
    link_meshFile->setCaption("Open OFF model file");
    link_meshFile->setFilter("OFF Files (*.off)");
    link_color->setLabel("Link color");
    joint_render->hide();
    link_render->hide();

    connect(skeleton_render, SIGNAL(toggled(bool)), this, SIGNAL(view_skeleton_render_toggled(bool)));
    connect(skeleton_color, SIGNAL(selectionChanged(int)), this, SIGNAL(view_skeleton_material_changed(int)));
    connect(joint_render, SIGNAL(toggled(bool)), this, SIGNAL(view_joint_render_toggled(bool)));
    connect(joint_meshFile, SIGNAL(fileChanged(string)), this, SIGNAL(view_joint_meshFileChanged(string)));
    connect(joint_color, SIGNAL(selectionChanged(int)), this, SIGNAL(view_joint_material_changed(int)));
    connect(joint_selected_color, SIGNAL(selectionChanged(int)), this, SIGNAL(view_selectedJoint_material_changed(int)));
    connect(link_render, SIGNAL(toggled(bool)), this, SIGNAL(view_link_render_toggled(bool)));
    connect(link_meshFile, SIGNAL(fileChanged(string)), this, SIGNAL(view_link_meshFileChanged(string)));
    connect(link_color, SIGNAL(selectionChanged(int)), this, SIGNAL(view_link_material_changed(int)));

}

void RenderingOptionsWidget::update_content()
{
    /*
    RenderingOptions *rendering_options = cor3dApp->cor3d->get_rendering_options();
    if (rendering_options)
    {
        blockSignals(true);
        skeleton_render->setChecked(rendering_options->get_render_model());
        skeleton_color->populate(rendering_options->get_materials());
        skeleton_color->setIndex(rendering_options->get_model_material());
        joint_render->setChecked(rendering_options->get_renderJoints());
        joint_color->populate(rendering_options->get_materials());
        joint_color->setIndex(rendering_options->get_joint_material());
        joint_selected_color->populate(rendering_options->get_materials());
        joint_selected_color->setIndex(rendering_options->get_selectedJoint_material());
        link_render->setChecked(rendering_options->get_renderLinks());
        link_color->populate(rendering_options->get_materials());
        link_color->setIndex(rendering_options->get_link_material());
        joint_meshFile->setValue(rendering_options->get_joint_meshFile());
        link_meshFile->setValue(rendering_options->get_link_meshFile());
        blockSignals(false);
    }
    */
}


void RenderingOptionsWidget::on_pushButton_3_clicked()
{
    this->close();
}
