#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QColorDialog>
#include <QMessageBox>

#include "circle.h"
#include "ellipse.h"

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
    void on_backgroundButton_clicked();
    void change_color_label(QLabel *label, QColor color);

    void on_chooseColorButton_clicked();

    void on_drawButton_clicked();

    void on_drawSpektrButton_clicked();

    void on_chooseColorButton_2_clicked();

    void on_backgroundButton_2_clicked();

    void on_drawButton_2_clicked();

    void on_pushButton_clicked();

    void on_drawSpektrButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QColor curColor = Qt::black;
};

#endif // MAINWINDOW_H
