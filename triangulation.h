#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include "geometry.h"

// Handles clockwise correction.
// Core function: Takes a list of points and returns {Area, List of Triangles}.
std::vector<Triangle> triangulation_algorithm(std::vector<Point>& points);

// Clean up of circular linked list to avoid memory leaks
void cleanup_circular_linked_list(std::shared_ptr<Node> head);
#endif