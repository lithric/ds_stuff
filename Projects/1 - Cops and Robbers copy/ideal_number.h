#ifndef _IDEAL_NUMBER_H
#define _IDEAL_NUMBER_H

#include "fraction.h"

class IdealNumber {
    public:
        IdealNumber(float _decimal=0.0);
        IdealNumber(Fraction _fraction=0);
        IdealNumber(int32_t _integer=0);
        ~IdealNumber() = default;

        IdealNumber operator=(IdealNumber number);

        IdealNumber operator+(IdealNumber number);
        IdealNumber operator-(IdealNumber number);
        IdealNumber operator*(IdealNumber number);
        IdealNumber operator/(IdealNumber number);

        bool operator==(IdealNumber rhs);
        bool operator!=(IdealNumber rhs);
        bool operator>=(IdealNumber rhs);
        bool operator<=(IdealNumber rhs);
        bool operator>(IdealNumber rhs);
        bool operator<(IdealNumber rhs);

    private:
        bool sign;
        unsigned int integer;
        Fraction fraction;
        float decimal;
};

#endif