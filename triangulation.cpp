#include "triangulation.h"
#include <iostream>
#include <algorithm> 

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

// Find if triangle is ear
bool is_triangle_ear(std::shared_ptr<Node> curr) {

    // Extract curr and neighbors from the Circular Double Linked List
    Point p = curr->prev->point; 
    Point c = curr->point;       
    Point n = curr->next->point; 

    // The vertex must be convex and points should not be collinear
    if (!is_convex_and_not_collinear(p, c, n)) return false;

    // Second check: all other polygon vertices must fall outside of the triangle, 
    // (Observe that these conditions being valid will imply that the segment 
    // (pn) is contained in the polygon)

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

/// @brief Calculates triangles of a Polygon using the Ear Clipping method
/// @param points 
/// @return List of Triangles or returns empty in case no Triangle is found
std::vector<Triangle> triangulation_algorithm(std::vector<Point>& polygon) {

    std::vector<Triangle> triangles_output;

    size_t number_points = polygon.size();
    if (number_points < 3) {
        std::cout << "This is not a Polygon!  Check the csv file" << std::endl;
        return {};
    }

    // Initialize Circular Doubly Linked list.  
    // This data structure was selected given that insertion and deletion are O(1)
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
    std::cout << "Running Triangulation algorithm..." << std::endl;
    std::cout << std::endl;

    while (remaining_vertices > 3) {
        bool ear_found = false;
        size_t vertices_checked = 0;

        // Ear clipping, limit iterations for safety 
        while (vertices_checked < remaining_vertices && iterations < 10000) {
            if (is_triangle_ear(iter)) {

                // Save this triangle 
                triangles_output.push_back(Triangle(iter->prev->point, iter->point, iter->next->point));
                
                // Clip the ear:
                //  Clip the vertex from the list using the Circular Linked List
                //  (Observe that this is done in constant time ===> For this reason we use a Circular Linked List!)
                iter = remove_node_from_list(iter);
                
                remaining_vertices--;
                ear_found = true;
                break; 
            }

            iter = iter->next;
            vertices_checked++;
        }

        // This can only happen it the polygon is not simple, i.e. has self-intersections or holes.
        if (!ear_found) {
            std::cout << "Error: No ear found for a residual polygon.  Polygon may be non-simple." << std::endl;
            std::cout << "Remaining vertices in residual polygon = " << remaining_vertices << std::endl;
            break;
        }

        iterations++;
    }

    // If last 3 vertices remain, if collinear will not form a triangle.
    if (remaining_vertices == 3){
        auto c = std::abs(outer_product(iter->prev->point, iter->point, iter->next->point));

        // If c < EPSILON the three points lie on a line.
        if(c > EPSILON){
            triangles_output.push_back(Triangle(iter->prev->point, iter->point, iter->next->point));
        }
    }

    // Method to avoid memory leaks from any remaining shared pointer 
    cleanup_circular_linked_list(iter);

    return triangles_output;
}
