#include "GUI/WidgetExtensions/TreeWidgetExtension.h"
#include "GUI/BasicWidgets/EditableDeletableListItem.h"

TreeWidgetExtension::TreeWidgetExtension(QWidget* parent = 0) : QTreeWidget(parent)
{
    this->setHeaderHidden(false);
}

QTreeWidgetItem* TreeWidgetExtension::getTreeWidgetItemByData(const string& value)
{
    return _getTreeWidgetItemByData(this->topLevelItem(0), value);
}

void TreeWidgetExtension::deleteTreeWidgetItemByData(const string& parentDataValue, const string& dataValue)
{
    QTreeWidgetItem* parentItem = getTreeWidgetItemByData(parentDataValue);
    QTreeWidgetItem* child = getTreeWidgetItemByData(dataValue);

    child = parentItem->takeChild(parentItem->indexOfChild(child));

    delete child;
}

void TreeWidgetExtension::deleteTopLevelTreeWidgetItemByData(const string& dataValue)
{
    QTreeWidgetItem* item = getTreeWidgetItemByData(dataValue);
    item = takeTopLevelItem(indexOfTopLevelItem(item));
    delete item;
}

void TreeWidgetExtension::addTreeWidgetItem(const string& parentDataValue, const string& dataValue, QWidget* itemWidget)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setData(0, Qt::UserRole, QVariant(QString::fromStdString(dataValue)));
    QTreeWidgetItem* parentItem = getTreeWidgetItemByData(parentDataValue);
    parentItem->addChild(item);
    setItemWidget(item, 0, itemWidget);
    parentItem->setExpanded(true);
}

void TreeWidgetExtension::addTopLevelTreeWidgetItem(const string& dataValue, QWidget* itemWidget)
{
    QTreeWidgetItem* topLevelItem = new QTreeWidgetItem();
    topLevelItem->setData(0, Qt::UserRole, QVariant(QString::fromStdString(dataValue)));
    addTopLevelItem(topLevelItem);
    setItemWidget(topLevelItem, 0, itemWidget);
}

void TreeWidgetExtension::renameTreeWidgetItem(const string& oldName, const string& newName)
{
    QTreeWidgetItem* item = getTreeWidgetItemByData(oldName);
    item->setData(0, Qt::UserRole, QVariant(QString::fromStdString(newName)));
    EditableDeletableListItem* itemWidget = (EditableDeletableListItem*) this->itemWidget(item, 0);
    itemWidget->setLabelText(newName);
}

void TreeWidgetExtension::updateEditWidget(BaseEntity* baseEntity)
{
    QTreeWidgetItem* item = getTreeWidgetItemByData(baseEntity->get_name());
    EditableDeletableListItem* itemWidget = (EditableDeletableListItem*) this->itemWidget(item, 0);
    itemWidget->editWidget()->updateContent(baseEntity);
}

void TreeWidgetExtension::selectTreeWidgetItem(const string dataValue)
{
    QTreeWidgetItem* item = currentItem();
    if (item)
    {
        string value = item->data(0, Qt::UserRole).toString().toStdString();
        if (dataValue != value)
        {
            item = getTreeWidgetItemByData(dataValue);
            if (item)
            {
                setCurrentItem(item);
            }
            else
            {
                item = currentItem();
                setCurrentItem(item, 0, QItemSelectionModel::Deselect);
            }
        }
    }
}

void TreeWidgetExtension::toggleEditWidget(const string& dataValue)
{
    QTreeWidgetItem* item = getTreeWidgetItemByData(dataValue);
    EditableDeletableListItem* listItem = (EditableDeletableListItem*) this->itemWidget(item, 0);
    listItem->showEditWidget(!listItem->isEditWidgetVisible());
    item->setSizeHint(0, listItem->sizeHint());
    bool isExpanded = item->isExpanded();
    item->setExpanded(!isExpanded);
    item->setExpanded(isExpanded);
}


QTreeWidgetItem* TreeWidgetExtension::_getTreeWidgetItemByData(QTreeWidgetItem* item, const string& value)
{
    if (item->data(0, Qt::UserRole).toString().toStdString() == value)
    {
        return item;
    }
    for (unsigned int i = 0; i < item->childCount(); i++)
    {
        QTreeWidgetItem* result = _getTreeWidgetItemByData(item->child(i), value);
        if (result)
        {
            return result;
        }
    }

    return 0;
}
