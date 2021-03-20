#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>
#include <vector>
#include <cmath>
#include "Random.h"

class Individual {
    public:
        std::vector <double> gens;

        Individual (int quantity_of_points) {
            for (size_t i = 0; i < quantity_of_points * 2; i++) {
                gens.push_back (random_double (0, 1));
            }
        }

        void mutation (double mutation_percent, int generations, int generation) {
            int mutation_percent_int = (int) mutation_percent;
            for (size_t i = 0; i < gens.size(); i++) {
                if (random_int (0, 100) < mutation_percent_int) {
                    if (random_int (0, 1)) {
                        double t = generation / generations;
                        gens[i] = gens[i] - gens[i] * (1 - std::pow (random_int (0, 1), std::pow(1 - t, 5)));
                    } else {
                        double t = generation / generations;
                        gens[i] = gens[i] + (1 - gens[i]) * (1 - std::pow (random_int (0, 1), std::pow(1 - t, 5)));
                    }
                }
            }
        }
};

#endif
