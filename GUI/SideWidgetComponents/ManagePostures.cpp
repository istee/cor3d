#include "ManagePostures.h"
#include "ui_ManagePostures.h"

ManagePostures::ManagePostures(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagePostures)
{
    ui->setupUi(this);
}

ManagePostures::~ManagePostures()
{
    delete ui;
}
