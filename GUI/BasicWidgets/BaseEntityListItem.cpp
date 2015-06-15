#include "BaseEntityListItem.h"
#include "ui_BaseEntityListItem.h"
#include "GUI/WidgetExtensions/ToolButtonExtension.h"

#include <iostream>

#include <QMenu>

using namespace std;

BaseEntityListItem::BaseEntityListItem(const std::string& baseEntityNameLabelText, BaseEditWidget* editWidget, QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    _baseEntityBaseEntityNameEdit = 0;
    _mirrorToolButton = 0;
    baseEntityNameLabel->setText(QString::fromStdString(baseEntityNameLabelText));
    _sizeHint = QSize(100, 40);

    _isRenameActive = false;
    _isEditActive = false;
    _editWidget = editWidget;
    if (_editWidget)
    {
        _editWidget->setVisible(false);
        verticalLayout->addWidget(editWidget);
    }
}

void BaseEntityListItem::addRenameToolButton()
{
    ToolButtonExtension* renameToolButton = new ToolButtonExtension(this);
    renameToolButton->setIcon(QIcon(":/icons/Resources/renameIcon.png"));
    toolButtonLayout->addWidget(renameToolButton);
    _baseEntityBaseEntityNameEdit = new QLineEdit(this);
    _baseEntityBaseEntityNameEdit->setVisible(false);
    horizontalLayout->insertWidget(1, _baseEntityBaseEntityNameEdit);
    connect(renameToolButton, SIGNAL(clicked()), this, SLOT(handleRename()));
    connect(_baseEntityBaseEntityNameEdit, SIGNAL(returnPressed()), this, SLOT(handleRename()));
}

void BaseEntityListItem::addEditToolButton()
{
    ToolButtonExtension* editToolButton = new ToolButtonExtension(this);
    editToolButton->setIcon(QIcon(":/icons/Resources/editIcon.png"));
    toolButtonLayout->addWidget(editToolButton);
    connect(editToolButton, SIGNAL(clicked()), this, SLOT(handleEdit()));
}

void BaseEntityListItem::addDeleteToolButton()
{
    ToolButtonExtension* deleteToolButton = new ToolButtonExtension(this);
    deleteToolButton->setIcon(QIcon(":/icons/Resources/deleteIcon.png"));
    toolButtonLayout->addWidget(deleteToolButton);
    connect(deleteToolButton, SIGNAL(clicked()), this, SLOT(handleDelete()));
}

void BaseEntityListItem::addMirrorToolButton()
{
    QMenu *menu = new QMenu();
    QAction *testAction = new QAction("Mirror ", this);
    QAction *testAction1 = new QAction("Keep original z coordinate ", this);
    menu->addAction(testAction);
    menu->addAction(testAction1);

    _mirrorToolButton = new ToolButtonExtension(this);
    _mirrorToolButton->setAccessibleName(QString("mirrorToolButton"));
    _mirrorToolButton->setIcon(QIcon(":/icons/Resources/mirrorIcon.png"));
    _mirrorToolButton->setMenu(menu);
    _mirrorToolButton->setPopupMode(QToolButton::InstantPopup);
    toolButtonLayout->insertWidget(0, _mirrorToolButton);
    connect(_mirrorToolButton, SIGNAL(clicked()), this, SLOT(handleMirror()));
    connect(testAction, SIGNAL(triggered()), this, SLOT(handleMirror()));
}

void BaseEntityListItem::deleteMirrorToolButton()
{
    if (_mirrorToolButton)
    {
        delete _mirrorToolButton;
        _mirrorToolButton = 0;
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

string BaseEntityListItem::getBaseEntityNameLabelText() const
{
    return baseEntityNameLabel->text().toStdString();
}

string BaseEntityListItem::getBaseEntityBaseEntityNameEditText() const
{
    return _baseEntityBaseEntityNameEdit->text().toStdString();
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

void BaseEntityListItem::handleEdit()
{
    emit viewListItemEdited(baseEntityNameLabel->text().toStdString());
}

void BaseEntityListItem::handleRename()
{
    _isRenameActive = !_isRenameActive;

    if (_isRenameActive)
    {
        baseEntityNameLabel->setVisible(false);
        _baseEntityBaseEntityNameEdit->setText(baseEntityNameLabel->text());
        _baseEntityBaseEntityNameEdit->setVisible(true);
        _baseEntityBaseEntityNameEdit->setFocus();
    }
    else
    {
        _baseEntityBaseEntityNameEdit->setVisible(false);
        baseEntityNameLabel->setVisible(true);
        if (baseEntityNameLabel->text() != _baseEntityBaseEntityNameEdit->text())
        {
            emit viewListItemRenamed(baseEntityNameLabel->text().toStdString(), _baseEntityBaseEntityNameEdit->text().toStdString());
        }
    }
}

void BaseEntityListItem::handleDelete()
{
    emit viewListItemDeleted(baseEntityNameLabel->text().toStdString());
}

void BaseEntityListItem::handleMirror()
{
    emit viewListItemMirrored(baseEntityNameLabel->text().toStdString());
}

void BaseEntityListItem::setVisible(bool visible)
{
    QWidget::setVisible(visible);
    if (_baseEntityBaseEntityNameEdit)
    {
        _baseEntityBaseEntityNameEdit->setVisible(visible && _isRenameActive);
    }
    if (_editWidget)
    {
        _editWidget->setVisible(visible && _isEditActive);
    }
}
