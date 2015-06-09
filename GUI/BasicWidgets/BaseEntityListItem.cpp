#include "BaseEntityListItem.h"
#include "ui_BaseEntityListItem.h"

#include <iostream>

using namespace std;

BaseEntityListItem::BaseEntityListItem(const std::string& baseEntityNameLabelText, BaseEditWidget* editWidget, QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    baseEntityNameLabel->setText(QString::fromStdString(baseEntityNameLabelText));
    baseEntityBaseEntityNameEdit->setVisible(false);
    _sizeHint = QSize(100, 40);

    _isRenameVisible = true;
    _isEditVisible = true;
    _isDeleteVisible = true;
    _isRenameActive = false;
    _isEditActive = false;
    _editWidget = editWidget;
    if (_editWidget)
    {
        _editWidget->setVisible(false);
        verticalLayout->addWidget(editWidget);
    }
}

void BaseEntityListItem::setBaseEntityNameLabelText(const string& text)
{
    baseEntityNameLabel->setText(QString::fromStdString(text));
    if (_editWidget)
    {
        _editWidget->setEntityName(text);
    }
}

string BaseEntityListItem::baseEntityNameLabelText() const
{
    return baseEntityNameLabel->text().toStdString();
}

string BaseEntityListItem::baseEntityBaseEntityNameEditText() const
{
    return baseEntityBaseEntityNameEdit->text().toStdString();
}

void BaseEntityListItem::showEditWidget(bool show)
{
    if (_editWidget)
    {
        _isEditActive = show;
        _editWidget->setVisible(_isEditActive);
        if (_isEditActive)
        {
            _editWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        }
    }
}

bool BaseEntityListItem::isEditWidgetVisible()
{
    return _isEditActive;
}

BaseEditWidget* BaseEntityListItem::editWidget()
{
    return _editWidget;
}

void BaseEntityListItem::showRename(bool show)
{
    renameToolButton->setVisible(show);
    _isRenameVisible = show;
}

void BaseEntityListItem::showEdit(bool show)
{
    editToolButton->setVisible(show);
    _isEditVisible = show;
}

void BaseEntityListItem::showDelete(bool show)
{
    deleteToolButton->setVisible(show);
    _isDeleteVisible = show;
}

QSize BaseEntityListItem::sizeHint() const
{
    if (_editWidget && _isEditActive)
    {
        return QSize(_sizeHint.width(), _sizeHint.height() + _editWidget->sizeHint().height());
    }
    else
    {
        return _sizeHint;
    }
}

QSize BaseEntityListItem::minimumSizeHint() const
{
    if (_isEditActive)
    {
        return QSize(100, 200);
    }
    else
    {
        return QSize(100, 40);
    }
}

void BaseEntityListItem::on_deleteToolButton_clicked()
{
    emit viewListItemDeleted(baseEntityNameLabel->text().toStdString());
}

void BaseEntityListItem::handleRename()
{
    _isRenameActive = !_isRenameActive;

    if (_isRenameActive)
    {
        baseEntityNameLabel->setVisible(false);
        baseEntityBaseEntityNameEdit->setText(baseEntityNameLabel->text());
        baseEntityBaseEntityNameEdit->setVisible(true);
        baseEntityBaseEntityNameEdit->setFocus();
    }
    else
    {
        baseEntityBaseEntityNameEdit->setVisible(false);
        baseEntityNameLabel->setVisible(true);
        if (baseEntityNameLabel->text() != baseEntityBaseEntityNameEdit->text())
        {
            emit viewListItemRenamed(baseEntityNameLabel->text().toStdString(), baseEntityBaseEntityNameEdit->text().toStdString());
        }
    }
}

void BaseEntityListItem::setVisible(bool visible)
{
    QWidget::setVisible(visible);
    renameToolButton->setVisible(visible && _isRenameVisible);
    editToolButton->setVisible(visible && _isEditVisible);
    deleteToolButton->setVisible(visible && _isDeleteVisible);
    baseEntityBaseEntityNameEdit->setVisible(visible && _isRenameActive);
    if (_editWidget)
    {
        _editWidget->setVisible(visible && _isEditActive);
    }
}

void BaseEntityListItem::on_renameToolButton_clicked()
{
    handleRename();
}

void BaseEntityListItem::on_baseEntityBaseEntityNameEdit_returnPressed()
{
    handleRename();
}

void BaseEntityListItem::on_editToolButton_clicked()
{
    emit viewListItemEdited(baseEntityNameLabel->text().toStdString());
}
