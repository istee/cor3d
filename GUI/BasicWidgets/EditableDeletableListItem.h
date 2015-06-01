#ifndef EDITABLEDELETABLELISTITEM_H
#define EDITABLEDELETABLELISTITEM_H

#include <QWidget>
#include <string>

#include "GUI/SideWidgetComponents/BaseSideWidget.h"

using namespace std;

namespace Ui {
    class EditableDeletableListItem;
}

class EditableDeletableListItem : public QWidget
{
    Q_OBJECT

public:
    explicit EditableDeletableListItem(const string& labelText, BaseSideWidget* editWidget, QWidget *parent = 0);
    void setLabelText(const string& text);
    string labelText() const;
    string lineEditText() const;
    void showEditWidget(bool show);
    bool isEditWidgetVisible();
    BaseSideWidget* editWidget();
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    ~EditableDeletableListItem();

signals:
    void view_list_item_deleted(const string& labelText);
    void view_list_item_renamed(const string& labelText, const string& lineEditText);
    void view_list_item_edited(const string& labeltext);

private:
    QSize               _sizeHint;
    bool                _isRenameActive;
    bool                _isEditActive;
    BaseSideWidget*     _editWidget;

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
