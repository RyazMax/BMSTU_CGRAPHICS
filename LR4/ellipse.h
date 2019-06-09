#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QPainter>

#include <math.h>

void draw_ellipse_sim(QPainter &painter, QPoint center, int x, int y);

void draw_ellipse_kanon(QPainter &painter, QPoint center, int a, int b);
void draw_ellipse_param(QPainter &painter, QPoint center, int a, int b);
void draw_ellipse_brezen(QPainter &painter, QPoint center, int a, int b);
void draw_ellipse_middle_point(QPainter &painter, QPoint center, int a, int b);
void draw_ellipse_standart(QPainter &painter, QPoint center, int a, int b);

void draw_spektr_ellipse(QPainter &painter, QPoint center, int a, int b, int stepX, int stepY, int count, void (*draw)(QPainter &, QPoint, int, int));

#endif // CIRCLE_H
