#include "lines.h"


void draw_standart(int x1, int y1, int x2, int y2, QPainter &painter)
{
    painter.drawLine(x1, y1, x2, y2);
}

void draw_CDA(int x1, int y1, int x2, int y2, QPainter &painter)
{
    double dy = y2 - y1, dx = x2 - x1;
    int sx = sign(dx), sy = sign(dy);
    dy = fabs(dy), dx = fabs(dx);
    int cnt = dy > dx ? dy : dx;
    if (dx < dy) {
        dx = sx * dx / dy;
        dy = sy;
    } else {
        dy = sy * dy / dx;
        dx = sx;
    }
    double x = x1;
    double y = y1;

    for (int i = 0; i < cnt + 1; ++i) {
        painter.drawPoint(x, y);
        x += dx;
        y += dy;
    }
}

void draw_brezan(int x1, int y1, int x2, int y2, QPainter &painter)
{
    if (x1 == x2 && y1 == y2) {
        painter.drawPoint(x1, y1);
        return;
    }
    int x = x1, y = y1;
    int dx = x2 - x1, dy = y2 - y1;
    int sx = sign(dx), sy = sign(dy);
    dx = abs(dx), dy = abs(dy);
    int changed = 0;
    if (dx <= dy) {
        changed = 1;
        std::swap(dx, dy);
    }
    double m = (double)dy / dx;
    double e = m - 1/2;
    for (int i = 0; i < dx + 1; ++i) {
        painter.drawPoint(x, y);
        if (e > 0) {
            if (changed) {
                x += sx;
            } else {
                y += sy;
            }
            e -= 1;
        }
        if (changed) {
            y += sy;
        } else {
            x += sx;
        }
        e += m;
    }
}

void draw_brezan_int(int x1, int y1, int x2, int y2, QPainter &painter)
{
    if (x1 == x2 && y1 == y2) {
        painter.drawPoint(x1, y1);
        return;
    }
    int x = x1, y = y1;
    int dx = x2 - x1, dy = y2 - y1;
    int sx = sign(dx), sy = sign(dy);
    dx = abs(dx), dy = abs(dy);
    int changed = 0;
    if (dx < dy) {
        changed = 1;
        std::swap(dx, dy);
    }
    int dx2 = 2 * dx;
    int dy2 = 2 * dy;
    int e = dy2 - dx;
    for (int i = 0; i < dx + 2; ++i) {
        painter.drawPoint(x, y);
        while (e >= 0) {
            if (changed) {
                x += sx;
            } else {
                y += sy;
            }
            e -= dx2;
        }
        if (changed) {
            y += sy;
        } else {
            x += sx;
        }
        e += dy2;
    }
}

void draw_brezan_step(int x1, int y1, int x2, int y2, QPainter &painter)
{
    if (x1 == x2 && y1 == y2) {
        painter.drawPoint(x1, y1);
        return;
    }
    int x = x1, y = y1;
    int dx = x2 - x1, dy = y2 - y1;
    int sx = sign(dx), sy = sign(dy);
    dx = abs(dx), dy = abs(dy);
    bool changed = 0;
    if (dx <= dy) {
        changed = 1;
        std::swap(dx, dy);
    }
    QColor color = painter.pen().color();
    int I = 255;
    double e = I / 2;
    double m = (I * (double)dy / dx);
    double w = I - m;
    color.setAlpha(m / 2);
    painter.setPen(color);
    painter.drawPoint(x, y);
    for (int i = 0; i < dx + 1; ++i) {
        if (e > w) {
            y += sy;
            x += sx;
            e -= w;
        } else {
        if (changed) {
            y += sy;
        } else {
            x += sx;
        }
        e += m;
        }
        color.setAlpha(e);
        painter.setPen(color);
        painter.drawPoint(x, y);
    }
}

int sign(int x)
{
    return x > 0 ? 1 : -1;
}

int sign(double x)
{
    return x > 0 ? 1 : -1;
}

void test_visual(int xc, int yc, int len, double angle, void (*f)(int, int, int, int, QPainter &), QPainter &painter)
{
    angle = M_PI * angle / 180;
    int steps = 2 * M_PI / angle;

    for (int i = 0; i < steps; ++i) {
        f(xc, yc, xc + cos(angle * i) * len, yc + sin(angle * i) * len, painter);
    }
}
