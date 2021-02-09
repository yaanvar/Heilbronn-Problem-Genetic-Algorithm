#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

class Individe {
    public:
        std::vector <bool> individual;
        int quality;
        std::string gens;

        int check_quality () {
            int temp_quality = 0;
            for (size_t i = 0; i < individual.size(); i++) {
                if (individual[i]) {
                    temp_quality++;
                }
            }
            quality = temp_quality;
            return quality;
        }

        std::string check_gens () {
            std::string temp_gens = "";
            for (size_t i = 0; i < individual.size(); i++) {
                if (individual[i]) {
                    temp_gens += '1';
                } else {
                    temp_gens += '0';
                }
            }
            gens = temp_gens;
            return gens;
        }

        Individe (int size_of_individual) {
            for (size_t i = 0; i < size_of_individual; i++) {
                if (rand() % 2) {
                    individual.push_back(true);
                } else {
                    individual.push_back(false);
                }
            }
            gens = check_gens();
            quality = check_quality();
        }

        Individe () {
        }

        void mutation_optional (double mutation_percent) { //TODO engine?
            for (size_t i = 0; i < individual.size(); i++) {
                if (rand() % 100 < mutation_percent) {
                    individual[i] = !individual[i];
                }
            }
            gens = check_gens();
            quality = check_quality();
        }

        void mutation_strong () {
            double mutation_percent = (3. / individual.size()) * 100;
            mutation_optional (mutation_percent);
        }

        void mutation_medium () {
            double mutation_percent = (1. / individual.size()) * 100;
            mutation_optional (mutation_percent);
        }

        void mutation_weak () {
            double mutation_percent = (1. / (3. * individual.size())) * 100;
            mutation_optional (mutation_percent);
        }
};

class Genetic_Algorithm {
    public:
        std::vector <Individe> population;
        int fitness;
        int population_size;
        int individe_size;
        int individe_quality;


        int check_fitness () {
            int temp_fitness = 0;
            for (int i = 0; i < population_size; i++) {
                if (population[i].quality >= individe_quality) {
                    temp_fitness++;
                }
            }
            fitness = temp_fitness;
            return fitness;
        }

        Genetic_Algorithm (int quantity_of_population, int size_of_individual, int min_quality) {
            for (int i = 0; i < quantity_of_population; i++) {
                population.push_back (Individe (size_of_individual));
            }
            population_size = quantity_of_population;
            individe_size = size_of_individual ;
            individe_quality = min_quality;
            fitness = check_fitness ();
        }

        int rand_divisor () {
            int divisor = rand() % individe_size;
            return divisor;
        }

        Individe selection () {
            int x = rand() % population_size;
            int y = rand() % population_size;
            if (population[x].quality >= population[y].quality) {
                return population[x];
            } else {
                return population[y];
            }
        }

        Individe crossover () {
            Individe parent_1;
            Individe parent_2;
            parent_1 = selection ();
            parent_2 = selection ();
            Individe child = parent_1;
            int divisor = rand_divisor ();
            for (int i = divisor; i < individe_size; i++) {
                child.individual[i] = parent_2.individual[i];
            }
            return child;
        }

        void evolution () {
            std::vector <Individe> temp_population;
            for (int i = 0; i < population_size; i++) {
                Individe temp_individe (individe_size);
                temp_individe = crossover();
                temp_individe.mutation_medium();
                temp_population.push_back(temp_individe);
            }
            population = temp_population;
            fitness = check_fitness();
        }

        void show_generation () {
            std::cout << "\n\n" << "Generation:" << " quantity of population = " << population_size
                    << " size of individe = " << population_size << "\n\n";
            for (int i = 0; i < population_size; i++) {
                std::cout << population[i].gens << "\n";
            }
            std::cout << "\n\n" << "fitted = " << fitness;
        }

        void run (int quantity_of_generations) {
            for (int i = 0; i < quantity_of_generations; i++) {
                show_generation();
                evolution();
            }
        }
};

int main () {

    srand(time(NULL));

    //code

    /*Individe temp (10);
    std::cout << temp.gens << std::endl;
    std::cout << temp.quality << std::endl;
    temp.mutation_optional(100);
    std::cout << temp.gens << std::endl;
    std::cout << temp.quality << std::endl;*/

    Genetic_Algorithm temp (10, 10, 5);
    temp.show_generation();
    std::cout << std::endl << temp.rand_divisor();
    //temp.show_generation();


    return 0-0;
}
