#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QColorDialog>

#include "lines.h"

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
    void on_drawButton_clicked();

    void on_cleanButton_clicked();

    void on_chooseColorButton_clicked();

    void on_bgColorButton_clicked();

    void on_compareButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap pxp;
    QColor color = Qt::black;
    QColor bgColor = Qt::white;
};

#endif // MAINWINDOW_H
