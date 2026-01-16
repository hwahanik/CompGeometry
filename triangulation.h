#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include "geometry.h"

// Handles clockwise correction.

/// @brief Calculates triangles of a Polygon using the Ear Clipping method
/// @param points 
/// @return List of Triangles or returns empty in case no Triangle was found.
std::vector<Triangle> triangulation_algorithm(std::vector<Point>& points);

/// @brief Clean up of shared pointers to avoid memory leaks
/// @param head 
void cleanup_circular_linked_list(std::shared_ptr<Node> head);

/// @brief Removes node from Circular Linked List
/// @param node 
/// @return Pointer to Next node after the input is removed for the CLL
std::shared_ptr<Node> remove_node_from_list(std::shared_ptr<Node> node);

/// @brief Determine if the triangle formed by the points curr and its neighbors (prev and next) forms an ear
/// @param curr => current node
/// @return Whether triangle (prev, curr, next) forms an ear
bool is_triangle_ear(std::shared_ptr<Node> curr);

#endif