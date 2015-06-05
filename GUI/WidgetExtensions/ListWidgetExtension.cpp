#include "ListWidgetExtension.h"

#include "GUI/BasicWidgets/EditableDeletableListItem.h"

ListWidgetExtension::ListWidgetExtension(QWidget* parent = 0) : QListWidget(parent)
{
}

void ListWidgetExtension::addListWigetItem(const string& dataValue, QWidget* itemWidget)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(130, 40));
    item->setData(Qt::UserRole, QString::fromStdString(dataValue));
    addItem(item);
    setItemWidget(item, itemWidget);
}

void ListWidgetExtension::deleteListWidgetItemByData(const string& dataValue)
{
    QListWidgetItem* item = getListWidgetItemByData(dataValue);
    item = takeItem(row(item));
    delete item;
}

void ListWidgetExtension::renameListWidgetItem(const string& oldName, const string& newName)
{
    QListWidgetItem* item = getListWidgetItemByData(oldName);
    item->setData(Qt::UserRole, QString::fromStdString(newName));
    EditableDeletableListItem* itemWidget = (EditableDeletableListItem*) this->itemWidget(item);
    itemWidget->setLabelText(newName);
}

void ListWidgetExtension::updateEditWidget(BaseEntity* baseEntity)
{
    QListWidgetItem* item = getListWidgetItemByData(baseEntity->get_name());
    EditableDeletableListItem* itemWidget = (EditableDeletableListItem*) this->itemWidget(item);
    itemWidget->editWidget()->updateContent(baseEntity);;
}

void ListWidgetExtension::selectListWidgetItem(const string& dataValue)
{
    QListWidgetItem* item = getListWidgetItemByData(dataValue);
    if (item)
    {
        this->setCurrentItem(item);
    }
    else

    {
        clearSelection();
    }
}

void ListWidgetExtension::toggleEditWidget(const string& dataValue)
{
    QListWidgetItem* item = getListWidgetItemByData(dataValue);
    if (item)
    {
        EditableDeletableListItem* listItem = (EditableDeletableListItem*) itemWidget(item);
        listItem->showEditWidget(!listItem->isEditWidgetVisible());
        item->setSizeHint(listItem->sizeHint());
    }
}

QListWidgetItem* ListWidgetExtension::getListWidgetItemByData(const string& dataValue)
{
    int count = this->count();
    for (int index = 0; index < count; index++)
    {
        QListWidgetItem * item = this->item(index);
        if (item->data(Qt::UserRole).toString().toStdString() == dataValue)
        {
            return item;
        }
    }

    return 0;
}
