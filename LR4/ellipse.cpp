#include "circle.h"


void draw_ellipse_sim(QPainter &painter, QPoint center, int x, int y) {
    int xc = center.x();
    int yc = center.y();

    painter.drawPoint(xc + x, yc + y);
    painter.drawPoint(xc - x, yc + y);
    painter.drawPoint(xc - x, yc - y);
    painter.drawPoint(xc + x, yc - y);
}

void draw_ellipse_kanon(QPainter &painter, QPoint center, int a, int b) {
    int A = a * a;
    int B = b * b;
    int xk = round(A * sqrt((double)1 / (A + B)));
    int x = 0;
    int y = 0;
    while (x < round(xk)) {
        y = round(sqrt(B - (double)B / A * x * x));
        draw_ellipse_sim(painter, center, x, y);
        x++;
    }

    while (y >= 0) {
        x = round(sqrt(A - (double)A / B * y * y));
        draw_ellipse_sim(painter, center, x, y);
        y--;
    }
}

void draw_ellipse_param(QPainter &painter, QPoint center, int a, int b) {
    double border = M_PI / 4;
    double step = (double)1 / b;
    double angle = 0;

    while (angle <= border) {
        int axe_x = round(a * cos(angle));
        int axe_y = round(b * sin(angle));
        draw_ellipse_sim(painter, center, axe_x, axe_y);
        angle += step;
    }

    step = (double)1 / a;
    border = M_PI / 2;
    while (angle <= border) {
        int axe_x = round(a * cos(angle));
        int axe_y = round(b * sin(angle));
        draw_ellipse_sim(painter, center, axe_x, axe_y);
        angle += step;
    }
}

void draw_ellipse_brezen(QPainter &painter, QPoint center, int a, int b) {
    int x = 0;
    int y = b;
    int A = a * a;
    int B = b * b;
    int delta = A + B - 2 * A * b;
    for (; y >= 0;) {
        draw_ellipse_sim(painter, center, x, y);
        if (delta < 0) {
            int delta1 = 2 * (delta + A * y) - A;
            x += 1;
            if (delta1 <= 0) {
                delta = delta + 2 * B * x + B;
            } else {
                y -= 1;
                delta = delta + 2 * (B * x - A * y) + A + B;
            }
        } else if(delta > 0) {
            int delta2 = 2 * (delta - B * x) - B;
            y -= 1;
            if (delta2 <= 0) {
                x += 1;
                delta = delta + 2 * (B * x - A * y) + A + B;
            } else {
                delta = delta - 2 * A * y + A;
            }
        } else {
            x += 1;
            y -= 1;
            delta = delta = delta + 2 * (B * x - A * y) + A + B;
        }
    }
}

void draw_ellipse_middle_point(QPainter &painter, QPoint center, int a, int b) {
    int x = 0;
    int y = b;
    int A = a * a;
    int B = b * b;
    int Ad = 2 * A;
    int Bd = 2 * B;
    int dx = Bd * x + B;
    int dy = - Ad * y + A;
    int x_square = (x + 1) * (x + 1);
    int y_square = (2 * y - 1) * (2 * y - 1);

    int F = 4 * B * x_square + A * y_square - 4 * A * B;
    int oct_y = -8 * A * y + 8 * A;
    int oct_x = 8 * B * x + 12 * B;
    int oct_A = 8 * A;
    int oct_B = 8 * B;
    int L = A * y;
    while (L > 0) {
        draw_ellipse_sim(painter, center, x, y);

        if (F > 0) {
            F += oct_y;
            oct_y += oct_A;
            y -= 1;
            L -= A;
        }
        F += oct_x;
        oct_x += oct_B;
        x += 1;
        L -= B;
    }

    F += 3 * A - 3 * B - 4 * B * x - 4 * A * y;
    oct_y = -8 * A * y + 12 * A;
    oct_x = 8 * B * x + 8 * B;
    while (y >= 0) {
        draw_ellipse_sim(painter, center, x, y);

        if (F <= 0) {
            F += oct_x;
            oct_x += oct_B;
            x += 1;
        }
        F += oct_y;
        oct_y += oct_A;
        y -= 1;
    }
}

void draw_ellipse_standart(QPainter &painter, QPoint center, int a, int b) {
    painter.drawEllipse(center, a, b);
}

void draw_spektr_ellipse(QPainter &painter, QPoint center, int a, int b, int stepX, int stepY, int count, void (*draw)(QPainter &, QPoint, int, int))
{
    for (int i = 0; i < count; ++i) {
        draw(painter, center, a, b);
        a += stepX;
        b += stepY;
    }
}
