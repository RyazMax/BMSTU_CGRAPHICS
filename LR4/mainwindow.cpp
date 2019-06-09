#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap *pxp = new QPixmap(ui->label->width(), ui->label->height());
    pxp->fill();
    ui->label->setPixmap(*pxp);
    QPixmap *curColorPxp = new QPixmap(ui->curColLabel->width(), ui->curColLabel->height());
    curColorPxp->fill(this->curColor);
    ui->curColLabel->setPixmap(*curColorPxp);
    ui->curColLabel_2->setPixmap(*curColorPxp);
}

MainWindow::~MainWindow()
{
    delete ui->label->pixmap();
    delete ui->curColLabel->pixmap();
    delete ui;
}

void MainWindow::on_backgroundButton_clicked()
{
    this->curColor = Qt::white;
    change_color_label(ui->curColLabel, this->curColor);
    change_color_label(ui->curColLabel_2, this->curColor);

}

void MainWindow::change_color_label(QLabel *label, QColor color)
{
    //delete ui->curColLabel->pixmap();
    QPixmap curColorPxp(ui->curColLabel->width(), ui->curColLabel->height());
    curColorPxp.fill(color);
    ui->curColLabel->setPixmap(curColorPxp);
    ui->curColLabel_2->setPixmap(curColorPxp);
}

void MainWindow::on_chooseColorButton_clicked()
{
    QColor newColor = QColorDialog::getColor();
    if (newColor.isValid()) {
        this->curColor = newColor;
        change_color_label(ui->curColLabel, this->curColor);
        change_color_label(ui->curColLabel_2, this->curColor);
    }
}

void MainWindow::on_drawButton_clicked()
{
    int xc = ui->xcEdit->text().toInt(), yc = ui->ycEdit->text().toInt();
    QPoint center(xc, yc);
    int radius = ui->rEdit->text().toInt();

    QPixmap pxp(*ui->label->pixmap());
   // pxp.fill();
    QPainter painter(&pxp);
    painter.setPen(this->curColor);

    if (ui->CanonRButton->isChecked()) {
        draw_circle_kanon(painter, center, radius);
    }

    if (ui->ParamRButton->isChecked()) {
        draw_circle_param(painter, center, radius);
    }

    if (ui->brezenRButton->isChecked()) {
        draw_circle_brezen(painter, center, radius);
    }

    if (ui->middlePRButton->isChecked()) {
        draw_circle_middle_point(painter, center, radius);
    }

    if (ui->standRButton->isChecked()) {
        draw_circle_standart(painter, center, radius);
    }

    if (ui->buttonGroup->checkedButton() == nullptr) {
        QMessageBox::warning(this, "Предупреждение", "Необходимо выбрать метод");
    }

    ui->label->setPixmap(pxp);
}

void MainWindow::on_drawSpektrButton_clicked()
{
    int xc = ui->xcEdit->text().toInt(), yc = ui->ycEdit->text().toInt();
    QPoint center(xc, yc);
    int rb = ui->rbEdit->text().isEmpty() ? 0 : ui->rbEdit->text().toInt();
    int rf = ui->RfEdit->text().isEmpty() ? 0 : ui->RfEdit->text().toInt();
    int steps = ui->stepEdit->text().isEmpty() ? 0 : ui->stepEdit->text().toInt();
    int cnt = ui->cntEdit->text().isEmpty() ? 0 : ui->cntEdit->text().toInt();

    if (cnt == 0 && steps == 0) {
        QMessageBox::warning(this, "Предупреждение", "Вы должны указать 3 из 4 полей");
        return;
    }

    QPixmap pxp(*ui->label->pixmap());
   // pxp.fill();
    QPainter painter(&pxp);
    painter.setPen(this->curColor);

    if (ui->CanonRButton->isChecked()) {
        draw_spektr(painter, center, rb, rf, steps, cnt, draw_circle_kanon);
    }

    if (ui->ParamRButton->isChecked()) {
        draw_spektr(painter, center, rb, rf, steps, cnt, draw_circle_param);
    }

    if (ui->brezenRButton->isChecked()) {
        draw_spektr(painter, center, rb, rf, steps, cnt, draw_circle_brezen);
    }

    if (ui->middlePRButton->isChecked()) {
        draw_spektr(painter, center, rb, rf, steps, cnt, draw_circle_middle_point);
    }

    if (ui->standRButton->isChecked()) {
        draw_spektr(painter, center, rb, rf, steps, cnt, draw_circle_standart);
    }

    if (ui->buttonGroup->checkedButton() == nullptr) {
        QMessageBox::warning(this, "Предупреждение", "Необходимо выбрать метод");
    }

    ui->label->setPixmap(pxp);
}

void MainWindow::on_chooseColorButton_2_clicked()
{
    this->on_chooseColorButton_clicked();
}

void MainWindow::on_backgroundButton_2_clicked()
{
    this->on_backgroundButton_clicked();
}

void MainWindow::on_drawButton_2_clicked()
{
    int xc = ui->xcEdit_2->text().toInt(), yc = ui->ycEdit_2->text().toInt();
    QPoint center(xc, yc);
    int a = ui->rEdit_2->text().toInt();
    int b = ui->rEdit_3->text().toInt();

    QPixmap pxp(*ui->label->pixmap());
   // pxp.fill();
    QPainter painter(&pxp);
    painter.setPen(this->curColor);

    if (ui->CanonRButton_2->isChecked()) {
        draw_ellipse_kanon(painter, center, a, b);
    }

    if (ui->ParamRButton_2->isChecked()) {
        draw_ellipse_param(painter, center, a, b);
    }

    if (ui->brezenRButton_2->isChecked()) {
        draw_ellipse_brezen(painter, center, a, b);
    }

    if (ui->middlePRButton_2->isChecked()) {
        draw_ellipse_middle_point(painter, center, a, b);
    }

    if (ui->standRButton_2->isChecked()) {
        draw_ellipse_standart(painter, center, a, b);
    }

    if (ui->buttonGroup_2->checkedButton() == nullptr) {
        QMessageBox::warning(this, "Предупреждение", "Необходимо выбрать метод");
    }

    ui->label->setPixmap(pxp);
}

void MainWindow::on_pushButton_clicked()
{
    QPixmap *pxp = new QPixmap(ui->label->width(), ui->label->height());
    pxp->fill();
    ui->label->setPixmap(*pxp);
}

void MainWindow::on_drawSpektrButton_2_clicked()
{
    int xc = ui->xcEdit_2->text().toInt(), yc = ui->ycEdit_2->text().toInt();
    QPoint center(xc, yc);
    int ra = ui->rbEdit_2->text().isEmpty() ? 0 : ui->rbEdit_2->text().toInt();
    int rb = ui->RfEdit_2->text().isEmpty() ? 0 : ui->RfEdit_2->text().toInt();
    int stepsA = ui->stepEdit_2->text().isEmpty() ? 0 : ui->stepEdit_2->text().toInt();
    int stepsB = ui->stepEdit_5->text().isEmpty() ? 0 : ui->stepEdit_5->text().toInt();
    int cnt = ui->cntEdit_2->text().isEmpty() ? 0 : ui->cntEdit_2->text().toInt();

    if (!ra || !rb || !stepsA || !stepsB) {
        QMessageBox::warning(this, "Предупреждение", "Вы должны заполнить все поля");
        return;
    }

    QPixmap pxp(*ui->label->pixmap());
   // pxp.fill();
    QPainter painter(&pxp);
    painter.setPen(this->curColor);

    if (ui->CanonRButton_2->isChecked()) {
        draw_spektr_ellipse(painter, center, ra, rb, stepsA, stepsB, cnt, draw_ellipse_kanon);
    }

    if (ui->ParamRButton_2->isChecked()) {
        draw_spektr_ellipse(painter, center, ra, rb, stepsA, stepsB, cnt, draw_ellipse_param);
    }

    if (ui->brezenRButton_2->isChecked()) {
        draw_spektr_ellipse(painter, center, ra, rb, stepsA, stepsB, cnt, draw_ellipse_brezen);
    }

    if (ui->middlePRButton_2->isChecked()) {
        draw_spektr_ellipse(painter, center, ra, rb, stepsA, stepsB, cnt, draw_ellipse_middle_point);
    }

    if (ui->standRButton_2->isChecked()) {
        draw_spektr_ellipse(painter, center, ra, rb, stepsA, stepsB, cnt, draw_ellipse_standart);
    }

    if (ui->buttonGroup_2->checkedButton() == nullptr) {
        QMessageBox::warning(this, "Предупреждение", "Необходимо выбрать метод");
    }

    ui->label->setPixmap(pxp);
}
