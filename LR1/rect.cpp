#include "rect.h"
#include <iostream>

triangle_t get_normalized_tring(triangle_t t, int width, int height, double w, double offsetx, double offsety) {
    triangle_t res;
    res.p1 = get_normalized(t.p1, width, height, w, offsetx, offsety);
    res.p2 = get_normalized(t.p2, width, height, w, offsetx, offsety);
    res.p3 = get_normalized(t.p3, width, height, w, offsetx, offsety);
    return res;
}

rect_t get_normalized_rect(rect_t r, int width, int height, double w, double offsetx, double offsety) {
    rect_t res;
    res.p1 = get_normalized(r.p1, width, height, w, offsetx, offsety);
    res.p2 = get_normalized(r.p2, width, height, w, offsetx, offsety);
    res.p3 = get_normalized(r.p3, width, height, w, offsetx, offsety);
    res.p4 = get_normalized(r.p4, width, height, w, offsetx, offsety);
    return res;
}

void draw_triangle(triangle_t tring, QPainter &painter) {
    painter.drawLine(tring.p1.x, tring.p1.y, tring.p2.x, tring.p2.y);
    painter.drawLine(tring.p2.x, tring.p2.y, tring.p3.x, tring.p3.y);
    painter.drawLine(tring.p1.x, tring.p1.y, tring.p3.x, tring.p3.y);
}

void draw_rect(rect_t rect, QPainter &painter) {
    painter.drawLine(rect.p1.x, rect.p1.y, rect.p2.x, rect.p2.y);
    painter.drawLine(rect.p2.x, rect.p2.y, rect.p3.x, rect.p3.y);
    painter.drawLine(rect.p3.x, rect.p3.y, rect.p4.x, rect.p4.y);
    painter.drawLine(rect.p1.x, rect.p1.y, rect.p4.x, rect.p4.y);
}

void draw_solution(rect_t rect, QPainter &painter) {

    int height = painter.device()->height();
    int width = painter.device()->width();

    triangle_t max_tring = get_max_tring(rect);
    triangle_t min_tring = get_min_tring(rect);
    point_t central = intersect(vector_t{rect.p1, rect.p3}, vector_t{rect.p2, rect.p4});

    double min_x = std::min(rect.p1.x, std::min(rect.p2.x, std::min(rect.p3.x, rect.p4.x)));
    double min_y = std::min(rect.p1.y, std::min(rect.p2.y, std::min(rect.p3.y, rect.p4.y)));

    double max_x = std::max(rect.p1.x, std::max(rect.p2.x, std::max(rect.p3.x, rect.p4.x)));
    double max_y = std::max(rect.p1.y, std::max(rect.p2.y, std::max(rect.p3.y, rect.p4.y)));

    double offsetx = -(max_x + min_x) / 2;
    double offsety = -(max_y + min_y) / 2;

    int border = 80;
    double w = std::min(fabs((height - border)/(max_y - min_y)), fabs((width - border)/(max_x - min_x)));

    rect_t rect_normal = get_normalized_rect(rect, width, height, w, offsetx, offsety);
    triangle_t max_tring_normal = get_normalized_tring(max_tring, width, height, w, offsetx, offsety);
    triangle_t min_tring_normal = get_normalized_tring(min_tring, width, height, w, offsetx, offsety);


    QPen pen(Qt::darkYellow);
    painter.setPen(pen);
    painter.setFont(QFont("Arial", 18));
    painter.drawText(rect_normal.p1.x + 2, rect_normal.p1.y, "(" + QString::number(rect.p1.x, 'f',2) + "; " + QString::number(rect.p1.y, 'f', 2) + ")");
    painter.drawText(rect_normal.p2.x + 2, rect_normal.p2.y, "(" + QString::number(rect.p2.x, 'f',2) + "; " + QString::number(rect.p2.y, 'f', 2) + ")");
    painter.drawText(rect_normal.p3.x + 2, rect_normal.p3.y, "(" + QString::number(rect.p3.x, 'f',2) + "; " + QString::number(rect.p3.y, 'f', 2) + ")");
    painter.drawText(rect_normal.p4.x + 2, rect_normal.p4.y, "(" + QString::number(rect.p4.x, 'f',2) + "; " + QString::number(rect.p4.y, 'f', 2) + ")");

    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    draw_rect(rect_normal, painter);
    painter.drawLine(rect_normal.p1.x, rect_normal.p1.y, rect_normal.p3.x, rect_normal.p3.y);
    painter.drawLine(rect_normal.p2.x, rect_normal.p2.y, rect_normal.p4.x, rect_normal.p4.y);

    // Max
    pen.setColor(Qt::blue);
    pen.setWidth(4);
    painter.setPen(pen);
    draw_triangle(max_tring_normal, painter);

    // Min
    pen.setColor(Qt::green);
    pen.setWidth(4);
    painter.setPen(pen);
    draw_triangle(min_tring_normal, painter);

    point_t central_n = get_normalized(central, width, height, w, offsetx, offsety);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawEllipse(QPoint(central_n.x, central_n.y), 3, 3);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(central_n.x, central_n.y -5, "(" + QString::number(central.x, 'f', 2) + "; " + QString::number(central.y, 'f', 2) + ")");
}

bool is_rect(point_t p1, point_t p2, point_t p3, point_t p4) {
    vector_t first{p1, p2}, second{p2, p3}, third{p3, p4}, fourth{p4, p1};
    if (vector_mul(first, vector_t{p1, p3}) * vector_mul(first, vector_t{p1,p4}) <= 0) {
        return false;
    }
    if (vector_mul(second, vector_t{p2, p1}) * vector_mul(second, vector_t{p2,p4}) <= 0) {
        return false;
    }
    if (vector_mul(third, vector_t{p3, p1}) * vector_mul(third, vector_t{p3,p2}) <= 0) {
        return false;
    }
    if (vector_mul(fourth, vector_t{p4, p2}) * vector_mul(fourth, vector_t{p4,p3}) <= 0) {
        return false;
    }
    return true;
}

double get_square(triangle_t t) {
    double a = sqrt(get_delta_x(vector_t{t.p1, t.p2}) * get_delta_x(vector_t{t.p1, t.p2}) + get_delta_y(vector_t{t.p1, t.p2}) * get_delta_y(vector_t{t.p1, t.p2}));
    double b = sqrt(get_delta_x(vector_t{t.p2, t.p3}) * get_delta_x(vector_t{t.p2, t.p3}) + get_delta_y(vector_t{t.p2, t.p3}) * get_delta_y(vector_t{t.p2, t.p3}));
    double c = sqrt(get_delta_x(vector_t{t.p1, t.p3}) * get_delta_x(vector_t{t.p1, t.p3}) + get_delta_y(vector_t{t.p1, t.p3}) * get_delta_y(vector_t{t.p1, t.p3}));

    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

triangle_t get_min_tring(rect_t rect) {
    point_t central = intersect(vector_t{rect.p1, rect.p3}, vector_t{rect.p2, rect.p4});
    triangle_t res{rect.p1, rect.p2, central};
    double square = get_square(res);
    triangle_t new_triangle{rect.p2, rect.p3, central};
    double new_square = get_square(new_triangle);
    if (new_square < square) {
        res = new_triangle;
        square = new_square;
    }

    new_triangle.p1 = rect.p3, new_triangle.p2 = rect.p4;
    new_square = get_square(new_triangle);
    if (new_square < square) {
        res = new_triangle;
        square = new_square;
    }

    new_triangle.p1 = rect.p1, new_triangle.p2 = rect.p4;
    new_square = get_square(new_triangle);
    if (new_square < square) {
        res = new_triangle;
        square = new_square;
    }
    return res;
}

triangle_t get_max_tring(rect_t rect) {
    point_t central = intersect(vector_t{rect.p1, rect.p3}, vector_t{rect.p2, rect.p4});
    triangle_t res{rect.p1, rect.p2, central};
    double square = get_square(res);
    triangle_t new_triangle{rect.p2, rect.p3, central};
    double new_square = get_square(new_triangle);
    if (new_square > square) {
        res = new_triangle;
        square = new_square;
    }

    new_triangle.p1 = rect.p3, new_triangle.p2 = rect.p4;
    new_square = get_square(new_triangle);
    if (new_square > square) {
        res = new_triangle;
        square = new_square;
    }

    new_triangle.p1 = rect.p1, new_triangle.p2 = rect.p4;
    new_square = get_square(new_triangle);
    if (new_square > square) {
        res = new_triangle;
        square = new_square;
    }
    return res;
}

rect_t get_min_sub(std::vector<point_t> points) {
    int len = points.size();
    double min_square = -1;
    rect_t best_rect{0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < len; ++i) {
        point_t p1 = points[i];
        for (int j = 0; j < len; ++j)  {
            point_t p2 = points[j];
            if (is_points_equal(p1, p2)) continue;
            for (int q = 0; q < len; ++q) {
                point_t p3 = points[q];
                if (is_on_line(vector_t{p1, p2}, p3)) continue;
                for (int k = 0; k < len; ++k) {
                    point_t p4 = points[k];
                    if (!is_rect(p1, p2, p3, p4)) continue;
                    rect_t cur_rect{p1, p2, p3, p4};
                    double sub_square = get_square(get_max_tring(cur_rect)) - get_square(get_min_tring(cur_rect));
                    if (min_square == -1 || sub_square < min_square) {
                        best_rect = cur_rect;
                        min_square = sub_square;
                    }
                }
            }
        }
    }
    return best_rect;
}

point_t get_normalized(point_t p, int width, int height, double w, double offsetx, double offsety) {
    point_t res { (p.x  + offsetx) * w + width/2 , height / 2 - ((p.y + offsety) * w) };
    return res;
}
