#pragma once

#include <QTreeWidget>

#include <iostream>

using namespace std;

class TreeWidgetExtension : public QTreeWidget
{
    Q_OBJECT
public:
    TreeWidgetExtension(QWidget* parent = 0) : QTreeWidget(parent)
    {

    }

    QTreeWidgetItem* getTreeWidgetItemByData(const string& value);

private:
    QTreeWidgetItem* _getTreeWidgetItemByData(QTreeWidgetItem* item, const string& value);
};
