#ifndef MANAGEPOSTURES_H
#define MANAGEPOSTURES_H

#include <QWidget>

namespace Ui {
    class ManagePostures;
}

class ManagePostures : public QWidget
{
    Q_OBJECT

public:
    explicit ManagePostures(QWidget *parent = 0);
    ~ManagePostures();

private:
    Ui::ManagePostures *ui;
};

#endif // MANAGEPOSTURES_H
