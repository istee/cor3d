#pragma once

#include <QWidget>
#include <QFileDialog>
#include "ui_FileDisplayAndChooser.h"


using namespace std;

class FileDisplayAndChooser: public QWidget, public Ui::FileDisplayAndChooser
{
    Q_OBJECT
    string                  _caption;
    string                  _filter;
    string                  _folder;
    string                  _filename;
    QFileDialog::AcceptMode _acceptMode;
public:
    // special and default constructor
    FileDisplayAndChooser(QWidget *parent = 0);
    string value() const;
    void setValue(const string& value);
    void setLabel(const string& label_string);
    void setCaption(const string& caption);
    void setFilter(const string& filter);
    void setButtonText(const string& buttonText);
    void setFilePath(const string& setFilePath);
    void setAcceptMode(const QFileDialog::AcceptMode acceptMode);

signals:
    void file_changed(string);

private slots:
    void on_pushButton_released();
};
