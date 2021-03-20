#ifndef POINT_H
#define POINT_H

class Point {
    public:
        long double x;
        long double y;
        //TODO: double z
        Point (long double temp_x, long double temp_y) {
            x = temp_x;
            y = temp_y;
        }
};

#endif
