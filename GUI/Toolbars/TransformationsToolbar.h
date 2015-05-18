#ifndef TRANSFORMATIONSTOOLBAR_H
#define TRANSFORMATIONSTOOLBAR_H

#include <QWidget>

namespace Ui {
    class TransformationsToolbar;
}

class TransformationsToolbar : public QWidget
{
    Q_OBJECT

public:
    explicit TransformationsToolbar(QWidget *parent = 0);
    ~TransformationsToolbar();

private:
    Ui::TransformationsToolbar *ui;
};

#endif // TRANSFORMATIONSTOOLBAR_H
