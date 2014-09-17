#include "FileDisplayAndChooser.h"

#include <QFileDialog>

using namespace std;

FileDisplayAndChooser::FileDisplayAndChooser(QWidget *parent): QWidget(parent)
{
    setupUi(this);
}

string FileDisplayAndChooser::value() const
{
    return file->text().toStdString();
}

void FileDisplayAndChooser::setValue(const string& value)
{
    unsigned found = value.find_last_of("/\\");
    file->setText(QString::fromStdString(value.substr(found+1)));
    file->setToolTip(QString::fromStdString(value));
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

void FileDisplayAndChooser::on_pushButton_released()
{
    string file_name = QFileDialog::getOpenFileName(this,tr("Open OFF model file"), "Models", tr("OFF Files (*.off)")).toStdString();
    emit file_changed(file_name);
}
