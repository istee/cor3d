#ifndef EDITPOSTURE_H
#define EDITPOSTURE_H

#include <QWidget>

namespace Ui {
    class EditPosture;
}

class EditPosture : public QWidget
{
    Q_OBJECT

public:
    explicit EditPosture(QWidget *parent = 0);
    ~EditPosture();

private:
    Ui::EditPosture *ui;
};

#endif // EDITPOSTURE_H
