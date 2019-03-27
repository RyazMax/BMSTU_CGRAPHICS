#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>

#include <vector>
#include <utility>

//Debug
#include <iostream>

#include "rect.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_addPointButton_clicked();

    void on_clearButton_clicked();

    void on_deletePointButton_clicked();

    void on_solveButton_clicked();

    void on_changePointButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<point_t> points;
    QPixmap pxp;
};

#endif // MAINWINDOW_H
