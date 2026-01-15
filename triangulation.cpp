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

/// @brief Clean up of shared pointers to avoid memory leaks
/// @param head 
void cleanup_circular_linked_list(std::shared_ptr<Node> head){ 

    if(!head) return;
    auto iterator = head->next; 
    
    head->next = nullptr;
    head->prev = nullptr;

    while(iterator != nullptr && iterator != head){
        auto next_node = iterator->next;
        iterator->next = nullptr;
        iterator->prev = nullptr;
        iterator = next_node;
    }
    
    return;
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
        Triangle t(p, c, n);
        if (t.is_point_in_triangle(iter->point)) {
            return false;
        }
        iter = iter->next;
    }

    return true;
}

/// @brief Triangulation algorithm
/// @param The polygon 
/// @return 
std::vector<Triangle> triangulation_algorithm(std::vector<Point>& polygon) {
    std::vector<Triangle> triangles_output;

    size_t number_points = polygon.size();
    if (number_points < 3) {
        std::cout << "This is not a Polygon!  Check csv file" << std::endl;
        return {};
    }

    // Initialize Circular Doubly Linked List.
    std::shared_ptr<Node> head = std::make_shared<Node>(polygon[0]);
    std::shared_ptr<Node> curr = head;

    for (size_t i = 1; i < number_points - 1; ++i) {
        auto new_node = std::make_shared<Node>(polygon[i]);
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

    std::cout << std::endl;
    std::cout << "Calculating triangulation..." << std::endl;
    std::cout << std::endl;

    while (remaining_vertices > 3) {
        bool ear_found = false;
        size_t vertices_checked = 0;

        // Ear check and clipping, limit iterations in case cycles in the polygon vertices are present
        while (vertices_checked < remaining_vertices && iterations < 10000) {
            if (is_triangle_ear(iter)) {

                // Save this triangle 
                triangles_output.push_back(Triangle(iter->prev->point, iter->point, iter->next->point));
                
                // Clip the ear:
                //  Clip the vertex from the list using the Circular Linked List
                //  (Observe that this is done in constant time ===> For this reason we use a Circular Linked List!)
                //  (removal of nodes from Linked Lists is O(1)).
                iter = remove_node_from_list(iter);
                
                remaining_vertices--;
                ear_found = true;
                break; 
            }

            iter = iter->next;
            vertices_checked++;
        }

        if (!ear_found) {
            std::cout << "Error: No ear found for the residual polygon" << std::endl;
            std::cout << "Remaining vertices of residual polygon = " << remaining_vertices << std::endl;
            break;
        }

        iterations++;
    }

    // Last 3 vertices form one triangle.
    if (remaining_vertices == 3) {
        triangles_output.push_back(Triangle(iter->prev->point, iter->point, iter->next->point));
    }

    cleanup_circular_linked_list(iter);

    return triangles_output;
}
