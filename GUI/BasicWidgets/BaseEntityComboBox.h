#pragma once

#include <QWidget>
#include "ui_BaseEntityComboBox.h"

#include "Model/BaseEntity.h"

using namespace std;
using namespace cor3d;

class BaseEntityComboBox: public QWidget, protected Ui::BaseEntityComboBox
{
    Q_OBJECT
public:
    // special and default constructor
    BaseEntityComboBox(QWidget *parent = 0);
    const BaseEntity value() const;
    int key() const;
    const string& text() const;
    void setValue(const BaseEntity& baseEntity);
    void setIndex(int index);
    void setLabel(const string& label_string);
    void setEditable(bool editable);
    void populate(const vector<BaseEntity>& values);
    void populateFromPointer(const vector<BaseEntity*>& values);

signals:
    void nameChanged(string name);
    void selectionChanged(int id);

private slots:
    void on_baseEntityComboBox_currentIndexChanged(int index);
    void on_baseEntityComboBox_editTextChanged(QString );
};
