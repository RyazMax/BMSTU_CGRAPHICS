#ifndef RECT_H
#define RECT_H

#include <QPainter>
#include <QPoint>

#include <math.h>
#include <vector>
#include <algorithm>

#include "vector.h"

struct rect_t {
    point_t p1;
    point_t p2;
    point_t p3;
    point_t p4;
};

struct triangle_t {
    point_t p1;
    point_t p2;
    point_t p3;
};

bool is_rect(point_t p1, point_t p2, point_t p3, point_t p4);
rect_t get_min_sub(std::vector<point_t> points);
triangle_t get_min_tring(rect_t rect);
triangle_t get_max_tring(rect_t rect);

point_t get_normalized(point_t p, int width, int height, double w, double offsetx, double offsety);
triangle_t get_normalized_tring(triangle_t t, int width, int height, double w, double offsetx, double offsety);
rect_t get_normalized_rect(rect_t r, int width, int height, double w, double offsetx, double offsety);

double get_square(triangle_t triangle);

void draw_solution(rect_t rect, QPainter &painter);
void draw_rect(rect_t rect, QPainter &painter);
void draw_triangle(triangle_t tring, QPainter &painter  );

#endif // RECT_H
