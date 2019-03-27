#ifndef LINES_H
#define LINES_H

#include <QPainter>

#include <math.h>
#include <algorithm>

int sign(int x);
int sign(double x);

void draw_standart(int x1, int y1, int x2, int y2, QPainter &painter);
void draw_CDA(int x1, int y1, int x2, int y2, QPainter &painter);
void draw_brezan(int x1, int y1, int x2, int y2, QPainter &painter);
void draw_brezan_int(int x1, int y1, int x2, int y2, QPainter &painter);
void draw_brezan_step(int x1, int y1, int x2, int y2, QPainter &painter);
void draw_vu(int x1, int y1, int x2, int y2, QPainter &painter);

void test_visual(int xc, int yc, int len, double angle, void (*f)(int, int, int, int, QPainter&), QPainter &painter);

#endif // LINES_H
