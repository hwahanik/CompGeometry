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

        // Parse X (delimited by comma in the csv file)
        if (std::getline(ss, segment, ',')) {
            try { x = std::stod(segment); } catch (...) { continue; }
        }
        
        // Parse Y (remainder of the line in the csv file)
        if (std::getline(ss, segment)) {
             try { y = std::stod(segment); } catch (...) { continue; }
        }

        points.push_back({x, y});
    }

    return points;
}