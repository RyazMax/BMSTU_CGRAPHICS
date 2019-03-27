#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pxp = QPixmap(ui->label->width(), ui->label->height());
    pxp.fill();
    ui->label->setPixmap(pxp);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(std::initializer_list<QString>{tr("X"), tr("Y")});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QMessageBox::information(this, "Условие задачи", "На плоскости дано множество точек. Найти такой выпуклый четырехугольник, вершины которого лежат в точках заданного множества, у которого разность площадейнаибольшего и наименьшего треугольников образованных пересечением диагоналей, минимальна");
}

void MainWindow::on_addPointButton_clicked()
{
    QStringList input = ui->addPointEdit->text().split(" ");
    if (input.size() != 2) {
        QMessageBox::warning(this, "Неверные данные", "Задано неверное число координат");
        return;
    }

    bool isOk = true;

    double x = input.at(0).toDouble(&isOk);
    double y = input.at(1).toDouble(&isOk);

    if (!isOk) {
        QMessageBox::warning(this, "Неверные данные", "Введены неверные координаты");
        return;
    }

    this->points.push_back(point_t{x, y});

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::number(x)));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(y)));
}

void MainWindow::on_clearButton_clicked()
{
    this->pxp.fill();
    this->points.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->label->setPixmap(this->pxp);

}

void MainWindow::on_deletePointButton_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    delete ui->tableWidget->takeItem(currentRow, 0);
    delete ui->tableWidget->takeItem(currentRow, 1);
    ui->tableWidget->removeRow(currentRow);
    this->points.erase(this->points.begin() + currentRow);
}

void MainWindow::on_solveButton_clicked()
{
    if (this->points.size() < 4) {
        QMessageBox::warning(this, "Предупреждение", "Недостаточно точек");
        return;
    }
    for (int i = 0; i < points.size(); ++i) {
        std::cout << points[i].x << " " << points[i]. y << "\n";
    }
    std::cout.flush();
    rect_t ans = get_min_sub(this->points);

    if (!is_rect(ans.p1, ans.p2, ans.p3, ans.p4)) {
        QMessageBox::warning(this, "Предупреждение", "На указанном множестве не найдено подходящий 4 -угольников");
        return;
    }

    point_t max1, max2, max3;
    double max_square = get_square(get_max_tring(ans));
    double min_square = get_square(get_min_tring(ans));
    double sub = max_square - min_square;

    ui->maxAnsLabel->setText("Наибольшая площадь = " + QString::number(max_square, 'f', 3));
    ui->minAnsLabel->setText("Наименьшая площадь = " + QString::number(min_square, 'f', 3));
    ui->subLabel->setText("Разность = " + QString::number(sub, 'f', 3));

    this->pxp.fill();

    QPainter painter(&this->pxp);

    draw_solution(ans, painter);

    ui->label->setPixmap(this->pxp);
}

void MainWindow::on_changePointButton_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    double newX = ui->tableWidget->item(currentRow, 0)->text().toDouble();
    double newY = ui->tableWidget->item(currentRow, 1)->text().toDouble();
    this->points[currentRow] = point_t{newX, newY};
}
