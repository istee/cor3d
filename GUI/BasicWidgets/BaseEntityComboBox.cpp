#include "BaseEntityComboBox.h"

#include <iostream>
using namespace std;

BaseEntityComboBox::BaseEntityComboBox(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

const BaseEntity BaseEntityComboBox::getValue() const
{
    return BaseEntity((baseEntityComboBox->itemData(baseEntityComboBox->currentIndex())).toInt(0), baseEntityComboBox->currentText().toStdString());
}

int BaseEntityComboBox::getKey() const
{
    if (baseEntityComboBox->currentIndex() >= 0)
    {
        return (baseEntityComboBox->itemData(baseEntityComboBox->currentIndex())).toInt(0);
    }
    return -1;
}

const string& BaseEntityComboBox::getText() const
{
    return baseEntityComboBox->currentText().toStdString();
}

void BaseEntityComboBox::setValue(const BaseEntity& baseEntity)
{
    baseEntityComboBox->blockSignals(true);
    baseEntityComboBox->setCurrentIndex(baseEntityComboBox->findData(baseEntity.get_id()));
    baseEntityComboBox->blockSignals(false);
}

void BaseEntityComboBox::setIndex(int index)
{
    baseEntityComboBox->blockSignals(true);
    baseEntityComboBox->setCurrentIndex(index);
    baseEntityComboBox->blockSignals(false);
}

void BaseEntityComboBox::setLabel(const string& label_string)
{
    baseEntityNameLabel->setText(QString::fromStdString(label_string));
}

void BaseEntityComboBox::setEditable(bool editable)
{
    baseEntityComboBox->setEditable(editable);
}

void BaseEntityComboBox::populate(const vector<BaseEntity>& values)
{
    baseEntityComboBox->blockSignals(true);
    baseEntityComboBox->clear();
    for (vector<BaseEntity>::const_iterator it = values.begin(); it != values.end(); it++)
    {
        baseEntityComboBox->addItem(QString::fromStdString((*it).get_name()), QVariant((*it).get_id()));
    }
    baseEntityComboBox->blockSignals(false);
}

void BaseEntityComboBox::populateFromPointer(const vector<BaseEntity*>& values)
{
    baseEntityComboBox->blockSignals(true);
    baseEntityComboBox->clear();
    for (vector<BaseEntity*>::const_iterator it = values.begin(); it != values.end(); it++)
    {
        baseEntityComboBox->addItem(QString::fromStdString(((BaseEntity*)*it)->get_name()), QVariant(((BaseEntity*)*it)->get_id()));
    }
    baseEntityComboBox->blockSignals(false);
}

void BaseEntityComboBox::on_baseEntityComboBox_editTextChanged(QString string)
{
    emit nameChanged(string.toStdString());
}

void BaseEntityComboBox::on_baseEntityComboBox_currentIndexChanged(int index)
{
    emit selectionChanged(index);
}
