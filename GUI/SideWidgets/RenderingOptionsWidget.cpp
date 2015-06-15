#include "RenderingOptionsWidget.h"

using namespace std;
using namespace cor3d;

unsigned int int_to_unsigned(int integer)
{
    return (unsigned int) integer;
}

RenderingOptionsWidget::RenderingOptionsWidget(RenderingOptions* renderingOptions, QWidget *parent): QFrame(parent)
{
    setupUi(this);

    _renderingOptions = renderingOptions;

    skeletonMaterial->setLabel("Skeleton color");
    jointMeshFile->setLabel("Joint model");
    jointMeshFile->setCaption("Open OFF model file");
    jointMeshFile->setLabel("OFF Files (*.off)");
    jointMaterial->setLabel("Joint color");
    jointSelectedMaterial->setLabel("Joint selected color");
    linkMeshFile->setLabel("Link model");
    linkMeshFile->setCaption("Open OFF model file");
    linkMeshFile->setFilter("OFF Files (*.off)");
    linkMaterial->setLabel("Link color");
    renderJoints->hide();
    renderLink->hide();

    skeletonMaterial->populate(renderingOptions->getMaterials());
    skeletonMaterial->setIndex(renderingOptions->getSkeletonMaterial());
    jointMaterial->populate(renderingOptions->getMaterials());
    jointMaterial->setIndex(renderingOptions->getJointMaterial());
    jointSelectedMaterial->populate(renderingOptions->getMaterials());
    jointSelectedMaterial->setIndex(renderingOptions->getSelectedJointMaterial());
    linkMaterial->populate(renderingOptions->getMaterials());
    linkMaterial->setIndex(renderingOptions->getLinkMaterial());

    _skeletonMaterialBackup = renderingOptions->getSkeletonMaterial();
    _jointMaterialBackup = renderingOptions->getJointMaterial();
    _jointSelectedMaterialBackup = renderingOptions->getSelectedJointMaterial();
    _linkMaterial = renderingOptions->getLinkMaterial();

    connect(skeletonMaterial, SIGNAL(selectionChanged(int)), this, SLOT(skeletonMaterialSelectionChanged(int)));
    connect(jointMaterial, SIGNAL(selectionChanged(int)), this, SLOT(jointMaterialSelectionChanged(int)));
    connect(jointSelectedMaterial, SIGNAL(selectionChanged(int)), this, SLOT(jointSelectedMaterialSelectionChanged(int)));
    connect(linkMaterial, SIGNAL(selectionChanged(int)), this, SLOT(linkMaterialSelectionChanged(int)));
}

void RenderingOptionsWidget::on_defaultPushButton_clicked()
{
    _renderingOptions->restoreDefaultValues();
    this->close();
}

void RenderingOptionsWidget::on_savePushButton_clicked()
{
    this->close();
}

void RenderingOptionsWidget::on_cancelPushButton_clicked()
{
    _renderingOptions->setSkeletonMaterial(_skeletonMaterialBackup);
    _renderingOptions->setJointMaterial(_jointMaterialBackup);
    _renderingOptions->setSelectedJointMaterial(_jointSelectedMaterialBackup);
    _renderingOptions->setLinkMaterial(_linkMaterial);
    this->close();
}

void RenderingOptionsWidget::skeletonMaterialSelectionChanged(int material)
{
    _renderingOptions->setSkeletonMaterial(material);
}

void RenderingOptionsWidget::jointMaterialSelectionChanged(int material)
{
    cout << "material " << material << endl;
    _renderingOptions->setJointMaterial(material);
}

void RenderingOptionsWidget::jointSelectedMaterialSelectionChanged(int material)
{
    _renderingOptions->setSelectedJointMaterial(material);
}

void RenderingOptionsWidget::linkMaterialSelectionChanged(int material)
{
    _renderingOptions->setLinkMaterial(material);
}
