#pragma once

#include <QListWidget>

#include "GUI/SideWidgetComponents/BaseSideWidget.h"

using namespace std;

namespace Ui {
    class ManagePostures;
}

class ManagePostures : public BaseSideWidget
{
    Q_OBJECT

private:
    Ui::ManagePostures *ui;

public:
    explicit ManagePostures(QWidget *parent = 0);
    void populatePostureList(Skeleton* skeleton);
    void addPosture(Skeleton* skeleton, Posture* posture);
    void deletePosture(const string& postureName);
    void renamePosture(const string& oldPostureName, const string& newPostureName);
    void selectPosture(Skeleton* skeleton, Posture* posture);
    ~ManagePostures();

signals:

    void viewPostureAdded(const string& postureName);
    void viewPostureRenamed(const string& oldPostureName, const string& newPostureName);
    void viewPostureDeleted(const string& postureName);
    void viewPostureSelected(const string& postureName);

private slots:
    void on_postureList_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void on_toolButtonAdd_clicked();
};

