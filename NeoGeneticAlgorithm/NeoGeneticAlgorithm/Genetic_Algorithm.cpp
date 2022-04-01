//
//  Genetic_Algorithm.cpp
//  NeoGeneticAlgorithm
//
//  Created by Anvar Rahimov on 30.03.2022.
//

#include <iostream>

#include "Heilbronn_Problem.h"

using namespace MyNameSpace;

void Heilbronn_Problem::evolution (Individual &bi, double &bd) {
    std::vector <Individual> new_population;
    std::vector <long double> new_population_quality;
    for (int i = 0; i < population_size; i++) {
        Individual p1 = selection_tournament (population, population_quality);
        Individual p2 = selection_tournament (population, population_quality);
        Individual child = crossover_two_point (p1, p2);
        child.mutation_strong ();
        /*if (last_best == check_fitness (best_individe ())) {
            child.mutation_strong ();
        } else {
            child.mutation_medium ();
        }*/
        new_population.push_back (child);
        new_population_quality.push_back (check_fitness (child));

    }
    population = new_population;
    population_quality = new_population_quality;
    long double temp = check_fitness (best_individe ());
    /*if (temp > bd) {
        bi = best_individe ();
        bd = temp;
    }*/
    std::cout << temp << "\n";
}

void Heilbronn_Problem::symbiosis (Individual &bi, double &bd) {
    std::vector <Individual> new_population;
    std::vector <long double> new_population_quality;
    for (int i = 0; i < population_size; i++) {
        Individual p1 (individual_size), p2 (individual_size), child (individual_size);
        if (random_int (0, 4) > 0) {
            Individual p1 = selection_tournament (population, population_quality);
            Individual p2 = selection_tournament (population, population_quality);
        } else {
            Individual p1 = selection_roulette_wheel (population, population_quality);
            Individual p2 = selection_roulette_wheel (population, population_quality);
        }
        if (random_int (0, 4) > 0) {
            child = crossover_one_point (p1, p2);
        } else {
            child = crossover_roulette_wheell (p1, p2, population, population_quality);
        }
        child.mutation_strong ();
        new_population.push_back (child);
        new_population_quality.push_back (check_fitness (child));
    }
    population = new_population;
    population_quality = new_population_quality;
    long double temp = check_fitness (best_individe ());
    /*if (temp > bd) {
        bi = best_individe ();
        bd = temp;
    }*/
    std::cout << temp << "\n";
}

int main () {
    int n = 1;
    long double av = 0;
    /*for (int i = 0; i < n; i++) {
        Heilbronn_Problem f (100, 5, 6);
        f.run (1000);
        double temp = f.check_fitness (f.best_individe ());
        std::cout << temp << "\n";
        av += temp;
    }
    std::cout << av / n << "\n\n";
    av = 0;
    for (int i = 0; i < n; i++) {
        Heilbronn_Problem f (100, 5, 6);
        f.run_symbiosis (1000);
        double temp = f.check_fitness (f.best_individe ());
        std::cout << temp << "\n";
        av += temp;
    }
    std::cout << av / n << "\n";*/
    for (int i = 0; i < n; i++) {
        Heilbronn_Problem f (1000, 6, 16);
        f.run (1000);
        av += f.check_fitness (f.best_individe ());
        show_points (f.best_individe ());
    }
    std::cout << av/n;
    return 0-0;
}
