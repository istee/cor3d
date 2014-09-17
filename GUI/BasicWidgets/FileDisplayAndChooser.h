#pragma once

#include <QWidget>
#include "ui_FileDisplayAndChooser.h"


using namespace std;

class FileDisplayAndChooser: public QWidget, public Ui::FileDisplayAndChooser
{
    Q_OBJECT
    string      _caption;
    string      _filter;
public:
    // special and default constructor
    FileDisplayAndChooser(QWidget *parent = 0);
    string value() const;
    void setValue(const string& value);
    void setLabel(const string& label_string);
    void setCaption(const string& caption);
    void setFilter(const string& filter);

signals:
    void file_changed(string);

private slots:
    void on_pushButton_released();
};
