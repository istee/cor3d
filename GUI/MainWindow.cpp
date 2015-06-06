#include "MainWindow.h"

#include <QListWidgetItem>
#include <QFileDialog>
#include <QtGui>

#include "PostureGLWidget.h"
#include "SkeletonGLWidget.h"
#include "SkeletonEditorTab.h"
#include "RenderingOptions.h"
#include "GUI/PopupWindows/Export.h"
#include "GUI/PopupWindows/Import.h"
#include "GUI/SideWidgetComponents/RenderingOptionsWidget.h"
#include "GUI/Toolbars/TransformationsToolbar.h"
#include "GUI/Toolbars/FileToolbar.h"
#include "IMainWindowTab.h"

using namespace std;
using namespace cor3d;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUi(this);
    _transformationToolbar = new TransformationsToolbar(this);
    _transformationAction = transformationToolbarUi->addWidget(_transformationToolbar);

    Cor3d* _cor3d = ((Cor3dApplication*) qApp)->cor3d;

    fileToolbarUi->addWidget(new FileToolbar(this));
    connect(_transformationToolbar, SIGNAL(viewTranslationChanged(DCoordinate3)), _cor3d, SLOT(handle_view_translation_changed(DCoordinate3)));
    connect(_transformationToolbar, SIGNAL(viewRotationChanged(DCoordinate3)), _cor3d, SLOT(handle_view_rotation_changed(DCoordinate3)));
    connect(_transformationToolbar, SIGNAL(viewZoomFactorChanged(double)), _cor3d, SLOT(handle_view_zoom_changed(double)));

    connect(_cor3d, SIGNAL(model_translation_changed(DCoordinate3)), this, SLOT(handle_model_translation_changed(DCoordinate3)));
    connect(_cor3d, SIGNAL(model_rotation_changed(DCoordinate3)), this, SLOT(handle_model_rotation_changed(DCoordinate3)));
    connect(_cor3d, SIGNAL(model_zoom_changed(double)), this, SLOT(handle_model_zoom_changed(double)));

    _selectedTab = 0;
}

void MainWindow::initialize()
{
    skeleton_editor->initialize();
    posture_editor->initialize();
    scene_editor->initialize();
}

//--------------------------------
// implementation of private slots
//--------------------------------
void MainWindow::on_action_Quit_triggered()
{
    qApp->exit(0);
}


void MainWindow::on_actionRendering_options_activated()
{
    RenderingOptionsWidget *roWidget = new RenderingOptionsWidget(this);
    roWidget->setWindowTitle("Rendering Options");
    roWidget->setWindowModality(Qt::ApplicationModal);
    roWidget->setWindowFlags(Qt::Window);
    roWidget->show();

/*
    QBoxLayout *frameLayout = new QHBoxLayout();
    frameLayout->addWidget(roWidget);

    QFrame *qFrame = new QFrame(this);
    qFrame->setFrameStyle(QFrame::Sunken | QFrame::Box);
    qFrame->setGeometry(50,-2,100,15);
    qFrame->setLayout(frameLayout);
    qFrame->show();


    QDialog *dialog = new QDialog( this );
    dialog->setWindowFlags( Qt::WindowStaysOnTopHint );
                    dialog->show();


    QWidget *popup = new QWidget();
    popup->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    popup->setWindowModality(Qt::ApplicationModal);
    popup->show();
    */
}

void MainWindow::on_actionExport_triggered()
{
    Export *exportWindow = new Export(this);
    exportWindow->setWindowTitle("Export");
    exportWindow->setWindowModality(Qt::ApplicationModal);
    exportWindow->setWindowFlags(Qt::Window);
    exportWindow->show();
}

void MainWindow::on_actionImport_triggered()
{
    Import *importWindow = new Import(this);
    importWindow->setWindowTitle("Import");
    importWindow->setWindowFlags(Qt::Window);
    importWindow->show();
}

void MainWindow::on_actionTransformations_triggered(bool checked)
{
    transformationToolbarUi->setVisible(checked);
}

void MainWindow::handle_model_translation_changed(const DCoordinate3& translation)
{
    IMainWindowTab* currentMainWindowTab = (IMainWindowTab* ) tabWidget->currentWidget();
    currentMainWindowTab->setGLWidgetTranslation(translation);
    currentMainWindowTab->updateGlWidget();
    _transformationToolbar->setTranslation(translation);
}

void MainWindow::handle_model_rotation_changed(const DCoordinate3& rotation)
{
    IMainWindowTab* currentMainWindowTab = (IMainWindowTab* ) tabWidget->currentWidget();
    currentMainWindowTab->setGLWidgetRotation(rotation);
    currentMainWindowTab->updateGlWidget();
    _transformationToolbar->setRotation(rotation);
}

void MainWindow::handle_model_zoom_changed(double zoom)
{
    IMainWindowTab* currentMainWindowTab = (IMainWindowTab* ) tabWidget->currentWidget();
    currentMainWindowTab->setGLWidgetZoomFactor(zoom);
    currentMainWindowTab->updateGlWidget();
    _transformationToolbar->setZoomFactor(zoom);
}

void MainWindow::on_tabWidget_currentChanged(QWidget* tabWidget)
{
    Cor3d* cor3d = ((Cor3dApplication*) qApp)->cor3d;
    RenderingOptions* renderingOptions = cor3d->getRenderingOpstions();
    IMainWindowTab* mainWindowTab = (IMainWindowTab*) tabWidget;
    mainWindowTab->setGLWidgetTranslation(renderingOptions->getTranslation());
    mainWindowTab->setGLWidgetRotation(renderingOptions->getRotation());
    mainWindowTab->setGLWidgetZoomFactor(renderingOptions->getZoom());
    mainWindowTab->updateGlWidget();
}
