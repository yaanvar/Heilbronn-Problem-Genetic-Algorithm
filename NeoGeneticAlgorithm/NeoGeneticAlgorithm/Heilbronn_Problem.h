//
//  Heilbronn_Problem.h
//  NeoGeneticAlgorithm
//
//  Created by Anvar Rahimov on 02.04.2022.
//

#ifndef Heilbronn_Problem_h
#define Heilbronn_Problem_h

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
            std::vector <long double> population_quality;
            int population_size;
            int individual_size;
            int points_quantity;
            long double last_best;

            void evolution (Individual &bi, double &bd);

            void symbiosis (Individual &bi, double &bd);

            void run (int generation_size) {
                Individual best_i (individual_size);
                double best_d = 0.;
                for (int i = 0; i < generation_size; i++) {
                    evolution (best_i, best_d);
                }
            }

            void run_symbiosis (int generation_size) {
                Individual best_i (individual_size);
                double best_d = 0.;
                for (int i = 0; i < generation_size; i++) {
                    symbiosis (best_i, best_d);
                    last_best = check_fitness (best_individe ());
                }
            }

            Heilbronn_Problem (int temp_population_size, int temp_quantity_of_points, int bits) {
                population_size = temp_population_size;
                points_quantity = temp_quantity_of_points;
                individual_size = 2 * bits * points_quantity;
                for (int i = 0; i < population_size; i++) {
                    population.push_back (Individual (individual_size));
                    population_quality.push_back(check_fitness (population[i]));
                }
            }

            long double check_fitness (Individual temp) {
                std::vector <Point> points = transform (temp, 0., 1., points_quantity);
                long double min_s = 1.;
                long double s = 0;
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
                long double max_fitness = 0;
                long double cnt = 0;
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

#endif /* Heilbronn_Problem_h */
