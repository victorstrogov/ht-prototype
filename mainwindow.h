#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <htmodelprototype.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    HtModelPrototype * m_model;
    Header* m_rootItem;
};

#endif // MAINWINDOW_H
