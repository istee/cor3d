#include "GUI/WidgetExtensions/TreeWidgetExtension.h"

QTreeWidgetItem* TreeWidgetExtension::getTreeWidgetItemByData(const string& value)
{
    return _getTreeWidgetItemByData(this->topLevelItem(0), value);
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
