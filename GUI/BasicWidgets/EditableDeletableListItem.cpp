#include "EditableDeletableListItem.h"
#include "ui_EditableDeletableListItem.h"

EditableDeletableListItem::EditableDeletableListItem(const std::string& labelText, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditableDeletableListItem)
{
    ui->setupUi(this);
    ui->label->setText(QString::fromStdString(labelText));
}

EditableDeletableListItem::~EditableDeletableListItem()
{
    delete ui;
}

void EditableDeletableListItem::on_toolButtonDelete_clicked()
{
    emit view_list_item_deleted(ui->label->text().toStdString());
}
