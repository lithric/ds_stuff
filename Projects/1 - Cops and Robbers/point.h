#ifndef _POINT_H
#define _POINT_H

#include <iostream>
#include "fraction.h"

class Point {
    public:
        Point(Fraction _x = Fraction(), Fraction _y = Fraction());
        ~Point() = default;

        Point operator+(Point rhs);
        Point operator-(Point rhs);
        Fraction operator*(Point rhs);
        Point operator*(Fraction rhs);

        Fraction x;
        Fraction y;
    private:
};

#endif