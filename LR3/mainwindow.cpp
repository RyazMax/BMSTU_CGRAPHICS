#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int width = ui->picture->width();
    int height = ui->picture->height();
    ui->x1spinBox->setMaximum(width);
    ui->x2spinBox->setMaximum(width);
    ui->y1spinBox->setMaximum(height);
    ui->y2spinBox->setMaximum(height);

    ui->ycSpinbBox->setMaximum(height);
    ui->xcSpinBox->setMaximum(width);
    pxp = QPixmap(width, height);
    pxp.fill();
    ui->picture->setPixmap(pxp);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    QPainter painter(&this->pxp);
    painter.setPen(this->color);

    int x1 = ui->x1spinBox->value();
    int x2 = ui->x2spinBox->value();
    int y1 = ui->y1spinBox->value();
    int y2 = ui->y2spinBox->value();
    if (ui->standart->isChecked()) {
        draw_standart(x1, y1, x2, y2, painter);
    }

    if (ui->cda->isChecked()) {
        draw_CDA(x1, y1, x2, y2, painter);
    }

    if (ui->brezan->isChecked()) {
        draw_brezan(x1, y1, x2, y2, painter);
    }

    if (ui->brezan_int->isChecked()) {
        draw_brezan_int(x1, y1, x2, y2, painter);
    }

    if (ui->brezan_step->isChecked()) {
        draw_brezan_step(x1, y1, x2, y2, painter);
    }

    if (ui->buttonGroup->checkedButton() == nullptr) {
        QMessageBox::warning(this, "Предупреждение", "Необходимо выбрать тип линии");
    }
    ui->picture->setPixmap(pxp);
}

void MainWindow::on_cleanButton_clicked()
{
    pxp.fill();
    ui->picture->setPixmap(pxp);
}

void MainWindow::on_chooseColorButton_clicked()
{
   QColor newColor = QColorDialog::getColor(Qt::black, this, "Цвет линии");
   if (newColor.isValid()) {
       this->color = newColor;
   }
}

void MainWindow::on_bgColorButton_clicked()
{
    this->color = this->bgColor;
}

void MainWindow::on_compareButton_clicked()
{
    QPainter painter(&this->pxp);
    painter.setPen(this->color);

    int x1 = ui->xcSpinBox->value();
    int y1 = ui->ycSpinbBox->value();
    int len = ui->lenSpinBox->value();
    int angle = ui->angleSpinBox->value();
    if (ui->standart->isChecked()) {
        test_visual(x1, y1, len, angle, draw_standart, painter);
    }

    if (ui->cda->isChecked()) {
        test_visual(x1, y1, len, angle, draw_CDA, painter);
    }

    if (ui->brezan->isChecked()) {
        test_visual(x1, y1, len, angle, draw_brezan, painter);
    }

    if (ui->brezan_int->isChecked()) {
        test_visual(x1, y1, len, angle, draw_brezan_int, painter);
    }

    if (ui->brezan_step->isChecked()) {
        test_visual(x1, y1, len, angle, draw_brezan_step, painter);
    }

    if (ui->buttonGroup->checkedButton() == nullptr) {
        QMessageBox::warning(this, "Предупреждение", "Необходимо выбрать тип линии");
    }
    ui->picture->setPixmap(pxp);
}

void MainWindow::on_pushButton_clicked()
{
    this->color = Qt::black;
}
