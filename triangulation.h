#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include "geometry.h"

// Handles clockwise correction.
// Core function: Takes a list of points and returns {Area, List of Triangles}.
std::vector<Triangle> triangulation_algorithm(std::vector<Point>& points);

#endif