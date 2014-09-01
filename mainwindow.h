#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QGraphicsScene>
#include "data.h"
#include "view.h"

/* This is the controller class of MVC pattern. */

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
    void showEvent(QShowEvent *event);

private:
    Ui::MainWindow *ui;
    Data dataModel;
    View *view;
    QString fileName;
};

#endif // MAINWINDOW_H
