#include "BaseEntityNameEdit.h"

#include <QTimer>

using namespace std;

BaseEntityNameEdit::BaseEntityNameEdit(QWidget *parent): QWidget(parent)
{
    setupUi(this);
    lineEdit->installEventFilter(this);
}

void BaseEntityNameEdit::setToolButtonToolTip(const string& toolTip)
{
    toolButton->setToolTip(QString::fromStdString(toolTip));
}

void BaseEntityNameEdit::setEnabled(bool enabled)
{
    toolButton->setEnabled(enabled);
    lineEdit->setEnabled(enabled);
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
string BaseEntityNameEdit::getValue() const
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
    emit nameChanged(getValue());
}

void BaseEntityNameEdit::on_toolButton_clicked()
{
    emit baseEntityAdded(getValue());
}
