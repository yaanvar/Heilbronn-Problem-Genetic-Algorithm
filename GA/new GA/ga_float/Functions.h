#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cmath>

#include "Point.h"
#include "Individual.h"

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
    for (int i = 0; i < points_quantity * 2; i += 2) {
        Point t (temp.gens[i], temp.gens[i + 1]);
        result.push_back (t);
    }
    return result;
}


#endif
