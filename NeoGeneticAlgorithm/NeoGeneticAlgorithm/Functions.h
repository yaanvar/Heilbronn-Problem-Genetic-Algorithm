//
//  Functions.h
//  NeoGeneticAlgorithm
//
//  Created by Anvar Rahimov on 02.04.2022.
//

#ifndef Functions_h
#define Functions_h

#include <iostream>
#include <cmath>

#include "Point.h"
#include "Individe.h"

int binary_to_decimal(std::string str_gens) {
    return std::stoi(str_gens, 0, 2);
}

double make_float(long long point_int, long double a, long double b, int size_of_point) {
    long double h = (b - a) / (pow(2, size_of_point) - 1.);
    long double result = a + point_int * h;
    return result;
}

long double triangle_area(Point first, Point second, Point third) {
    long double AB, BC, AC, ab, bc, ac, p, S;
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

std::vector <Point> transform(Individe temp, long double a, long double b, int points_quantity) {
    std::vector <Point> result;
    int size_of_point = temp.str_gens.size() / points_quantity;
    for(int i = 0; i < temp.str_gens.size(); i += size_of_point) {
        long long x1, y1;
        std::string s = temp.str_gens.substr(i, size_of_point);
        std::string sx = s.substr(0, size_of_point / 2);
        std::string sy = s.substr(size_of_point / 2, size_of_point / 2);
        x1 = binary_to_decimal(sx);
        y1 = binary_to_decimal(sy);
        long double x = make_float(x1, a, b, size_of_point / 2);
        long double y = make_float(y1, a, b, size_of_point / 2);
        Point t(x, y);
        result.push_back(t);
    }
    return result;
}

void show_points(Individe temp) {
    std::vector <Point> res = transform(temp, 0., 1., 5);
    for(int i = 0; i < res.size(); i++) {
        std::cout << res[i].x << " " << res[i].y << "\n";
    }
}

#endif /* Functions_h */
