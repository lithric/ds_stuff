#include "fraction.h"

static int absoluteValue(int number) {
    return (number>=0)?number:-number;
}

static int gcd(int num,int den) {
    int remainder;
    
    num = absoluteValue(num);
    den = absoluteValue(den);

    while (den!=0) {
        remainder = num%den;
        num = den;
        den = remainder;
    }

    return num;
}

Fraction::Fraction(int _num,int _den) {
    int commonDivisor;

    if (_den<0) {
        _num = -_num;
        _den = -_den;
    }

    commonDivisor = gcd(_num,_den);

    num = _num/commonDivisor;
    den = _den/commonDivisor;
}

Fraction Fraction::operator=(Fraction rhs) {
    
    num = rhs.num;
    den = rhs.den;

    return Fraction(num,den);
}

Fraction Fraction::operator+(Fraction rhs) {
    int32_t resultNum;
    int32_t resultDen;

    resultNum = num * rhs.den + den * rhs.num;
    resultDen = den * rhs.den;

    return Fraction(resultNum,resultDen);
}

Fraction Fraction::operator-(Fraction rhs) {
    int32_t resultNum;
    int32_t resultDen;

    resultNum = num * rhs.den - den * rhs.num;
    resultDen = den * rhs.den;

    return Fraction(resultNum,resultDen);
}

Fraction Fraction::operator*(Fraction rhs) {
    int32_t resultNum;
    int32_t resultDen;

    resultNum = num * rhs.num;
    resultDen = den * rhs.den;

    return Fraction(resultNum,resultDen);
}

Fraction Fraction::operator/(Fraction rhs) {
    int32_t resultNum;
    int32_t resultDen;

    resultNum = num * rhs.den;
    resultDen = den * rhs.num;

    return Fraction(resultNum,resultDen);
}

bool Fraction::operator==(Fraction rhs) {
    return num == rhs.num && den == rhs.den;
}

bool Fraction::operator!=(Fraction rhs) {
    return num != rhs.num || den != rhs.den;
}

bool Fraction::operator>=(Fraction rhs) {
    return num*rhs.den>=den*rhs.num;
}

bool Fraction::operator<=(Fraction rhs) {
    return num*rhs.den<=den*rhs.num;
}

bool Fraction::operator>(Fraction rhs) {
    return num*rhs.den>den*rhs.num;
}

bool Fraction::operator<(Fraction rhs) {
    return num*rhs.den<den*rhs.num;
}

std::istream& operator>>(std::istream& inputStream, Fraction& fraction) {
    int inputNum;
    int inputDen;
    char slash;

    inputStream >> inputNum >> slash >> inputDen;

    fraction = Fraction(inputNum,inputDen);

    return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, Fraction fraction) {

    outputStream << fraction.getNum() << " / " << fraction.getDen();

    return outputStream;
}