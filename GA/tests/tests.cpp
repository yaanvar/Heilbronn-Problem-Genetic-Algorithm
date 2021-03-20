#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

#include "Random.h"
#include "Individual.h"
#include "Point.h"


double random_normal (double a, double dil) {
    std::normal_distribution<double> uid(a, dil);
    return uid(gen);
}


int main() {

    for (int i = 0; i < 100; i++) {
        std::cout << random_normal (100, 10) << "\n";
    }

    return 0-0;
}
