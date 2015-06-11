#ifndef FILETOOLBAR_H
#define FILETOOLBAR_H

#include <QWidget>

namespace Ui {
    class FileToolbar;
}

class FileToolbar : public QWidget
{
    Q_OBJECT

public:
    explicit FileToolbar(QWidget *parent = 0);
    ~FileToolbar();

private:
    Ui::FileToolbar *ui;

private slots:
    void on_toolButtonImport_clicked();
    void on_toolButtonExport_clicked();
};

#endif // FILETOOLBAR_H
