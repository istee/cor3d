#pragma once

#include <QWidget>
#include "ui_NameLineEdit.h"


using namespace std;

class NameLineEdit: public QWidget, public Ui::NameLineEdit
{
    Q_OBJECT
public:
    // special and default constructor
    NameLineEdit(QWidget *parent = 0);
    bool eventFilter(QObject *obj, QEvent *event);
    string value() const;
    void setValue(const string& value);
    void setLabel(const string& label_string);

signals:
    void name_changed(const string& name);

private slots:
    void on_lineEdit_editingFinished();
};
