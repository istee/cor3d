#pragma once

#include <QListWidget>

#include "Model/Skeleton.h"

using namespace std;
using namespace cor3d;

class ListWidgetExtension : public QListWidget
{
    Q_OBJECT
public:
    ListWidgetExtension(QWidget* parent);
    void addListWigetItem(const string& dataValue, QWidget* itemWidget);
    void deleteListWidgetItemByData(const string& dataValue);
    void renameListWidgetItem(const string& oldName, const string& newName);
    void updateEditWidget(BaseEntity* baseEntity);
    void selectListWidgetItem(const string& dataValue);
    void toggleEditWidget(const string& dataValue);
private:
    QListWidgetItem* getListWidgetItemByData(const string& dataValue);
};
