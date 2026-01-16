#include "geometry.h"

double outer_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}

bool is_convex_and_not_collinear(Point prev, Point curr, Point next) {
    return outer_product(prev, curr, next) > EPSILON;
}

double calculate_signed_area(const std::vector<Point>& polygon){
    size_t num_vertices = polygon.size();
    double area = 0.0;

    // The Shoelace loop
    for (size_t i = 0; i < num_vertices; ++i) {
        int j = (i + 1) % num_vertices;
        area += (polygon[i].x * polygon[j].y);
        area -= (polygon[j].x * polygon[i].y);
    }

    return area / 2.0;
}