#include "triangulation.h"
#include <iostream>
#include <algorithm> 

// Reminder:  write unit test for this
/// @brief Removes node from Circular Linked List
/// @param node 
/// @return Next node after removed
std::shared_ptr<Node> remove_node_from_list(std::shared_ptr<Node> node) {
    
    if (node == nullptr || node->next == node) return nullptr;

    // Access of weak ptr requires lock
    std::shared_ptr<Node> p = node->prev.lock(); 
    std::shared_ptr<Node> n = node->next;

    p->next = n;
    n->prev = p;
    node->next = nullptr;
    node->prev = nullptr;

    return n;
}

/// @brief Determine if the triangle formed curr and its neighbors is an ear
/// @param curr
/// @return 
bool is_triangle_ear(std::shared_ptr<Node> curr) {

    // Extract curr and neighbors from the Circular Double Linked List
    Point p = curr->prev->point; 
    Point c = curr->point;       
    Point n = curr->next->point; 

    // First check: the vertex must be convex
    if (!is_convex(p, c, n)) return false;

    // Second check: all other polygon vertices must fall outside of triangle, 
    // Equivalently, the segment p - n is contained in the polygon

    std::shared_ptr<Node> iterator = n->next;
    
    // Loop over all remaining points of the polygon
    while (iterator != curr->prev) {
        if (is_point_in_triangle(iterator->point, p, c, n)) {
            return false;
        }
        iterator = iterator->next;
    }

    return true;
}

/// @brief Triangulation algorithm
/// @param points 
/// @return 
std::vector<Triangle> triangulation_algorithm(std::vector<Point>& points) {
    std::vector<Triangle> triangles_output;

    size_t number_points = points.size();
    if (number_points < 3) {
        std::err << "This is not a Polygon" std::endl;
        return {};
    }

    // Step 2: Initialize Circular Doubly Linked List.
    std::shared_ptr<Node> head = std::make_shared<Node>(points[0]);
    std::shared_ptr<Node> curr = head;

    for (size_t i = 1; i < number_points; ++i) {
        auto new_node = std::make_shared<Node>(points[i]);
        curr->next = new_node;
        new_node->prev = curr;
        curr = new_node;
    }

    // Close the Circular Linked List 
    curr->next = head;
    head->prev = curr;

    // Iteration of the Ear Clipping method
    size_t remaining_vertices = number_points;
    std::shared_ptr<Node> iterator = head;
    size_t iterations = 0;

    while (remaining_vertices > 3) {
        bool ear_found = false;
        size_t vertices_checked = 0;

        // Ear check and clipping
        while (vertices_checked < remaining_vertices && iterations < 10000) {
            if (is_ear(iterator)) {

                // Save this triangle and clip the ear
                triangles_output.push_back({iterator->prev->point, iterator->point, iterator->next->point});
                
                // Clip the vertex from the list using the circular linked list
                // (Observe that this is done in constant time ===> For this reason we use a Circular Linked List!)
                // (removal of nodes from Linked Lists is O(1)).
                iterator = remove_node_from_list(iterator);
                
                remaining_vertices--;
                ear_found = true;
                break; 
            }

            // Move to next vertex
            iterator = iterator->next;
            vertices_checked++;
        }

        if (!ear_found) {
            std::cerr << "Error: No ear found in this polygon." << std::endl;
            break;
        }

        iterations++;
    }

    // Last 3 vertices form one triangle.
    if (remaining_vertices == 3) {
        triangles.push_back({iterator->prev->point, iterator->point, iterator->next->point});
    }

    return triangles_output;
}