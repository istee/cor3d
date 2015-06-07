#ifndef EDITABLEDELETABLELISTITEM_H
#define EDITABLEDELETABLELISTITEM_H

#include <QWidget>
#include <string>

#include "GUI/EditWidgets/BaseEditWidget.h"

using namespace std;

namespace Ui {
    class EditableDeletableListItem;
}

class EditableDeletableListItem : public QWidget
{
    Q_OBJECT

public:
    explicit EditableDeletableListItem(const string& labelText, BaseEditWidget* editWidget, QWidget *parent = 0);
    void setLabelText(const string& text);
    string labelText() const;
    string lineEditText() const;
    void showEditWidget(bool show);
    bool isEditWidgetVisible();
    void showRename(bool show);
    void showEdit(bool show);
    void showDelete(bool show);
    BaseEditWidget* editWidget();
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    ~EditableDeletableListItem();

signals:
    void viewListItemDeleted(const string& labelText);
    void viewListItemRenamed(const string& labelText, const string& lineEditText);
    void viewListItemEdited(const string& labeltext);

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
    Ui::EditableDeletableListItem *ui;

private slots:
    void on_lineEdit_returnPressed();
    void on_toolButtonEdit_clicked();
    void on_toolButtonRename_clicked();
    void on_toolButtonDelete_clicked();
};

#endif // EDITABLEDELETABLELISTITEM_H
