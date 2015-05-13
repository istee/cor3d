#include "FileDisplayAndChooser.h"

#include <QFileDialog>

#include<iostream>

using namespace std;

FileDisplayAndChooser::FileDisplayAndChooser(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

string FileDisplayAndChooser::value() const
{
    return fileLabel->text().toStdString();
}

void FileDisplayAndChooser::setValue(const string& value)
{
    unsigned found = value.find_last_of("/\\");
    fileLabel->setText(QString::fromStdString(value.substr(found+1)));
    fileLabel->setToolTip(QString::fromStdString(value));
}

void FileDisplayAndChooser::setLabel(const string& label_string)
{
    label->setText(QString::fromStdString(label_string));
}

void FileDisplayAndChooser::setCaption(const string& caption)
{
    _caption = caption;
}

void FileDisplayAndChooser::setFilter(const string& filter)
{
    _filter = filter;
}

void FileDisplayAndChooser::setButtonText(const string& buttonText)
{
    pushButton->setText(QString::fromStdString(buttonText));
}

void FileDisplayAndChooser::setFilePath(const string& filePath)
{
    fileLabel->setText(QString::fromStdString(filePath));
}

void FileDisplayAndChooser::setAcceptMode(const QFileDialog::AcceptMode acceptMode)
{
    _acceptMode = acceptMode;
}

void FileDisplayAndChooser::on_pushButton_released()
{
    QFileDialog fileDialog(this, QString::fromStdString(_caption), QString::fromStdString(_folder), QString::fromStdString(_filter));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    string filename = "";
    if (QFileDialog::AcceptSave == _acceptMode)
    {
        filename = fileDialog.getSaveFileName(this, QString::fromStdString(_caption), QString::fromStdString(_folder), QString::fromStdString(_filter)).toStdString();
    }
    else
    {
        filename = fileDialog.getOpenFileName(this, QString::fromStdString(_caption), QString::fromStdString(_folder), QString::fromStdString(_filter)).toStdString();
    }
    cout << "file name" << filename << endl;
    emit file_changed(filename);
}
