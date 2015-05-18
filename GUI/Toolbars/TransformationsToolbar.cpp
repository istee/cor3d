#include "TransformationsToolbar.h"
#include "ui_TransformationsToolbar.h"

TransformationsToolbar::TransformationsToolbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformationsToolbar)
{
    ui->setupUi(this);
}

TransformationsToolbar::~TransformationsToolbar()
{
    delete ui;
}
