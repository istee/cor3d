#include "BaseEntityComboBox.h"

#include <iostream>
using namespace std;

BaseEntityComboBox::BaseEntityComboBox(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

const BaseEntity BaseEntityComboBox::value() const
{
    return BaseEntity((comboBox->itemData(comboBox->currentIndex())).toInt(0), comboBox->currentText().toStdString());
}

int BaseEntityComboBox::key() const
{
    if (comboBox->currentIndex() >= 0)
    {
        return (comboBox->itemData(comboBox->currentIndex())).toInt(0);
    }
    return -1;
}

string BaseEntityComboBox::text() const
{
    return comboBox->currentText().toStdString();
}

void BaseEntityComboBox::setValue(const BaseEntity& baseEntity)
{
    comboBox->blockSignals(true);
    comboBox->setCurrentIndex(comboBox->findData(baseEntity.get_id()));
    comboBox->blockSignals(false);
}

void BaseEntityComboBox::setIndex(int index)
{
    comboBox->blockSignals(true);
    comboBox->setCurrentIndex(index);
    comboBox->blockSignals(false);
}

void BaseEntityComboBox::setLabel(const string& label_string)
{
    label->setText(QString::fromStdString(label_string));
}

void BaseEntityComboBox::setEditable(bool editable)
{
    comboBox->setEditable(editable);
}

void BaseEntityComboBox::populate(const vector<BaseEntity>& values)
{
    comboBox->blockSignals(true);
    comboBox->clear();
    for (vector<BaseEntity>::const_iterator it = values.begin(); it != values.end(); it++)
    {
        comboBox->addItem(QString::fromStdString((*it).get_name()), QVariant((*it).get_id()));
    }
    comboBox->blockSignals(false);
}

void BaseEntityComboBox::on_comboBox_editTextChanged(QString string)
{
    emit name_changed(string.toStdString());
}

void BaseEntityComboBox::on_comboBox_currentIndexChanged(int index)
{
    emit selection_changed(index);
}
