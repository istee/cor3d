#pragma once

#include <QWidget>
#include "ui_BaseEntityNameEdit.h"


using namespace std;

class BaseEntityNameEdit: public QWidget, protected Ui::BaseEntityNameEdit
{
    Q_OBJECT
public:
    // special and default constructor
    BaseEntityNameEdit(QWidget *parent = 0);
    bool eventFilter(QObject *obj, QEvent *event);
    string value() const;
    void setValue(const string& value);
    void setLabel(const string& label_string);

signals:
    void nameChanged(const string& name);
    void baseEntityAdded(const string& name);

private slots:
    void on_toolButton_clicked();
    void on_lineEdit_editingFinished();
};
