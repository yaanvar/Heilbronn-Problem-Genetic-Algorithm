#ifndef POINT_H
#define POINT_H

class Point {
    public:
        double x;
        double y;
        double z;
        Point (double temp_x, double temp_y, double temp_z) {
            x = temp_x;
            y = temp_y;
            z = temp_z;
        }
};

#endif
