#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_RenderingOptionsWidget.h"
#include "BaseSideWidget.h"
#include "GUI/RenderingOptions.h"
#include "Cor3dApplication.h"

using namespace std;

class RenderingOptionsWidget: public QFrame, public Ui::RenderingOptionsWidget
{
    Q_OBJECT
    RenderingOptions*           _renderingOptions;
    int                         _skeletonMaterialBackup;
    int                         _jointMaterialBackup;
    int                         _jointSelectedMaterialBackup;
    int                         _linkMaterial;
public:
    // special and default constructor
    RenderingOptionsWidget(RenderingOptions*, QWidget *parent = 0);

private slots:
    void on_cancelPushButton_clicked();
    void on_savePushButton_clicked();
    void on_defaultPushButton_clicked();

    void skeletonMaterialSelectionChanged(int);
    void jointMaterialSelectionChanged(int);
    void jointSelectedMaterialSelectionChanged(int);
    void linkMaterialSelectionChanged(int);
};
