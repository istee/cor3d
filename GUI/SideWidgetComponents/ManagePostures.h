#pragma once

#include <QWidget>
#include <QTreeWidget>

using namespace std;

namespace Ui {
    class ManagePostures;
}

class ManagePostures : public QWidget
{
    Q_OBJECT

public:
    explicit ManagePostures(QWidget *parent = 0);
    void addSkeleton(const string& name);
    void deleteSkeleton(const string& name);
    void renameSkeleton(const string& oldName, const string& newName);
    void selectSkeleton(const string& skeletonName);
    ~ManagePostures();

signals:
    void viewSkeletonSelected(const string& skeletonName);
    void viewPostureSelected(const string& postureName);

private:
    Ui::ManagePostures *ui;

private slots:
    void on_postureTreeWidget_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
};

