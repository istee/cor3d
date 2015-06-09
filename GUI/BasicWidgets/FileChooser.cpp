#include "FileChooser.h"

#include <QFileDialog>

#include<iostream>

using namespace std;

FileChooser::FileChooser(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

const string& FileChooser::value() const
{
    return fileNameLabel->text().toStdString();
}

void FileChooser::setValue(const string& value)
{
    unsigned found = value.find_last_of("/\\");
    fileNameLabel->setText(QString::fromStdString(value.substr(found+1)));
    fileNameLabel->setToolTip(QString::fromStdString(value));
}

void FileChooser::setLabel(const string& label_string)
{
    entityPropertyLabel->setText(QString::fromStdString(label_string));
}

void FileChooser::setCaption(const string& caption)
{
    _caption = caption;
}

void FileChooser::setFilter(const string& filter)
{
    _filter = filter;
}

void FileChooser::setButtonText(const string& buttonText)
{
    browseFilePushButton->setText(QString::fromStdString(buttonText));
}

void FileChooser::setFilePath(const string& filePath)
{
    fileNameLabel->setText(QString::fromStdString(filePath));
}

void FileChooser::setAcceptMode(const QFileDialog::AcceptMode acceptMode)
{
    _acceptMode = acceptMode;
}

void FileChooser::on_browseFilePushButton_released()
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
    emit fileChanged(filename);
}
