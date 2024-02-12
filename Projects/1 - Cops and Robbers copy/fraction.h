#include <cstdint>

#ifndef _FRACTION_H
#define _FRACTION_H

#include <iostream>

class Fraction {
    public:
        Fraction(int _num=0) {num=_num;den=1;};
        Fraction(int _num,int _den);
        Fraction(int _num,Fraction _denFrac);
        Fraction(float decimal,Fraction _denFrac=1);
        Fraction(double decimal,Fraction _denFrac=1);
        ~Fraction() = default;

        Fraction operator=(Fraction rhs);

        Fraction operator+(Fraction rhs);
        Fraction operator-(Fraction rhs);
        Fraction operator*(Fraction rhs);
        Fraction operator/(Fraction rhs);

        Fraction operator+=(Fraction rhs) {return *this = *this + rhs;}
        Fraction operator-=(Fraction rhs) {return *this = *this - rhs;}
        Fraction operator*=(Fraction rhs) {return *this = *this * rhs;}
        Fraction operator/=(Fraction rhs) {return *this = *this / rhs;}

        Fraction& operator++() {num+=den;return *this;} // prefix
        Fraction& operator--() {num-=den;return *this;} // prefix
        Fraction operator++(int) {Fraction temp=*this;++*this;return temp;} // postfix
        Fraction operator--(int) {Fraction temp=*this;--*this;return temp;} // postfix

        Fraction operator-() {return Fraction(-num,den);} // unary minus

        explicit operator double() {return (double)num/(double)den;}
        explicit operator float() {return (float)num/(float)den;}
        explicit operator int() {return num/den;}

        bool operator==(Fraction rhs);
        bool operator!=(Fraction rhs);
        bool operator>=(Fraction rhs);
        bool operator<=(Fraction rhs);
        bool operator>(Fraction rhs);
        bool operator<(Fraction rhs);

        [[nodiscard]] int64_t getNum() const { return num; }
        [[nodiscard]] uint32_t getDen() const { return den; }
    private:
        int64_t num;
        uint32_t den;
};

std::istream& operator>>(std::istream&, Fraction&);
std::ostream& operator<<(std::ostream&, Fraction);

Fraction operator+(int lhs,Fraction rhs);
Fraction operator-(int lhs,Fraction rhs);
Fraction operator*(int lhs,Fraction rhs);
Fraction operator/(int lhs,Fraction rhs);

bool operator==(int lhs,Fraction rhs);
bool operator!=(int lhs,Fraction rhs);
bool operator>=(int lhs,Fraction rhs);
bool operator<=(int lhs,Fraction rhs);
bool operator>(int lhs,Fraction rhs);
bool operator<(int lhs,Fraction rhs);

#endif