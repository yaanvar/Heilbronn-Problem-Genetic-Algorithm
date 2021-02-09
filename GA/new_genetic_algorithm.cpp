#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

class Individe {
    public:
        std::vector <bool> individual;
        std::string gens;

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
                    individual.push_back (true);
                } else {
                    individual.push_back (false);
                }
            }
            gens = check_gens ();
        }

        Individe () {
        }

        void mutation_optional (double mutation_percent) { //TODO engine?
            for (size_t i = 0; i < individual.size(); i++) {
                if (rand() % 100 < mutation_percent) {
                    individual[i] = !individual[i];
                }
            }
            gens = check_gens ();
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
        int population_size;
        int individe_size;

        int check_quality () = 0;

        int check_fitness () = 0;

        Genetic_Algorithm (int quantity_of_population, int size_of_individual, int min_quality) {
            for (int i = 0; i < quantity_of_population; i++) {
                population.push_back (Individe (size_of_individual));
            }
            population_size = quantity_of_population;
            individe_size = size_of_individual ;
            //individe_min_quality = min_quality;
            //fitness = check_fitness ();
        }

        int rand_divisor () {
            int divisor = rand() % individe_size;
            return divisor;
        }

        Individe selection_tournament () { //TODO (quality)
            int x = rand() % population_size;
            int y = rand() % population_size;
            if (population[x].quality >= population[y].quality) {
                return population[x];
            } else {
                return population[y];
            }
        }

        Individe crossover_one_point () {
            Individe parent_1;
            Individe parent_2;
            parent_1 = selection_tournament ();
            parent_2 = selection_tournament ();
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
                temp_individe = crossover_one_point ();
                temp_individe.mutation_medium ();
                temp_population.push_back (temp_individe);
            }
            population = temp_population;
            fitness = check_fitness (); //TODO 
        }

        void show_generation () { //TODO
            std::cout << "\n\n" << "Generation:" << " quantity of population = " << population_size
                    << " size of individe = " << population_size << "\n\n";
            for (int i = 0; i < population_size; i++) {
                std::cout << population[i].gens << "\n";
            }
            std::cout << "\n\n" << "fitted = " << fitness;
        }

        void run (int quantity_of_generations) {
            for (int i = 0; i < quantity_of_generations; i++) {
                show_generation ();
                evolution ();
            }
        }
};

class Ideal_Binary_Line: public Genetic_Algorithm {
    public:
        int fitness;
        int individe_quality;
        int individe_min_quality;

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

        int check_fitness () {
            int temp_fitness = 0;
            for (int i = 0; i < population_size; i++) {
                if (population[i].quality >= individe_min_quality) {
                    temp_fitness++;
                }
            }
            fitness = temp_fitness;
            return fitness;
         }

};

struct Point {
    double x;
    double y;
    //TODO: double z
    Point (double temp_x, double temp_y) {
        x = temp_x;
        y = temp_y;
    }
};

class Heilbronn_Problem: public Genetic_Algorithm {

    //code

    int binary_to_decimal (std::string gens) {
        return std::stoi (gens, 0, 2);
    }

    double make_float (int point, double a, double b, int n) { // n - size of one point
        double h = (b - a) / (n * n - 1.);
        double result = a + point * h;
        return result;
    }

    std::vector <Point> transform (Individe temp, double a, double b, int size_of_point) {
        std::vector <Point> result;
        for (int i = 0; i < temp.individual.size(); i += size_of_point) {
            int x1, y1;
            std::string s = temp.gens.substr (i, size_of_point);
            std::string sx = s.substr (0, size_of_point / 2);
            std::string sy = s.substr (size_of_point / 2, size_of_point);
            x1 = binary_to_decimal (sx);
            y1 = binary_to_decimal (sy);
            double x = make_float (x1, a, b, size_of_point);
            double y = make_float (y1, a, b, size_of_point);
            Point t (x, y);
            result.push_back (t);
        }
        return result;
    }

    double triangle_area (Point first, Point second, Point third) {
        double AB, BC, AC, ab, bc, ac, p, S;
        AB = ((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));
        ab = sqrt(AB);
        BC = ((second.x - third.x) * (second.x - third.x) + (second.y - third.y) * (second.y - third.y));
        bc = sqrt(BC);
        AC = ((first.x - third.x) * (first.x - third.x) + (first.y - third.y) * (first.y - third.y));
        ac = sqrt(AC);
        p = (ab + ac + bc) / 2;
        S = sqrt((p - ab) * (p - ac) * (p - bc) * p);
        return S;
    }

    double f_triangle_area (Individe temp, int size_of_point) {
        std::vector <Point> points = transform (temp, 0., 1., size_of_point);
        double min_s = 1.;
        double s = 0;
        for (int i = 0; i < points.size(); i++) {
            for (int j = 0; j < points.size(); j++) {
                for (int z = 0; z < points.size(); z++) {
                    if (i != j || i != z || j != z) {
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

};




int main() {

    srand(time(NULL));

    //code

    Genetic_Algorithm temp (10, 10, 9);
    temp.run (1000);

    return 0-0;
}
