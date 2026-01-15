#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <cmath>

// Tolerance for the cross product
const double EPSILON = 1e-9;

// Node in the circular doubly linked list.
// Represents a vertex
class Node {
public:
    Point point;
    
    // Shared pointers to the neighbors of this node in the circular linked list
    std::shared_ptr<Node> next;

    // Use weak ptr for prev to avoid memory leaks due to double count of ownership
    std::weak_ptr<Node> prev;

    Node(Point p) : point(p), next(nullptr), prev(nullptr) {}
};

// Point in 2D
struct Point {
    double x, y;
}

struct Triangle {
    Point p1, p2, p3;
};

// Auxiliary functions
bool is_zero(double val);

// Note: Outer product or 2D Cross product is given by the single 
// scalar value defined 
// as:\(\mathbf{A}\times \mathbf{B}=A_{x}B_{y}-A_{y}B_{x}\)
// The sign indicates the orientation of the vectors

// Here A = (b.x - a.x, b.y - a.y)
// Here B = (c.x - b.x, c.y - b.y)
double outer_product(Point a, Point b, Point c);

// Check if current vertex "curr" forms a convex angle (angle < Pi).
// assuming orientation of polygon is counter clockwise.
bool is_convex(Point prev, Point curr, Point next);

// Checks if Point p lies inside or on the Boundary of the Triangle(a, b, c).
bool is_point_in_triangle(Point p, Point a, Point b, Point c);

// Calculates the signed area of the polygon 
// A > 0 implies winding is counter clockwise 
// A < 0 implies winding is clockwise => list of vertices needs to be reversed for computing the ear clipping method
double calculate_signed_area(const std::vector<Point>& vertices);

#endif