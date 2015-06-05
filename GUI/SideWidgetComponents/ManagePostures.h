#pragma once

#include <QWidget>

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
    ~ManagePostures();

private:
    Ui::ManagePostures *ui;
};

