#include "BaseEntityNameEdit.h"

#include <QTimer>

using namespace std;

BaseEntityNameEdit::BaseEntityNameEdit(QWidget *parent): QWidget(parent)
{
    setupUi(this);
    lineEdit->installEventFilter(this);
 }

 bool BaseEntityNameEdit::eventFilter(QObject *obj, QEvent *event)
 {
     if(event->type() == QEvent::FocusIn) {
         QTimer::singleShot(0, obj, SLOT(selectAll()));
         return false;
     } else {
         return QObject::eventFilter(obj, event);
     }
 }
string BaseEntityNameEdit::value() const
{
    return lineEdit->text().toStdString();
}

void BaseEntityNameEdit::setValue(const string& value)
{
    lineEdit->setText(QString::fromStdString(value));
}

void BaseEntityNameEdit::setLabel(const string& label_string)
{
    label->setText(QString::fromStdString(label_string));
}

void BaseEntityNameEdit::on_lineEdit_editingFinished()
{
    emit nameChanged(value());
}

void BaseEntityNameEdit::on_toolButton_clicked()
{
    emit baseEntityAdded(value());
}
