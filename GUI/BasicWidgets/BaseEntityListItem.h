#pragma once

#include <QWidget>
#include <string>
#include <QLineEdit>

#include "GUI/EditWidgets/BaseEditWidget.h"
#include "ui_BaseEntityListItem.h"
#include "GUI/WidgetExtensions/ToolButtonExtension.h"

using namespace std;

class BaseEntityListItem : public QWidget, protected Ui::BaseEntityListItem
{
    Q_OBJECT

private:
    QSize                   _sizeHint;
    QLineEdit*              _baseEntityBaseEntityNameEdit;
    bool                    _isRenameActive;
    bool                    _isEditActive;
    BaseEditWidget*         _editWidget;
    ToolButtonExtension*    _mirrorToolButton;

    void setVisible(bool visible);

public:
    explicit BaseEntityListItem(const string& labelText, BaseEditWidget* editWidget, QWidget *parent = 0);
    void setBaseEntityNameLabelText(const string& text);
    string getBaseEntityNameLabelText() const;
    string getBaseEntityBaseEntityNameEditText() const;
    void showEditWidget(bool show);
    bool isEditWidgetVisible();
    BaseEditWidget* editWidget();
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    void addRenameToolButton();
    void addEditToolButton();
    void addDeleteToolButton();
    void addMirrorToolButton();
    void deleteMirrorToolButton();

signals:
    void viewListItemDeleted(const string& labelText);
    void viewListItemRenamed(const string& labelText, const string& lineEditText);
    void viewListItemEdited(const string& labeltext);
    void viewListItemMirrored(const string& labelText);

private slots:
    void handleEdit();
    void handleRename();
    void handleDelete();
    void handleMirror();
};
