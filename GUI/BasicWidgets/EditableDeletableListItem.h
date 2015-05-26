#ifndef EDITABLEDELETABLELISTITEM_H
#define EDITABLEDELETABLELISTITEM_H

#include <QWidget>

#include <string>

using namespace std;

namespace Ui {
    class EditableDeletableListItem;
}

class EditableDeletableListItem : public QWidget
{
    Q_OBJECT

public:
    explicit EditableDeletableListItem(const string& labelText, QWidget *parent = 0);
    ~EditableDeletableListItem();

signals:
    void view_list_item_deleted(const string& labelText);

private:
    Ui::EditableDeletableListItem *ui;

private slots:
    void on_toolButtonDelete_clicked();
};

#endif // EDITABLEDELETABLELISTITEM_H
