#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPainter>

#include <math.h>

void draw_circle_sim(QPainter &painter, QPoint center, int x, int y);

void draw_circle_kanon(QPainter &painter, QPoint center, int radius);
void draw_circle_param(QPainter &painter, QPoint center, int radius);
void draw_circle_brezen(QPainter &painter, QPoint center, int radius);
void draw_circle_middle_point(QPainter &painter, QPoint center, int radius);
void draw_circle_standart(QPainter &painter, QPoint center, int radius);

void draw_spektr(QPainter &painter, QPoint center, int rb, int rf, int step, int count, void (*draw)(QPainter &, QPoint, int));

#endif // CIRCLE_H
