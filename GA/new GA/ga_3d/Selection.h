#ifndef SELECTION_H
#define SELECTION_H

#include <algorithm>
#include <cmath>

#include "Individual.h"

Individual selection_tournament (std::vector <Individual> &population_temp, std::vector <double> &population_quality_temp) {
    int sz = population_temp.size();
    int x = random_int (0, sz - 1);
    int y = random_int (0, sz - 1);
    if (population_quality_temp[x] >= population_quality_temp[y]) {
        return population_temp[x];
    } else {
        return population_temp[y];
    }
}

Individual selection_roulette_wheel (std::vector <Individual> &population_temp, std::vector <double> &population_quality_temp) {
    double sum = 0;
    int sz = population_temp.size();
    for (int i = 0; i < sz; i++) {
        sum += population_quality_temp[i];
    }
    double part_sum = random_double (0, sum);
    int chosen;
    for (chosen = 0; part_sum < sum; chosen++) {
        part_sum += population_quality_temp [chosen];
    }
    if (chosen == 0) {
        chosen = 1;
    }
    return population_temp[chosen - 1];
}

Individual selection_rank (std::vector <Individual> &population_temp, std::vector <double> &population_quality_temp) {
    int sz = population_temp.size();
    std::vector <double> ranks (sz, 0);
    std::vector<std::pair<double, int> > zip;
    for (int i = 0; i < sz; i++) {
        zip.push_back(std::make_pair(population_quality_temp[i], i));
    }
    std::sort(zip.begin(), zip.end(),
        [](std::pair<double, int> a, std::pair<double, int> b) {
            return a.first < b.first;
        });
    for (int i = 0; i < zip.size(); i++) {
        ranks [zip[i].second] = i + 1;
    }

    double start = zip[0].first;
    size_t iStart = 0;
    double sum = ranks[zip[0].second];
    size_t count = 1;
    bool isFirst = true;
    int i = 0;
    for (auto &elem : zip) {
        if (isFirst) {
            isFirst = false;
            i++;
            continue;
        }
        if (fabs(elem.first - start) <= std::numeric_limits<double>::epsilon()) {
            ++count;
            sum += ranks[elem.second];
        } else {
            if (count > 1)
            for (size_t j = iStart; j < i; ++j) {
                ranks[zip[j].second] = sum / count;
            }
            start = elem.first;
            iStart = i;
            count = 1;
            sum = ranks[elem.second];
        }
        ++i;
    }
    if (count > 1) {
        for (size_t j = iStart; j < sz; ++j) {
            ranks[zip[j].second] = sum / count;
        }
    }
    int summ = 0;
    for (int i = 0; i < sz; i++) {
        summ += ranks[i];
    }
    int part_sum = random_int (0, summ);
    int chosen;
    for (chosen = 0; part_sum < summ; chosen++) {
        part_sum += ranks [chosen];
    }
    if (chosen == 0) {
        chosen = 1;
    }
    return population_temp[chosen - 1];
}

Individual selection_random  (std::vector <Individual> &population_temp, std::vector <double> &population_quality_temp) {
    return population_temp [random_int (0, population_temp.size() - 1)];
}

#endif
