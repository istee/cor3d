#include "FileToolbar.h"
#include "ui_FileToolbar.h"

#include "GUI/PopupWindows/Export.h"
#include "GUI/PopupWindows/Import.h"

FileToolbar::FileToolbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileToolbar)
{
    ui->setupUi(this);
}

FileToolbar::~FileToolbar()
{
    delete ui;
}

void FileToolbar::on_toolButtonExport_clicked()
{
    Export *exportWindow = new Export(this);
    exportWindow->setWindowTitle("Export");
    exportWindow->setWindowModality(Qt::ApplicationModal);
    exportWindow->setWindowFlags(Qt::Window);
    exportWindow->show();
}

void FileToolbar::on_toolButtonImport_clicked()
{
    Import *importWindow = new Import(this);
    importWindow->setWindowTitle("Import");
    importWindow->setWindowFlags(Qt::Window);
    importWindow->show();
}
