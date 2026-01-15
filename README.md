##
## CODE FOR EAR CLIPPING ALGORITHM
## HELMUT WAHANIK
##

## Instructions:

1.  Fork the repository from Github

2.  In the Linux command line simply compile using:

        g++ -std=c++17 -O3 -Wall -o cgeom_algorithm main.cpp reader.cpp geometry.cpp triangulation.cpp

3.  Run as ./cgeom_algorithm concave_poly.csv

4.  Please find included here the simple cases of 

    "simple_concave_poly_ccw.csv" ==>  Answer equivalent to simple_concave, but NO warning will be printed as this Polygon already has clock-wise orientation.

    "two_points.csv" ==> An error should be displayed.

