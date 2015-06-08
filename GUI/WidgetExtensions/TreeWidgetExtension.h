#pragma once

#include <QTreeWidget>

#include <iostream>

#include "Model/BaseEntity.h"

using namespace std;
using namespace cor3d;

class TreeWidgetExtension : public QTreeWidget
{
    Q_OBJECT
public:
    TreeWidgetExtension(QWidget* parent);

    QTreeWidgetItem* getTreeWidgetItemByData(const string& value);
    QTreeWidgetItem* getTopLevelTreeWidgetItemByData(const string& value);
    QTreeWidgetItem* getChildrenTreeWidgetItemByData(QTreeWidgetItem* parent, const string& value);
    void deleteTreeWidgetItemByData(const string& parentDataValue, const string& dataValue);
    void deleteTopLevelTreeWidgetItemByData(const string& dataValue);
    void addTreeWidgetItem(const string& parentDataValue, const string& dataValue, QWidget* itemWidget);
    void addTopLevelTreeWidgetItem(const string& dataValue, QWidget* itemWidget);
    void renameTreeWidgetItem(const string& oldName, const string& newName);
    void renameTreeWidgetItem(QTreeWidgetItem* item, const string& newName);
    void updateEditWidget(BaseEntity* baseEntity);
    void selectTreeWidgetItem(const string dataValue);
    void selectTreeWidgetItem(QTreeWidgetItem* parentItem, const string& dataValue);
    void selectTreeWidgetItemWithChildren(const string dataValue);
    void toggleEditWidget(const string& dataValue);

private:
    QTreeWidgetItem* _getTreeWidgetItemByData(QTreeWidgetItem* item, const string& value);
};
