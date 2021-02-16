#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

class Point {
    public:
        double x;
        double y;
        //TODO: double z
        Point (double temp_x, double temp_y) {
            x = temp_x;
            y = temp_y;
        }
};

class Individe {
    public:
        std::vector <bool> gens;
        std::string str_gens;

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

        Individe (int individe_size) {
            for (size_t i = 0; i < individe_size; i++) {
                if (rand() % 2) {
                    gens.push_back (true);
                } else {
                    gens.push_back (false);
                }
            }
            str_gens = check_gens ();
        }

        Individe () {
        }

        void mutation_optional (double mutation_percent) { //TODO engine?
            for (size_t i = 0; i < gens.size(); i++) {
                if (rand() % 100 < mutation_percent) {
                    gens[i] = !gens[i];
                }
            }
            str_gens = check_gens ();
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

class Genetic_Algorithm {
    public:
        std::vector <Individe> population;
        int population_size;
        int individe_size;
        double population_fitness;

        virtual double check_individe_fitness (Individe temp) = 0;

        virtual double check_population_fitness () = 0;

        virtual void show_generation () = 0;

        virtual void run (int population_size) = 0;

        int rand_divisor () {
            int divisor = rand() % individe_size;
            return divisor;
        }

        Individe selection_tournament () {
            int x = rand() % population_size;
            int y = rand() % population_size;
            if (check_individe_fitness (population[x]) >= check_individe_fitness (population[y])) { ///////////
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
            int divisor = rand_divisor ();
            Individe child = parent_1;
            for (int i = divisor; i < individe_size; i++) {
                child.gens[i] = parent_2.gens[i];
            }
            return child;
        }

        Individe crossover_double_point () {
            Individe parent_1;
            Individe parent_2;
            Individe parent_3;
            parent_1 = selection_tournament ();
            parent_2 = selection_tournament ();
            parent_3 = selection_tournament ();
            int divisor = rand_divisor ();
            int divisor_2 = rand_divisor ();
            Individe child = parent_1;
            for (int i = std::min(divisor, divisor_2); i < std::max(divisor, divisor_2); i++) {
                child.gens[i] = parent_2.gens[i];
            }
            for (int i = std::max(divisor, divisor_2); i < individe_size; i++) {
                child.gens[i] = parent_3.gens[i];
            }
            return child;
        }

        Individe crossover_simmetry () {
            Individe parent_1;
            Individe parent_2;
            parent_1 = selection_tournament ();
            parent_2 = selection_tournament ();
            int divisor = individe_size / 2;
            Individe child = parent_1;
            for (int i = divisor; i < individe_size; i++) {
                child.gens[i] = parent_2.gens[i];
            }
            return child;
        }

        void evolution () {
            std::vector <Individe> temp_population;
            for (int i = 0; i < population_size; i++) {
                Individe temp_individe (individe_size);
                temp_individe = crossover_one_point ();
                temp_individe.mutation_medium (); //mutation
                temp_population.push_back (temp_individe);
            }
            population = temp_population;
            population_fitness = check_population_fitness (); //TODO
        }
};

class Ideal_Binary_Line: public Genetic_Algorithm {
    public:

        Ideal_Binary_Line (int temp_population_size, int temp_individe_size) {
            for (int i = 0; i < temp_population_size; i++) {
                population.push_back (Individe (temp_individe_size));
            }
            population_size = temp_population_size;
            individe_size = temp_individe_size ;
            population_fitness = check_population_fitness ();
        }

        double check_individe_fitness (Individe temp) {
            double temp_individe_fitness = 0;
            for (size_t i = 0; i < individe_size; i++) {
                if (temp.gens[i]) {
                    temp_individe_fitness++;
                }
            }
            return temp_individe_fitness;
        }

        double check_population_fitness () {
            int temp_population_fitness = 0;
            for (int i = 0; i < population_size; i++) {
                temp_population_fitness += check_individe_fitness (population[i]);
            }
            population_fitness = temp_population_fitness / population_size;
            return population_fitness;
         }

         void show_generation () { //TODO
            std::cout << "\n\n" << "Generation:" << " size of population = " << population_size
                    << " size of individe = " << individe_size << " population fitness = " << population_fitness << "\n\n";
            for (int i = 0; i < population_size; i++) {
                std::cout << population[i].str_gens << "\t" << check_individe_fitness (population[i]) << "\n";
            }
        }

         void run (int generation_size) {
            for (int i = 0; i < generation_size; i++) {
                show_generation ();
                evolution ();
            }
        }
};

class Heilbronn_Problem: public Genetic_Algorithm {
    public:

        Heilbronn_Problem (int temp_population_size, int temp_individe_size) {
                for (int i = 0; i < temp_population_size; i++) {
                    population.push_back (Individe (temp_individe_size));
                }
                population_size = temp_population_size;
                individe_size = temp_individe_size ;
                population_fitness = check_population_fitness ();
        }

        double check_individe_fitness (Individe temp) {
            double temp_individe_fitness = f_triangle_area (temp, 4);
            return temp_individe_fitness;
        }

        double check_population_fitness () {
                double temp_population_fitness = 0.;
                for (int i = 0; i < population_size; i++) {
                    temp_population_fitness += check_individe_fitness (population[i]);
                }
                population_fitness = temp_population_fitness / population_size;
                return population_fitness;
        }

        void show_generation () { //TODO
            std::cout << "\n\n" << "Generation:" << " size of population = " << population_size
                    << " size of individe = " << individe_size << " population fitness = " << population_fitness << "\n\n";
            for (int i = 0; i < population_size; i++) {
                std::cout << population[i].str_gens << "\t" << check_individe_fitness (population[i]) << "\n";
            }
        }

        void run (int generation_size) {
            for (int i = 0; i < generation_size; i++) {
                show_generation ();
                evolution ();
            }
        }

        //code

        int binary_to_decimal (std::string str_gens) {
            return std::stoi (str_gens, 0, 2);
        }

        double make_float (int point, double a, double b, int size_of_point) { // n - size of one point
            double h = (b - a) / (pow (2, size_of_point) - 1.);
            double result = a + point * h;
            return result;
        }

        std::vector <Point> transform (Individe temp, double a, double b, int quantity_of_points) {
            std::vector <Point> result;
            int size_of_point = temp.str_gens.size () / quantity_of_points;
            for (int i = 0; i < temp.gens.size(); i += size_of_point) {
                int x1, y1;
                std::string s = temp.str_gens.substr (i, size_of_point);
                std::string sx = s.substr (0, size_of_point / 2);
                std::string sy = s.substr (size_of_point / 2, size_of_point / 2);
                x1 = binary_to_decimal (sx);
                y1 = binary_to_decimal (sy);
                double x = make_float (x1, a, b, size_of_point / 2);
                double y = make_float (y1, a, b, size_of_point / 2);
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

        double f_triangle_area (Individe temp, int quantity_of_points) { //TODO: площадь n треугольников
            std::vector <Point> points = transform (temp, 0., 1., quantity_of_points);
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

    //Ideal_Binary_Line temp (100, 100);
    Heilbronn_Problem temp (100, 100);
    temp.run (1000);

    return 0-0;
}
