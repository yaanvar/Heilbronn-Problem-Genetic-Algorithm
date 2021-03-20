#ifndef HEILBRONN_PROBLEM_CLASS_H
#define HEILBRONN_PROBLEM_CLASS_H

#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Selection.h"
#include "Crossover.h"
#include "Functions.h"

namespace MyNameSpace {
    class Heilbronn_Problem {
        public:
            std::vector <Individual> population;
            std::vector <double> population_quality;
            int population_size;
            int points_quantity;
            double last_best;

            void evolution ();

            void symbiosis ();

            void run (int generations) {
                for (int i = 0; i < generations; i++) {
                    evolution (generations, i);
                }
            }
void evolution (int generations, int generation) {
    generation++;
    std::vector <Individual> new_population;
    std::vector <double> new_population_quality;
    for (int i = 0; i < population_size; i++) {
        Individual p1 = selection_rank (population, population_quality);
        Individual p2 = selection_rank (population, population_quality);
        Individual child = crossover_two_point (p1, p2);
        child.mutation (10, generations, generation);
        new_population.push_back (child);
        new_population_quality.push_back (check_fitness (child));

    }
    population = new_population;
    population_quality = new_population_quality;
    double temp = check_fitness (best_individe ());
    std::cout << temp << "\n";
}
            void run_symbiosis (int generations) {
                for (int i = 0; i < generations; i++) {
                    symbiosis ();
                    last_best = check_fitness (best_individe ());
                }
            }

            Heilbronn_Problem (int temp_population_size, int temp_quantity_of_points, int bits) {
                population_size = temp_population_size;
                points_quantity = temp_quantity_of_points;
                for (int i = 0; i < population_size; i++) {
                    population.push_back (Individual (points_quantity));
                    population_quality.push_back(check_fitness (population[i]));
                }
            }

            double check_fitness (Individual temp) {
                std::vector <Point> points = transform (temp, 0., 1., points_quantity);
                double min_s = 1.;
                double s = 0;
                int sz = points.size();
                for (int i = 0; i < sz; i++) {
                    for (int j = 0; j < sz; j++) {
                        for (int z = 0; z < sz; z++) {
                            if (i != j && i != z && j != z) {
                                s = triangle_area(points[i], points[j], points[z]);
                                if (s < min_s) {
                                    min_s = s;
                                }
                            }
                        }
                    }
                }
                return min_s;
            }

            Individual best_individe () {
                double max_fitness = 0;
                double cnt = 0;
                for (int i = 0; i < population_size; i++) {
                    if (population_quality[i] > max_fitness) {
                        max_fitness = population_quality[i];
                        cnt = i;
                    }
                }
                return population[cnt];
            }
    };
}
#endif
