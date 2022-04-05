//
//  Crossover.h
//  NeoGeneticAlgorithm
//
//  Created by Anvar Rahimov on 02.04.2022.
//

#ifndef Crossover_h
#define Crossover_h

#include "Individe.h"

Individe crossover_one_point(Individe &parent1, Individe &parent2) {
    int sz = parent1.gens.size();
    Individe child = parent1;
    int del = random_int(0, sz);
    for (int i = del; i < sz; i++) {
        child.gens[i] = parent2.gens[i];
    }
    return child;
}

Individe crossover_two_point(Individe &parent1, Individe &parent2) {
    int sz = parent1.gens.size();
    Individe child = parent1;
    int del = random_int(0, sz);
    int del2 = random_int(del, sz);
    for (int i = del; i < del2; i++) {
        child.gens[i] = parent2.gens[i];
    }
    for (int i = del2; i < sz; i++) {
        child.gens[i] = parent1.gens[i];
    }
    return child;
}

Individe crossover_symmetric(Individe &parent1, Individe &parent2) {
    int sz = parent1.gens.size();
    Individe child = parent1;
    int del = sz / 2;
    for (int i = del; i < sz; i++) {
        child.gens[i] = parent2.gens[i];
    }
    return child;
}

Individe crossover_roulette_wheel(Individe &parent1, Individe &parent2, std::vector <Individe> &population_temp, std::vector <long double> &population_qualtity_temp) {
    int sz = parent1.gens.size();
    int x = -1, y = -1;
    for (int i = 0; i < population_qualtity_temp.size(); i++) {
        if (parent1.gens == population_temp[i].gens) {
            if (x == -1) {
                x = i;
            } else if (y == -1) {
                y = i;
            }
        } else if (parent2.gens == population_temp[i].gens) {
            if (x == -1) {
                x = i;
            } else if (y == -1) {
                y = i;
            }
        }
    }
    Individe child = population_temp[x];
    int prob = (int) (population_qualtity_temp[y] / (population_qualtity_temp[y] + population_qualtity_temp[x])) * 100;
    for (int i = 0; i < sz; i++) {
        if (random_int(0, 100) < prob) {
            child.gens[i] = population_temp[y].gens[i];
        }
    }
    return child;
}

#endif /* Crossover_h */
