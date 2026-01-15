#ifndef CSV_READER_H
#define CSV_READER_H

#include <vector>
#include <string>
#include "geometry.h"

// Reads a CSV file with vertices
std::vector<Point> read_csv(const std::string& filename);

#endif