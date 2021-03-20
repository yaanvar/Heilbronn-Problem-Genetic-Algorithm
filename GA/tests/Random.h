#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <random>
#include <chrono>

auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);

int random_int (int a, int b) {
    std::uniform_int_distribution<> uid(a, b);
    return uid(gen);
}

double random_double (double a, double b) {
    std::uniform_real_distribution<double> uid(a, b);
    return uid(gen);
}

#endif
