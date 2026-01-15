#include "triangulation.h"
#include <iostream>
#include <algorithm> 

// Reminder:  write unit test for this
/// @brief Removes node from Circular Linked List
/// @param node 
/// @return Next node after removed
std::shared_ptr<Node> remove_node_from_list(std::shared_ptr<Node> node) {
    
    if (node == nullptr || node->next == node) return nullptr;

    std::shared_ptr<Node> p = node->prev;
    std::shared_ptr<Node> n = node->next;

    p->next = n;
    n->prev = p;
    node->next = nullptr;
    node->prev = nullptr;

    return n;
}

/// @brief Determine if the triangle formed by the points curr and its neighbors (prev and next) forms an ear
/// @param curr
/// @return 
bool is_triangle_ear(std::shared_ptr<Node> curr) {

    // Extract curr and neighbors from the Circular Double Linked List
    Point p = curr->prev->point; 
    Point c = curr->point;       
    Point n = curr->next->point; 

    // Check 1: the vertex must be convex
    if (!is_convex(p, c, n)) return false;

    // Check 2: all other polygon vertices must fall outside of triangle, 
    
    // (Both check 1 and check 2 imply that the segment (p - n) is contained in the polygon)

    std::shared_ptr<Node> iter = curr->next->next;
    // Loop over all remaining points of the polygon
    while (iter != curr->prev) {
        if (is_point_in_triangle(iter->point, p, c, n)) {
            return false;
        }
        it = it->next;
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
        std::cout << "This is not a Polygon!  Check your csv file" << std::endl;
        return {};
    }

    // Step 2: Initialize Circular Doubly Linked List.
    std::shared_ptr<Node> head = std::make_shared<Node>(points[0]);
    std::shared_ptr<Node> curr = head;

    for (size_t i = 1; i < number_points - 1; ++i) {
        auto new_node = std::make_shared<Node>(points[i]);
        curr->next = new_node;
        new_node->prev = curr;
        curr = new_node;
    }

    // Close the Circular Linked List 
    curr->next = head;
    head->prev = curr;

    // Ear Clipping method
    size_t remaining_vertices = number_points;
    std::shared_ptr<Node> iter = head;
    size_t iterations = 0;

    while (remaining_vertices > 3) {
        bool ear_found = false;
        size_t vertices_checked = 0;

        // Ear check and clipping, limit iterations in case cycles in the polygon vertices are present
        while (vertices_checked < remaining_vertices && iterations < 10000) {
            if (is_triangle_ear(iter)) {

                // Save this triangle and clip the ear
                triangles_output.push_back({iter->prev->point, iter->point, iter->next->point});
                
                // Clip the vertex from the list using the Circular Linked List
                // (Observe that this is done in constant time ===> For this reason we use a Circular Linked List!)
                // (removal of nodes from Linked Lists is O(1)).
                iter = remove_node_from_list(iter);
                
                remaining_vertices--;
                ear_found = true;
                break; 
            }

            // Move to next vertex
            iter = iter->next;
            vertices_checked++;
        }

        if (!ear_found) {
            std::cout << "Error: No ear found in this polygon." << std::endl;
            break;
        }

        iterations++;
    }

    // Last 3 vertices form one triangle.
    if (remaining_vertices == 3) {
        triangles_output.push_back({iter->prev->point, iter->point, iter->next->point});
    }

    // Missing method for freeing all references of shared pointers.
    cleanup_shared_pointers(iter);

    return triangles_output;
}

void cleanup_shared_pointers(std::shared<Node> node){


}