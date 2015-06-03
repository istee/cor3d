#include "EditPosture.h"
#include "ui_EditPosture.h"

EditPosture::EditPosture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditPosture)
{
    ui->setupUi(this);
}

EditPosture::~EditPosture()
{
    delete ui;
}
