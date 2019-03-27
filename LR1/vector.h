#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

struct point_t {
    double x;
    double y;
};

struct vector_t {
    point_t first;
    point_t second;
};

double vector_mul(vector_t a, vector_t b);
double get_delta_x(vector_t a);
double get_delta_y(vector_t a);

bool is_points_equal(point_t a, point_t b);
bool is_on_line(vector_t v, point_t p);
bool is_intersected(vector_t a, vector_t b);
point_t intersect(vector_t a, vector_t b);

#endif // VECTOR_H
