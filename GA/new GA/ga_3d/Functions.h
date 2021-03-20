#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cmath>

#include "Point.h"
#include "Individual.h"

int binary_to_decimal (std::string str_gens) {
    return std::stoi(str_gens, 0, 2);
}

double make_float (long long point_int, double a, double b, int size_of_point) {
    double h = (b - a) / (pow (2, size_of_point) - 1.);
    double result = a + point_int * h;
    return result;
}

double triangle_area (Point first, Point second, Point third) {
    double AB, BC, AC, ab, bc, ac, p, S;
    AB = ((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y) + (first.z - second.z) * (first.z - second.z));
    ab = sqrt(AB);
    BC = ((second.x - third.x) * (second.x - third.x) + (second.y - third.y) * (second.y - third.y) + (second.z - third.z) * (second.z - third.z));
    bc = sqrt(BC);
    AC = ((first.x - third.x) * (first.x - third.x) + (first.y - third.y) * (first.y - third.y) + (first.z - third.z) * (first.z - third.z));
    ac = sqrt(AC);
    p = (ab + ac + bc) / 2;
    S = sqrt((p - ab) * (p - ac) * (p - bc) * p);
    return S;
}

std::vector <Point> transform (Individual temp, double a, double b, int points_quantity) {
    std::vector <Point> result;
    int size_of_point = temp.str_gens.size() / points_quantity;
    for (int i = 0; i < temp.str_gens.size(); i += size_of_point) {
        long long x1, y1, z1;
        std::string s = temp.str_gens.substr (i, size_of_point);
        std::string sx = s.substr (0, size_of_point / 3);
        std::string sy = s.substr (size_of_point / 3, size_of_point / 3);
        std::string sz = s.substr (2 * size_of_point / 3, size_of_point / 3);
        x1 = binary_to_decimal (sx);
        y1 = binary_to_decimal (sy);
        z1 = binary_to_decimal (sz);
        double x = make_float (x1, a, b, size_of_point / 3);
        double y = make_float (y1, a, b, size_of_point / 3);
        double z = make_float (z1, a, b, size_of_point / 3);
        Point t (x, y, z);
        result.push_back (t);
    }
    return result;
}


#endif
