#include "geometry.h"

bool is_zero(double val) {
    return std::abs(val) < EPSILON;
}

double outer_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}

// The condition > EPSILON prevents collinear segments
bool is_convex(Point prev, Point curr, Point next) {
    return outer_product(prev, curr, next) > EPSILON;
}

// Unit test for this is missing
bool is_point_in_triangle(Point p, Point a, Point b, Point c) {
    // Check orientation of P relative to three edges (AB, BC, CA).
    // If P is to the left (or on the line) of all edges, it is inside.
    // Use a tolerance to allow the point to be on the edge.
    bool b1 = outer_product(a, b, p) >= -EPSILON;
    bool b2 = outer_product(b, c, p) >= -EPSILON;
    bool b3 = outer_product(c, a, p) >= -EPSILON;

    return b1 && b2 && b3;
}

// Unit test for this is missing
// Classic Shoelace formula for the calculation of signed area using the winding number
double calculate_signed_area(const std::vector<Point>& polygon){
    size_t num_vertices = polygon.size();
    double area = 0.0;

    for (size_t i = 0; i < num_vertices; ++i) {
        int j = (i + 1) % num_vertices;
        area += (polygon[i].x * polygon[j].y);
        area -= (polygon[j].x * polygon[i].y);
    }

    return area / 2.0;
}