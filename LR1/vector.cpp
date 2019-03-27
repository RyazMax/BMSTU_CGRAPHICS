#include "vector.h"

double get_delta_x(vector_t a) {
    return a.second.x - a.first.x;
}

double get_delta_y(vector_t a) {
    return a.second.y - a.first.y;
}

double vector_mul(vector_t a, vector_t b) {
    return get_delta_x(a) * get_delta_y(b) - get_delta_x(b) * get_delta_y(a);
}


bool is_intersected(vector_t a, vector_t b) {
    double dxa = get_delta_x(a), dxb = get_delta_x(b);
    double dya = get_delta_y(a), dyb = get_delta_y(b);

    if (dxa == 0 && dxb == 0) return false;
    if (dya == 0 && dyb == 0) return false;
    if (dxa != 0 && dxb == 0 && fabs(dya/dxa  - dyb/dxb) < 1e-6) return false;

    return true;
}

point_t intersect(vector_t a, vector_t b) {
    point_t res;

    double dxa = get_delta_x(a), dxb = get_delta_x(b);
    double dya = get_delta_y(a), dyb = get_delta_y(b);

    if (dxa != 0 && dxb != 0) {
        double k1 = dya / dxa, k2 = dyb / dxb;
        res.x = (b.first.y - a.first.y + a.first.x * k1 - b.first.x * k2) / (k1 - k2);
        res.y = k1 * (res.x - a.first.x) + a.first.y;
    } else if (dxa == 0) {
        res.x  = a.first.x;
        res.y = (dyb / dxb) * (res.x - b.first.x)  + b.first.y;
    } else {
        res.x = b.first.x;
        res.y = (dya / dxa) * (res.x - a.first.x) + a.first.y;
    }

    return res;
}

bool is_points_equal(point_t a, point_t b) {
    return a.x == b.x && a.y == b.y;
}

bool is_on_line(vector_t v, point_t p) {
    return fabs(vector_mul(v, vector_t{v.first, p})) < 1e-6;
}
