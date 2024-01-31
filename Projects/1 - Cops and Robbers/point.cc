#include "point.h"

Point::Point(Fraction _x, Fraction _y) {
    x = _x;
    y = _y;
}

Point Point::operator+(Point rhs) {
    Fraction newX;
    Fraction newY;

    newX = x + rhs.x;
    newY = y + rhs.y;

    return Point(newX,newY);
}

Point Point::operator-(Point rhs) {
    Fraction newX;
    Fraction newY;

    newX = x - rhs.x;
    newY = y - rhs.y;

    return Point(newX,newY);
}

Fraction Point::operator*(Point rhs) {
    return x*rhs.y-rhs.x*y;
}

Point Point::operator*(Fraction rhs) {
    Fraction newX;
    Fraction newY;

    newX = x * rhs;
    newY = y * rhs;

    return Point(newX,newY);
}