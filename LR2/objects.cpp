#include "objects.h"

point_t point(double x, double y) {
    return point_t{std::vector<double>{x, y, 1}};
}

linear_figure_t create_line(point_t a, point_t b) {
    linear_figure_t res;
    res.edges.push_back(edge_t{a, b});
    return res;
}

linear_figure_t create_triangle(point_t a, point_t b, point_t c) {
    linear_figure_t res;
    res.edges.push_back(edge_t{a, b});
    res.edges.push_back(edge_t{a, c});
    res.edges.push_back(edge_t{b, c});
    return res;
}

linear_figure_t create_ellips(point_t a, point_t b, int points) {
    linear_figure_t res;

    double al = (b.cords[0] - a.cords[0]) / 2;
    double bl = (b.cords[1] - a.cords[1]) / 2;

    double xc = (b.cords[0] + a.cords[0]) / 2;
    double yc = (b.cords[1] + a.cords[1]) / 2;

    double step = 2 * M_PI / points;
    double angle = 0;

    point_t prev = point(xc + cos(angle) *al, yc + sin(angle) * bl);
    angle += step;
    for (int i = 0; i < points; ++i) {
        double x = xc + cos(angle) * al;
        double y = yc + sin(angle) * bl;
        point_t cur = point(x, y);
        res.edges.push_back({prev, point(x, y)});
        prev = cur;
        angle += step;
    }
    return res;
}

object_t create_bun() {
    object_t res;

    point_t pc  = point(300, 300);

    res.linear_figures.push_back(create_line(point(350, 300), point(350, 320))); // Волосы 1
    res.linear_figures.push_back(create_line(point(345, 300.3), point(340, 320))); // Волосы 2
    res.linear_figures.push_back(create_line(point(355, 300.3), point(360, 320))); // Волосы 3
    res.linear_figures.push_back(create_line(point(340, 301.1), point(330, 320))); // Волосы 4
    res.linear_figures.push_back(create_line(point(360, 301.1), point(370, 320))); // Волосы 5

    res.linear_figures.push_back(create_triangle(point(350, 340), point(340, 360), point(360, 360))); // Нос
    res.linear_figures.push_back(create_triangle(point(350, 380), point(330, 370), point(370, 370))); // Рот

    res.linear_figures.push_back(create_ellips(point(320, 330), point(340, 340), 1000)); // Глаз 1
    res.linear_figures.push_back(create_ellips(point(380, 330), point(360, 340), 1000)); // Глаз 2
    res.linear_figures.push_back(create_ellips(pc, point(400, 400), 1000)); // Тело

    res.center = point(350, 350);

    return res;
}

void draw_edge(edge_t e, QPainter &painter)
{
    int height = painter.device()->height();
    painter.drawLine(e.p1.cords[0], height - e.p1.cords[1], e.p2.cords[0], height - e.p2.cords[1]);
}

void draw_linear(linear_figure_t f, QPainter &painter)
{
    for (uint i = 0; i < f.edges.size(); ++i) {
        draw_edge(f.edges[i], painter);
    }
}

void draw_points(point_figure_t f, QPainter &painter)
{
    for (uint i = 0; i < f.points.size(); ++i) {
        draw_point(f.points[i], painter);
    }
}

void draw_object(object_t o, QPainter &painter)
{
    for (uint i = 0; i < o.linear_figures.size(); ++i) {
        draw_linear(o.linear_figures[i], painter);
    }

    for (uint i = 0; i < o.point_figures.size(); ++i) {
        draw_points(o.point_figures[i], painter);
    }
}

void draw_point(point_t p, QPainter &painter)
{
    painter.drawPoint(p.cords[0], p.cords[1]);
}

point_t move_point(point_t p, double dx, double dy)
{
    std::vector<std::vector<double>> matrix;
    matrix.push_back(std::vector<double>{1, 0, 0});
    matrix.push_back(std::vector<double>{0, 1, 0});
    matrix.push_back(std::vector<double>{dx, dy, 1});
    return point_t{mul(p.cords, matrix)};
}

edge_t move_edge(edge_t e, double dx, double dy)
{
    return edge_t{move_point(e.p1, dx, dy), move_point(e.p2, dx, dy)};
}

linear_figure_t move_linear(linear_figure_t f, double dx, double dy)
{
    linear_figure_t res;
    for (uint i = 0; i < f.edges.size(); ++i) {
        res.edges.push_back(move_edge(f.edges[i], dx, dy));
    }
    return res;
}

point_figure_t move_points(point_figure_t f, double dx, double dy)
{
    point_figure_t res;
    for (uint i = 0; i < f.points.size(); ++i) {
        res.points.push_back(move_point(f.points[i], dx, dy));
    }
    return res;
}

object_t move_object(object_t o, double dx, double dy)
{
    object_t res;
    for (uint i = 0; i < o.linear_figures.size(); ++i) {
        res.linear_figures.push_back(move_linear(o.linear_figures[i], dx, dy));
    }

    for (uint i = 0; i < o.point_figures.size(); ++i) {
        res.point_figures.push_back(move_points(o.point_figures[i], dx, dy));
    }

    res.center = move_point(o.center, dx, dy);
    return res;
}

point_t scale_point_c(point_t p, double kx, double ky)
{
    std::vector<std::vector<double>> matrix;
    matrix.push_back(std::vector<double>{kx, 0, 0});
    matrix.push_back(std::vector<double>{0, ky, 0});
    matrix.push_back(std::vector<double>{0, 0, 1});
    return point_t{mul(p.cords, matrix)};
}

point_t scale_point(point_t p, double kx, double ky, double xc, double yc)
{
    return move_point(scale_point_c(move_point(p, -xc, -yc), kx, ky), xc, yc);

}

edge_t scale_edge(edge_t e, double kx, double ky, double xc, double yc)
{
    edge_t res;
    res.p1 = scale_point(e.p1, kx, ky, xc, yc);
    res.p2 = scale_point(e.p2, kx, ky, xc, yc);
    return res;
}

linear_figure_t scale_linear(linear_figure_t f, double kx, double ky, double xc, double yc)
{
    linear_figure_t res;
    for (int i = 0; i < f.edges.size(); ++i) {
        res.edges.push_back(scale_edge(f.edges[i], kx, ky, xc, yc));
    }
    return res;
}

point_figure_t scale_points(point_figure_t f, double kx, double ky, double xc, double yc)
{
    point_figure_t res;
    for (int i = 0; i < f.points.size(); ++i) {
        res.points.push_back(scale_point(f.points[i], kx, ky, xc, yc));
    }
    return res;
}

object_t scale_object(object_t o, double kx, double ky, double xc, double yc)
{
    object_t res;
    for (uint i = 0; i < o.linear_figures.size(); ++i) {
        res.linear_figures.push_back(scale_linear(o.linear_figures[i], kx, ky, xc, yc));
    }

    for (uint i = 0; i < o.point_figures.size(); ++i) {
        res.point_figures.push_back(scale_points(o.point_figures[i], kx, ky, xc, yc));
    }

    res.center = scale_point(o.center, kx, ky, xc, yc);
    return res;
}

point_t rotate_point_c(point_t p, double angle)
{
    std::vector<std::vector<double>> matrix;
    matrix.push_back(std::vector<double>{cos(angle), -sin(angle), 0});
    matrix.push_back(std::vector<double>{sin(angle), cos(angle), 0});
    matrix.push_back(std::vector<double>{0, 0, 1});
    return point_t{mul(p.cords, matrix)};
}

point_t rotate_point(point_t p, double angle, double xc, double yc)
{
    return move_point(rotate_point_c(move_point(p, -xc, -yc), angle), xc, yc);
}

edge_t rotate_edge(edge_t e, double angle, double xc, double yc)
{
    edge_t res;
    res.p1 = rotate_point(e.p1, angle, xc, yc);
    res.p2 = rotate_point(e.p2, angle, xc, yc);
    return res;
}

linear_figure_t rotate_linear(linear_figure_t f, double angle, double xc, double yc)
{
    linear_figure_t res;
    for (int i = 0; i < f.edges.size(); ++i) {
        res.edges.push_back(rotate_edge(f.edges[i], angle, xc, yc));
    }
    return res;
}

point_figure_t rotate_points(point_figure_t f, double angle, double xc, double yc)
{
    point_figure_t res;
    for (int i = 0; i < f.points.size(); ++i) {
        res.points.push_back(rotate_point(f.points[i], angle, xc, yc));
    }
    return res;
}

object_t rotate_object(object_t o, double angle, double xc, double yc)
{
    object_t res;
    for (uint i = 0; i < o.linear_figures.size(); ++i) {
        res.linear_figures.push_back(rotate_linear(o.linear_figures[i], angle, xc, yc));
    }

    for (uint i = 0; i < o.point_figures.size(); ++i) {
        res.point_figures.push_back(rotate_points(o.point_figures[i], angle, xc, yc));
    }

    res.center = rotate_point(o.center, angle, xc, yc);
    return res;
}
