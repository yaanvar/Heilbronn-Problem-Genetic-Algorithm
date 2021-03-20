#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <cmath>

#include "Point.h"

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
    AB = ((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));
    ab = sqrt(AB);
    BC = ((second.x - third.x) * (second.x - third.x) + (second.y - third.y) * (second.y - third.y));
    bc = sqrt(BC);
    AC = ((first.x - third.x) * (first.x - third.x) + (first.y - third.y) * (first.y - third.y));
    ac = sqrt(AC);
    p = (ab + ac + bc) / 2;
    S = sqrt((p - ab) * (p - ac) * (p - bc) * p);
    return S;
}

std::vector <Point> transform (Individual temp, double a, double b, int points_quantity) {
    std::vector <Point> result;
    int size_of_point = temp.str_gens.size() / points_quantity;
    for (int i = 0; i < temp.gens.size(); i += size_of_point) {
        int x1, y1;
        std::string s = temp.str_gens.substr (i, size_of_point);
        std::string sx = s.substr (0, size_of_point / 2);
        std::string sy = s.substr (size_of_point / 2, size_of_point / 2);
        x1 = binary_to_decimal (sx);
        y1 = binary_to_decimal (sy);
        double x = make_float (x1, a, b, size_of_point / 2);
        double y = make_float (y1, a, b, size_of_point / 2);
        Point t (x, y);
        result.push_back (t);
    }
    return result;
}


#endif
