#pragma once

#include <QWidget>
#include <string>

#include "GUI/EditWidgets/BaseEditWidget.h"
#include "ui_BaseEntityListItem.h"

using namespace std;

class BaseEntityListItem : public QWidget, protected Ui::BaseEntityListItem
{
    Q_OBJECT

private:
    QSize               _sizeHint;
    bool                _isRenameActive;
    bool                _isEditActive;
    bool                _isRenameVisible;
    bool                _isEditVisible;
    bool                _isDeleteVisible;
    BaseEditWidget*     _editWidget;

    void handleRename();
    void setVisible(bool visible);

public:
    explicit BaseEntityListItem(const string& labelText, BaseEditWidget* editWidget, QWidget *parent = 0);
    void setBaseEntityNameLabelText(const string& text);
    string getBaseEntityNameLabelText() const;
    string getBaseEntityBaseEntityNameEditText() const;
    void showEditWidget(bool show);
    bool isEditWidgetVisible();
    void showRename(bool show);
    void showEdit(bool show);
    void showDelete(bool show);
    BaseEditWidget* editWidget();
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void viewListItemDeleted(const string& labelText);
    void viewListItemRenamed(const string& labelText, const string& lineEditText);
    void viewListItemEdited(const string& labeltext);

private slots:
    void on_baseEntityBaseEntityNameEdit_returnPressed();
    void on_editToolButton_clicked();
    void on_renameToolButton_clicked();
    void on_deleteToolButton_clicked();
};
