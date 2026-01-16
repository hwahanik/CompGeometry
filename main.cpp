#include <iostream>
#include "geometry.h"
#include "triangulation.h"
#include "reader.h"
#include <algorithm>
#include <iomanip>

int main(int argc, char* argv[]) {

    // Verify that user's input argument is valid
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
        
    // Read csv
    std::vector<Point> polygon = read_csv(filename);
    if (polygon.empty()) {
        std::cout << "Polygon is empty" << std::endl;
        return 1;
    }

    std::cout << "Successfully read from the CSV file " << polygon.size() << " vertices.\n";

    // Compute Area from the Shoelace formula, provides orientation as well
    double area = calculate_signed_area(polygon);

    // Ear clipping requires counter-clockwise winding order (ccw)
    // If area is negative we reverse the polygon's vertices
    if (area < 0) {
        std::reverse(polygon.begin(), polygon.end());
        std::cout << "Polygon has clockwise orientation, reversing direction to counter-clockwise" << std::endl;
        std::cout << "Signed aread = " << area << std::endl;
        area = -area; 
    }

    // Polygon triangulation computation
    const std::vector<Triangle> triangles = triangulation_algorithm(polygon);

    if(triangles.size() == 0){
        std::cout << "No triangles found!" << std::endl;
        return 1;
    }

    // Output
    std::cout << "Total area is = " << std::setprecision(17) << area << std::endl;
    std::cout << "List of triangles: " << std::endl;
    std::cout << std::setprecision(6) << std::endl;

    // Printing the list of triangles 
    for(size_t i=0; i < triangles.size(); ++i){
        Triangle t = triangles[i];
        std::cout << "(" << t.a.x << " , " << t.a.y << ")" << "  ,  " << "(" << t.b.x << " , " << t.b.y << ")" << "  ,  " << "(" << t.c.x << " , " << t.c.y << ")" << std::endl;
    }

    return 0;
}