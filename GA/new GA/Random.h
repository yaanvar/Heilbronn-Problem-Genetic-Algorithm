#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <chrono>
#include <ctime>

auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 gen(seed);

int random_int (int a, int b) {
    std::uniform_int_distribution<> uid(a, b);
    return uid(gen);
}

long double random_double (long double a, long double b) {
    std::uniform_real_distribution<long double> uid(a, b);
    return uid(gen);
}

#endif
