#include "NameLineEdit.h"

#include <QTimer>

using namespace std;

NameLineEdit::NameLineEdit(QWidget *parent): QWidget(parent)
{
    setupUi(this);
    lineEdit->installEventFilter(this);
 }

 bool NameLineEdit::eventFilter(QObject *obj, QEvent *event)
 {
     if(event->type() == QEvent::FocusIn) {
         QTimer::singleShot(0, obj, SLOT(selectAll()));
         return false;
     } else {
         return QObject::eventFilter(obj, event);
     }
 }
string NameLineEdit::value() const
{
    return lineEdit->text().toStdString();
}

void NameLineEdit::setValue(const string& value)
{
    lineEdit->setText(QString::fromStdString(value));
}

void NameLineEdit::setLabel(const string& label_string)
{
    label->setText(QString::fromStdString(label_string));
}

void NameLineEdit::on_lineEdit_editingFinished()
{
    emit name_changed(value());
}
