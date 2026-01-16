#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <cmath>
#include <memory>

// Point in 2D
struct Point {
    double x, y;
};

const double EPSILON = 1e-12;

// Point node in the Circular Double Linked list.
class Node {
public:
    Point point;

    // Shared pointers to the neighbors 
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;

    Node(Point p) : point(p), next(nullptr), prev(nullptr) {}
};

// Note: Outer product or 2D Cross product is given by 
// \(\mathbf{A}\times \mathbf{B}=A_{x}B_{y}-A_{y}B_{x}\)
// The sign indicates the orientation of the vectors (for ccw points).
// Outer product > 0 => points form convex angle (< Pi).

// Here A = (b.x - a.x, b.y - a.y)
// Here B = (c.x - b.x, c.y - b.y)

/// @brief Input points of the outer product
/// @param a 
/// @param b 
/// @param c 
/// @return The outer product between the segments ab and bc
double outer_product(Point a, Point b, Point c);


// Check if current vertex "curr" forms a convex angle (angle < Pi).
// assuming orientation of polygon is counter-clockwise.
// Also checks for collinearity at the same time, which we want to avoid 
// (collinear points will not form an ear).

/// @brief Check if current vertex "curr" forms a convex angle (angle < Pi).
/// @param prev
/// @param curr 
/// @param next 
/// @return Whether points centered at curr form convex angle, and points are not collinear
bool is_convex_and_not_collinear(Point prev, Point curr, Point next);

/// @brief Classic Shoelace formula for the calculation of signed area using the winding order
/// @param vertices 
/// @return 
// area > 0 implies winding is counter clockwise 
// area < 0 implies winding is clockwise => list of vertices needs to be reversed for computing the ear clipping method
double calculate_signed_area(const std::vector<Point>& vertices);


class Triangle {
public:
    // Triangle vertices
    Point a, b, c;

    // Constructor
    Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {} 

    /// @brief Method verifies if Point p lies inside or on the Boundary of the Triangle(a, b, c).
    /// Check orientation of P relative to three edges (ab, bc, ca):
    ///    =>If P is to the left (or on the line) of all edges, it is inside of the triangle.
    /// @param p 
    /// @return whether point is in Triangle
    bool is_point_in_triangle(Point p) {        
        // Small tolerance allows point to be on the edge.
        bool b1 = outer_product(a, b, p) >= -EPSILON;
        bool b2 = outer_product(b, c, p) >= -EPSILON;
        bool b3 = outer_product(c, a, p) >= -EPSILON;
        return b1 && b2 && b3;
    }
};

#endif