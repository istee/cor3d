#pragma once

#include <QWidget>
#include <QFileDialog>
#include "ui_FileChooser.h"


using namespace std;

class FileChooser: public QWidget, protected Ui::FileChooser
{
    Q_OBJECT
    string                  _caption;
    string                  _filter;
    string                  _folder;
    string                  _filename;
    QFileDialog::AcceptMode _acceptMode;
public:
    // special and default constructor
    FileChooser(QWidget *parent = 0);
    const string& value() const;
    void setValue(const string& value);
    void setLabel(const string& label_string);
    void setCaption(const string& caption);
    void setFilter(const string& filter);
    void setButtonText(const string& buttonText);
    void setFilePath(const string& setFilePath);
    void setAcceptMode(const QFileDialog::AcceptMode acceptMode);

signals:
    void fileChanged(string);

private slots:
    void on_browseFilePushButton_released();
};
