#include "reader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Point> read_csv(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return points;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string segment;
        double x = 0, y = 0;

        // Parse X (delimited by comma)
        if (std::getline(ss, segment, ',')) {
            try { x = std::stod(segment); } catch (...) { continue; }
        }
        
        // Parse Y (remainder of line)
        if (std::getline(ss, segment)) {
             try { y = std::stod(segment); } catch (...) { continue; }
        }

        points.push_back({x, y});
    }
    return points;
}

// Building 
void generate_test_csv(const std::string& filename) {
    std::ofstream file(filename);
    // Simple concave shape
    file << "0,0\n";
    file << "4,0\n";
    file << "4,4\n";
    file << "2,2\n"; 
    file << "0,4\n";
    file.close();
}