//
//  Point.h
//  NeoGeneticAlgorithm
//
//  Created by Anvar Rahimov on 02.04.2022.
//

#ifndef Point_h
#define Point_h

class Point {
    public:
        long double x;
        long double y;
        //TODO: double z
        Point(long double temp_x, long double temp_y) {
            x = temp_x;
            y = temp_y;
        }
};

#endif /* Point_h */
