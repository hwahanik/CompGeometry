#include <iostream>
#include "geometry.h"
#include "triangulation.h"
#include "reader.h"
#include <algorithm>

int main(int argc, char* argv[]) {

    // 1. Verify that argument is valid
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1; // Return error code
    }

    std::string filename = argv[1];
        
    // Read csv
    std::vector<Point> polygon = read_csv(filename);
    if (polygon.empty()) {
        std::cout << "Polygon is empty" << std::endl;
        return 1;
    }

    std::cout << "Successfully read from CSV " << polygon.size() << " vertices.\n";

    // Step 1: Compute Area from the Shoelace formula, provides orientation as well
    // According to the literature 
    double area = calculate_signed_area(polygon);

    // Ear clipping requires counter-clockwise winding (ccw)
    // If area < 0, collection of points must be reversed
    if (area < 0) {
        std::reverse(polygon.begin(), polygon.end());
        area = -area; 
    }

    // Step 2: Polygon triangulation computation
    const std::vector<Triangle> triangles = triangulation_algorithm(polygon);

    // Output
    std::cout << "Total area is = " << area << std::endl;
    std::cout << "List of triangles " << area << std::endl;

    // List of triangles 
    for(size_t i=0; i < triangles.size(); ++i){
        Triangle t = triangles[i];
        std::cout << "(" << t.p1.x << " , " << t.p1.y << ")" << "  ,  " << "(" << t.p2.x << " , " << t.p2.y << ")" << "  ,  " << "(" << t.p3.x << " , " << t.p3.y << ")" << std::endl;
    }

    return 0;
}