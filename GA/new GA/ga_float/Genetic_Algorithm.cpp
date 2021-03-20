#include <iostream>

#include "Heilbronn_Problem_Class.h"

using namespace MyNameSpace;



/*void Heilbronn_Problem::symbiosis () {
    std::vector <Individual> new_population;
    std::vector <double> new_population_quality;
    for (int i = 0; i < population_size; i++) {
        Individual p1 (points_quantity), p2 (points_quantity), child (points_quantity);
        switch (random_int (0, 2)) {
            case 0:
                p1 = selection_rank (population, population_quality);
                p2 = selection_rank (population, population_quality);
                break;
            case 1:
                p1 = selection_tournament (population, population_quality);
                p2 = selection_tournament (population, population_quality);
                break;
            case 2:
                p1 = selection_roulette_wheel (population, population_quality);
                p2 = selection_roulette_wheel (population, population_quality);
                break;
            default:
                std::cout << "error";
                break;
        }
        switch (random_int (0, 3)) {
            case 0:
                child = crossover_one_point (p1, p2);
                break;
            case 1:
                child = crossover_two_point (p1, p2);
                break;
            case 2:
                child = crossover_roulette_wheell (p1, p2, population, population_quality);
                break;
            case 3:
                child = crossover_symmetric (p1, p2);
                break;
            default:
                std::cout << "error";
                break;
        }
        if (last_best == check_fitness (best_individe ())) {
            child.mutation_strong ();
        } else {
            child.mutation_medium ();
        }
        new_population.push_back (child);
        new_population_quality.push_back (check_fitness (child));
    }
    population = new_population;
    population_quality = new_population_quality;
    double temp = check_fitness (best_individe ());
    std::cout << temp << "\n";
}*/

int main () {
    int n = 10;
    double av = 0;
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
        Heilbronn_Problem f (1000, 5, 16);
        f.run (300);
        av += f.check_fitness (f.best_individe ());
    }
    std::cout << av / n;
    return 0-0;
}
