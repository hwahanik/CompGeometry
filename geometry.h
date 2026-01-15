#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <cmath>
#include <memory>

// Point in 2D
struct Point {
    double x, y;
};

// Tolerance for the cross product
const double EPSILON = 1e-12;

// Node in the circular doubly linked list.
// Represents a vertex
class Node {
public:
    Point point;
    
    // Shared pointers to the neighbors of this node in the circular linked list
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;

    Node(Point p) : point(p), next(nullptr), prev(nullptr) {}
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

// Calculates the signed area of the polygon 
// A > 0 implies winding is counter clockwise 
// A < 0 implies winding is clockwise => list of vertices needs to be reversed for computing the ear clipping method
double calculate_signed_area(const std::vector<Point>& vertices);

class Triangle {
public:

    // Triangle vertices
    Point a, b, c;

    // Constructor
    Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {} 
    
    // Checks if Point p lies inside or on the Boundary of the Triangle(a, b, c).
    bool is_point_in_triangle(Point p) {
        // Check orientation of P relative to three edges (ab, bc, ca).
        // If P is to the left (or on the line) of all edges, it is inside.
        // Use a tolerance to allow the point to be on the edge.
        bool b1 = outer_product(a, b, p) >= -EPSILON;
        bool b2 = outer_product(b, c, p) >= -EPSILON;
        bool b3 = outer_product(c, a, p) >= -EPSILON;

        return b1 && b2 && b3;
    }
};

#endif