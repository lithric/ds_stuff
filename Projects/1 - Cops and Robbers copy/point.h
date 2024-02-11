#ifndef _POINT_H
#define _POINT_H

#include <iostream>
#include "fraction.h"

class Point {
    public:
        Point(Fraction _x = 0, Fraction _y = 0);
        ~Point() = default;

        Point operator+(Point rhs);
        Point operator-(Point rhs);
        Fraction operator*(Point rhs);
        Point operator*(Fraction rhs);

        Fraction x;
        Fraction y;
    private:
};

std::istream& operator>>(std::istream&, Point&);
std::ostream& operator<<(std::ostream&, Point);

#endif