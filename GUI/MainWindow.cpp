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
#include "GUI/SideWidgets/RenderingOptionsWidget.h"
#include "GUI/Toolbars/TransformationsToolbar.h"
#include "GUI/Toolbars/FileToolbar.h"
#include "IMainWindowTab.h"
#include "GUI/PopupWindows/AboutWindow.h"

using namespace std;
using namespace cor3d;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setupUi(this);
    _transformationToolbar = new TransformationsToolbar(this);
    _transformationAction = transformationToolbarUi->addWidget(_transformationToolbar);

    Cor3d* _cor3d = ((Cor3dApplication*) qApp)->cor3d;

    fileToolbarUi->addWidget(new FileToolbar(this));
    connect(_transformationToolbar, SIGNAL(viewTranslationChanged(DCoordinate3)), _cor3d, SLOT(handleViewTranslationChanged(DCoordinate3)));
    connect(_transformationToolbar, SIGNAL(viewRotationChanged(DCoordinate3)), _cor3d, SLOT(handleViewRotationChanged(DCoordinate3)));
    connect(_transformationToolbar, SIGNAL(viewZoomFactorChanged(double)), _cor3d, SLOT(handleViewZoomChanged(double)));

    connect(_cor3d, SIGNAL(modelTranslationChanged(DCoordinate3)), this, SLOT(handle_modelTranslationChanged(DCoordinate3)));
    connect(_cor3d, SIGNAL(modelRotationChanged(DCoordinate3)), this, SLOT(handle_modelRotationChanged(DCoordinate3)));
    connect(_cor3d, SIGNAL(modelZoomChanged(double)), this, SLOT(handle_modelZoomChanged(double)));

    IMainWindowTab* skeletonEditorTab = (IMainWindowTab*) tabWidget->widget(1);
    skeletonEditorTab->setSelected(true);
}

void MainWindow::initialize()
{

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
    RenderingOptionsWidget *roWidget = new RenderingOptionsWidget(((Cor3dApplication*) qApp)->cor3d->getRenderingOptions(), this);
    roWidget->setWindowTitle("Rendering Options");
    roWidget->setWindowModality(Qt::ApplicationModal);
    roWidget->setWindowFlags(Qt::Window);
    roWidget->show();
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

void MainWindow::handle_modelTranslationChanged(const DCoordinate3& translation)
{
    IMainWindowTab* currentMainWindowTab = (IMainWindowTab* ) tabWidget->currentWidget();
    currentMainWindowTab->setGLWidgetTranslation(translation);
    currentMainWindowTab->updateGLWidget();
    _transformationToolbar->setTranslation(translation);
}

void MainWindow::handle_modelRotationChanged(const DCoordinate3& rotation)
{
    IMainWindowTab* currentMainWindowTab = (IMainWindowTab* ) tabWidget->currentWidget();
    currentMainWindowTab->setGLWidgetRotation(rotation);
    currentMainWindowTab->updateGLWidget();
    _transformationToolbar->setRotation(rotation);
}

void MainWindow::handle_modelZoomChanged(double zoom)
{
    IMainWindowTab* currentMainWindowTab = (IMainWindowTab* ) tabWidget->currentWidget();
    currentMainWindowTab->setGLWidgetZoomFactor(zoom);
    currentMainWindowTab->updateGLWidget();
    _transformationToolbar->setZoomFactor(zoom);
}

void MainWindow::on_tabWidget_currentChanged(QWidget* tab)
{
    Cor3d* cor3d = ((Cor3dApplication*) qApp)->cor3d;
    RenderingOptions* renderingOptions = cor3d->getRenderingOptions();
    IMainWindowTab* mainWindowTab = (IMainWindowTab*) tab;
    mainWindowTab->setGLWidgetTranslation(renderingOptions->getTranslation());
    mainWindowTab->setGLWidgetRotation(renderingOptions->getRotation());
    mainWindowTab->setGLWidgetZoomFactor(renderingOptions->getZoom());

    for (int i = 0; i < tabWidget->count(); i++)
    {
        if (tabWidget->widget(i) != tab)
        {
            IMainWindowTab* t = (IMainWindowTab*) tabWidget->widget(i);
            if (t)
            {
                t->setSelected(false);
            }
        }
    }

    mainWindowTab->setSelected(true);
    mainWindowTab->updateGLWidget();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutWindow* aboutWindow = new AboutWindow(this);
    aboutWindow->setWindowTitle("About");
    aboutWindow->setWindowFlags(Qt::Window);
    aboutWindow->show();
}

void MainWindow::on_actionFile_triggered(bool checked)
{
    fileToolbarUi->setVisible(checked);
}
