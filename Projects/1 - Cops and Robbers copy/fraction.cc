#include "fraction.h"

static const int MAX_DEPTH = (1<<8)-1;
static const float MIN_FLOAT = (1<<4)*__FLT_EPSILON__;

static int absoluteValue(int number) {
    return (number>=0)?number:-number;
}

static float absoluteValue(float number) {
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

static Fraction approxContinuedFraction(float decimal) {
    if (decimal<MIN_FLOAT) return Fraction(0);
    bool sign = decimal < 0;
    if (sign) {decimal = -decimal;}
    Fraction resultFraction = 0;
    int integerParts[MAX_DEPTH]{static_cast<int>(decimal)};
    int integerPartsSize = 1;
    bool isCycling = false;
    int cycleSize = 0;
    int uniqueSteps = 0;
    float slowDecimal = decimal;
    decimal -= integerParts[0];
    for (int index=1;decimal>MIN_FLOAT&&index<MAX_DEPTH;index++) {
        decimal = 1/decimal;
        if (absoluteValue(decimal-slowDecimal)<MIN_FLOAT) {isCycling = true;}
        if (isCycling&&integerPartsSize%2==1) {
            // the continued fraction is cycling here.
            // this means that "decimal" is badly approximated by fractions beyond this point.
            // the fraction will be stopped on an even index (odd length) of integerParts.
            // an even index means the continued fraction made will always be less than "decimal".
            // this is the ideal case to stop the continued fraction in favor of a floating
            // point representation for the rest of "decimal" as it is non-negative
            // when subtracted by the continued fraction.
            cycleSize = (integerPartsSize+1)/2;
            uniqueSteps = integerPartsSize - cycleSize;
            integerPartsSize = cycleSize;
            integerPartsSize += integerPartsSize%2==0?1:0;
            break;
        }
        if (integerPartsSize%2==0) {
            slowDecimal -= integerParts[(integerPartsSize-1)/2];
            slowDecimal = 1/slowDecimal;
        }
        integerParts[index] = static_cast<int>(decimal);
        decimal -= integerParts[index];
        integerPartsSize++;
    }
    if (isCycling) {
        for (int i=0;i<(MAX_DEPTH-uniqueSteps)/cycleSize;i++) {
            for (int j=cycleSize+uniqueSteps-1;j>=uniqueSteps;j--) {
                if (resultFraction==0) {
                    resultFraction = integerParts[j];
                    continue;
                }
                resultFraction = Fraction(1,resultFraction) + integerParts[j];
            }
        }
        for (int i=uniqueSteps-1;i<=0;i--) {
            if (resultFraction==0) {
                resultFraction = integerParts[i];
                continue;
            }
            resultFraction = Fraction(1,resultFraction) + integerParts[i];
        }
    }
    else {
        for (int i=integerPartsSize-1;i>=0;i--) {
            if (resultFraction==0) {
                resultFraction = integerParts[i];
                continue;
            }
            resultFraction = Fraction(1,resultFraction) + integerParts[i];
            std::cout << resultFraction << std::endl;
        }
    }
    return sign ? -resultFraction:resultFraction;
}

Fraction::Fraction(int _num,int _den) {
    int commonDivisor;
    int64_t parsedNum;
    uint64_t parsedDen;

    if (_den<0) { // user input case
        parsedNum = static_cast<int64_t>(-_num);
        parsedDen = static_cast<uint64_t>(-_den);
    }
    else {
        parsedNum = static_cast<int64_t>(_num);
        parsedDen = static_cast<uint64_t>(_den);
    }

    commonDivisor = gcd(parsedNum,parsedDen);

    num = parsedNum/commonDivisor;
    den = parsedDen/commonDivisor;
}


Fraction::Fraction(int _num,Fraction _denFrac) {
    Fraction fraction;
    int64_t parsedNum;
    uint64_t parsedDen;

    if (_denFrac.num<0) {
        parsedNum = static_cast<int64_t>(_num)*static_cast<int64_t>(_denFrac.den)*-1;
        parsedDen = static_cast<uint64_t>(-_denFrac.num);
    }
    else {
        parsedNum = static_cast<int64_t>(_num)*static_cast<int64_t>(_denFrac.den);
        parsedDen = static_cast<uint64_t>(_denFrac.num);
    }

    fraction = Fraction(parsedNum,parsedDen);

    num = fraction.num;
    den = fraction.den;
}

Fraction::Fraction(float decimal,Fraction _denFrac) {
    Fraction approximation;

    approximation = approxContinuedFraction(decimal);
    approximation.num *= _denFrac.den;
    approximation.den *= _denFrac.num;

    num = approximation.num;
    den = approximation.den;
}

Fraction Fraction::operator=(Fraction rhs) {
    
    num = rhs.num;
    den = rhs.den;

    return Fraction(num,den);
}

Fraction Fraction::operator+(Fraction rhs) {
    int64_t parsedNum;
    uint64_t parsedDen;

    if (den==rhs.den) return Fraction(num+rhs.num,den);

    parsedNum = num * static_cast<int64_t>(rhs.den) + static_cast<int64_t>(den) * rhs.num;
    parsedDen = static_cast<uint64_t>(den) * static_cast<uint64_t>(rhs.den);

    return Fraction(parsedNum,parsedDen);
}

Fraction Fraction::operator-(Fraction rhs) {
    int64_t parsedNum;
    uint64_t parsedDen;

    if (den==rhs.den) return Fraction(num-rhs.num,den);

    parsedNum = num * static_cast<int64_t>(rhs.den) - static_cast<int64_t>(den) * rhs.num;
    parsedDen = static_cast<uint64_t>(den) * static_cast<uint64_t>(rhs.den);

    return Fraction(parsedNum,parsedDen);
}

Fraction Fraction::operator*(Fraction rhs) {
    int64_t parsedNum;
    uint64_t parsedDen;

    parsedNum = num * rhs.num;
    parsedDen = static_cast<uint64_t>(den) * static_cast<uint64_t>(rhs.den);

    return Fraction(parsedNum,parsedDen);
}

Fraction Fraction::operator/(Fraction rhs) {
    int64_t parsedNum;
    uint64_t parsedDen;

    if (rhs.num<0) {
        parsedNum = num * static_cast<int64_t>(rhs.den) * -1;
        parsedDen = static_cast<uint64_t>(den) * static_cast<uint64_t>(-rhs.num);
    }
    else {
        parsedNum = num * static_cast<int64_t>(rhs.den);
        parsedDen = static_cast<uint64_t>(den) * static_cast<uint64_t>(rhs.num);
    }

    return Fraction(parsedNum,parsedDen);
}

bool Fraction::operator==(Fraction rhs) {
    return num == rhs.num && den == rhs.den;
}

bool Fraction::operator!=(Fraction rhs) {
    return num != rhs.num || den != rhs.den;
}

bool Fraction::operator>=(Fraction rhs) {
    if (*this==rhs) return true;
    // not equal
    if (num<0&&rhs.num<0) return -*this<-rhs;
    // one is positive
    if (num>0&&rhs.num<0) return true;
    if (num<0&&rhs.num>0) return false;
    // both are positive
    if (num>den&&rhs.num<rhs.den) return true;
    if (num<den&&rhs.num>rhs.den) return false;
    // both are >1 or <1
    if (den==rhs.den) return num>rhs.num;
    // different denominators
    if (num==rhs.num&&num>0) return den<rhs.den;
    // different numerators
    if (num>=2&&den>=2&&rhs.num>=2&&rhs.den>=2) return num+rhs.den>den+rhs.num;
    // a numerator or denominator is 1
    if (den==1) return num>rhs.num/rhs.den;
    if (rhs.den==1) return num/den>=rhs.num;
    // a numerator is 1
    if (num==1) return den<rhs.den/rhs.num;
    if (rhs.num==1) return rhs.den>=den/num;
    
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

Fraction operator+(int lhs,Fraction rhs) {
    return rhs + lhs;
}
Fraction operator-(int lhs,Fraction rhs) {
    return rhs - lhs;
}

Fraction operator*(int lhs,Fraction rhs) {
    return rhs * lhs;
}

Fraction operator/(int lhs,Fraction rhs) {
    return rhs / lhs;
}


bool operator==(int lhs,Fraction rhs) {
    return rhs == lhs;
}

bool operator!=(int lhs,Fraction rhs) {
    return rhs != lhs;
}

bool operator>=(int lhs,Fraction rhs) {
    return rhs >= lhs;
}

bool operator<=(int lhs,Fraction rhs) {
    return rhs <= lhs;
}

bool operator>(int lhs,Fraction rhs) {
    return rhs > lhs;
}

bool operator<(int lhs,Fraction rhs) {
    return rhs < lhs;
}
