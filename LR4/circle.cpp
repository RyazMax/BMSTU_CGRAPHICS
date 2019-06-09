#include "circle.h"


void draw_circle_sim(QPainter &painter, QPoint center, int x, int y) {
    int xc = center.x();
    int yc = center.y();

    painter.drawPoint(xc + x, yc + y);
    painter.drawPoint(xc - x, yc + y);
    painter.drawPoint(xc - x, yc - y);
    painter.drawPoint(xc + x, yc - y);

    painter.drawPoint(xc + y, yc + x);
    painter.drawPoint(xc - y, yc + x);
    painter.drawPoint(xc - y, yc - x);
    painter.drawPoint(xc + y, yc - x);
}

void draw_circle_kanon(QPainter &painter, QPoint center, int radius) {
    int squareR = radius * radius;
    int halfR = round(radius / sqrt(2));
    for (int i = 0; i <= halfR; ++i) {
        int dy = round(sqrt(squareR - i * i));
        draw_circle_sim(painter, center, i, dy);
    }
}

void draw_circle_param(QPainter &painter, QPoint center, int radius) {
    double border = M_PI / 4;
    double step = 1 / (double)radius;
    double angle = 0;

    while (angle <= border) {
        int axe_x = round(radius * cos(angle));
        int axe_y = round(radius * sin(angle));
        draw_circle_sim(painter, center, axe_x, axe_y);
        angle += step;
    }
}

void draw_circle_brezen(QPainter &painter, QPoint center, int radius) {
    int x = 0;
    int y = radius;
    int delta = 2 * (1 - radius);
    for (; y >= 0;) {
        draw_circle_sim(painter, center, x, y);
        if (delta < 0) {
            int delta1 = 2 * (delta + y) - 1;
            x += 1;
            if (delta1 <= 0) {
                delta = delta + 2 * x + 1;
            } else {
                y -= 1;
                delta = delta + 2 * (x - y + 1);
            }
        } else if(delta > 0) {
            int delta2 = 2 * (delta - x) - 1;
            y -= 1;
            if (delta2 <=0) {
                x += 1;
                delta = delta + 2 * (x - y + 1);
            } else {
                delta = delta - 2 * y + 1;
            }
        } else {
            x += 1;
            y -= 1;
            delta = delta + 2 * (x - y + 1);
        }
    }
}

void draw_circle_middle_point(QPainter &painter, QPoint center, int radius) {
    int x = 0;
    int y = radius;
    int r_square = radius * radius;
    int x_square = (x + 1) * (x + 1);
    int y_square = (2 * y - 1) * (2 * y - 1);
    int F = 4 * x_square + y_square - 4 * r_square;
    int oct_y = -8 * y + 8;
    int oct_x = 8 * x + 12;

    while (x <= y) {
        draw_circle_sim(painter, center, x, y);

        if (F > 0) {
            F += oct_y;
            oct_y += 8;
            y -= 1;
        }
        F += oct_x;
        oct_x += 8;
        x += 1;
    }
}

void draw_circle_standart(QPainter &painter, QPoint center, int radius) {
    painter.drawEllipse(center, radius, radius);
}

void draw_spektr(QPainter &painter, QPoint center, int rb, int rf, int step, int count, void (*draw)(QPainter &, QPoint, int))
{
    if (rb == 0) {
        rb = rf - step * count;
    }

    if (rf == 0) {
        rf = rb + step * count;
    }

    if (step == 0) {
        step = (rf - rb) / count;
    }

    int rx = rb;
    while (rx <= rf) {
        draw(painter, center, rx);
        rx += step;
    }
}
