#include "FileToolbar.h"
#include "ui_FileToolbar.h"

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
