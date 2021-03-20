#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
#include <string>
#include <vector>

#include "Random.h"

class Individual {
    public:
        std::vector <char> gens;
        std::string str_gens;

        Individual (int Individual_size) {
            for (size_t i = 0; i < Individual_size; i++) {
                gens.push_back (random_int (0, 1));
            }
            str_gens = check_gens();
        }
        std::string check_gens () {
            std::string temp_gens = "";
            for (size_t i = 0; i < gens.size(); i++) {
                if (gens[i]) {
                    temp_gens += '1';
                } else {
                    temp_gens += '0';
                }
            }
            str_gens = temp_gens;
            return str_gens;
        }

        void mutation_optional (double mutation_percent) {
            int mutation_percent_int = (int) mutation_percent;
            for (size_t i = 0; i < gens.size(); i++) {
                if (random_int (0, 100) < mutation_percent_int) {
                    gens[i] = !gens[i];
                }
            }
            str_gens = check_gens();
        }

        void mutation_strong () {
            double mutation_percent = (3. / gens.size()) * 100;
            mutation_optional (mutation_percent);
        }

        void mutation_medium () {
            double mutation_percent = (1. / gens.size()) * 100;
            mutation_optional (mutation_percent);
        }

        void mutation_weak () {
            double mutation_percent = (1. / (3. * gens.size())) * 100;
            mutation_optional (mutation_percent);
        }
};

#endif
