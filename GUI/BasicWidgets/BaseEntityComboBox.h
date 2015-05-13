#pragma once

#include <QWidget>
#include "ui_BaseEntityComboBox.h"

#include "Model/BaseEntity.h"

using namespace std;
using namespace cor3d;

class BaseEntityComboBox: public QWidget, public Ui::BaseEntityComboBox
{
    Q_OBJECT
    void on_editingFinished();

public:
    // special and default constructor
    BaseEntityComboBox(QWidget *parent = 0);
    const BaseEntity value() const;
    int key() const;
    string text() const;
    void setValue(const BaseEntity& baseEntity);
    void setIndex(int index);
    void setLabel(const string& label_string);
    void setEditable(bool editable);
    void populate(const vector<BaseEntity>& values);

signals:
    void name_changed(string name);
    void selection_changed(int id);

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_editTextChanged(QString );
};
