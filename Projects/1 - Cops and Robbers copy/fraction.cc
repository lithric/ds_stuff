#include "fraction.h"

static int absoluteValue(int);
static float absoluteValue(float);
static double absoluteValue(double);
static int gcd(int,int);
static int seqB(int[],int,int);
static Fraction seqARevProd(int[],int,int);
static Fraction seqAProd(int[],int,int);
static Fraction seqA(int[],int,int);
static Fraction seqARev(int[],int,int);
static Fraction seqAFinalProd(int[],int);
static Fraction buildContinuedFraction(int[],int);
static Fraction approxContinuedFraction(float);
static Fraction approxContinuedFraction(double);

static const int MAX_DEPTH = (1<<8)-1;
static const float MIN_FLOAT = (1<<4)*__FLT_EPSILON__;
static const double MIN_DOUBLE = (1<<4)*__FLT_EPSILON__;
static const int MAX_THRESH = (1<<15);

static int absoluteValue(int number) {
    return (number>=0)?number:-number;
}

static float absoluteValue(float number) {
    return (number>=0)?number:-number;
}

static double absoluteValue(double number) {
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

static int seqB(int series[],int mode,int k) {
    int finalVal = 1;
    for (int i=1;i<=mode;i++) {
        finalVal *= series[i+k];
    }
    return finalVal;
}

static Fraction seqARevProd(int series[],int mode,int k) {
    Fraction finalVal = 1;
    for (int t=2;t<=mode-2;t++) {
        finalVal *= seqARev(series,t,mode-t-2+k);
    }
    return finalVal;
}

static Fraction seqA(int series[],int mode,int k=0) {
    Fraction returnFraction = 0;
    if (mode==1) {
        returnFraction = Fraction(1,series[k+1]);
    }
    else if (mode==2) {
        returnFraction = seqA(series,1,k+1) + series[k+1];
    }
    else {
        returnFraction = seqA(series,mode-1,k+1);
        returnFraction += (mode%2==0?-1:1)*Fraction(1,seqB(series,mode-2,k)*seqARevProd(series,mode,k));
    }
    return returnFraction;
}

static Fraction seqAProd(int series[],int mode,int k) {
    Fraction finalVal = 1;
    for (int t=2;t<=mode-2;t++) {
        finalVal *= seqA(series,t,mode-t+k);
    }
    return finalVal;
}

static Fraction seqARev(int series[],int mode,int k=0) {
    Fraction returnFraction = 0;
    if (mode==1) {
        returnFraction = Fraction(1,series[k+1]);
    }
    else if (mode==2) {
        returnFraction = seqARev(series,1,k) + series[k+2];
    }
    else {
        returnFraction = seqARev(series,mode-1,k);
        returnFraction += (mode%2==0?-1:1)*Fraction(1,seqB(series,mode-2,2+k)*seqAProd(series,mode,k));
    }
    return returnFraction;
}

static Fraction seqAFinalProd(int series[],int mode) {
    Fraction finalVal = 1;
    for (int i=2;i<=mode;i++) {
        finalVal *= seqA(series,i,0);
    }
    return finalVal;
}

static Fraction buildContinuedFraction(int series[],int size) {
    if (size==0) return Fraction(0);
    Fraction finalVal = series[0];
    if (size==1) return finalVal;
    Fraction protectVal = finalVal;
    for (int i=1;i<size;i++) {
        protectVal = finalVal + (i%2==1?1:-1)*Fraction(1,seqB(series,i,0)*seqAFinalProd(series,i));
        if (protectVal.getNum()>(1LL<<60)||protectVal.getDen()>(1LL<<26)) {
            break;
        }
        finalVal = protectVal;
    }
    return finalVal;
}

static Fraction approxContinuedFraction(float decimal) {
    return approxContinuedFraction(static_cast<double>(decimal));
}

static Fraction approxContinuedFraction(double decimal) {
    if (decimal<MIN_DOUBLE) return Fraction(0);
    bool sign = decimal < 0;
    if (sign) {decimal = -decimal;}
    Fraction resultFraction = 0;
    int integerParts[MAX_DEPTH]{static_cast<int>(decimal)};
    int integerPartsSize = 1;
    bool isCycling = false;
    int cycleSize = 0;
    int uniqueSteps = 0;
    double slowDecimal = decimal;
    decimal -= integerParts[0];
    for (int index=1;decimal>MIN_DOUBLE&&index<MAX_DEPTH;index++) {
        decimal = 1/decimal;
        if (absoluteValue(decimal-slowDecimal)<MIN_DOUBLE) {isCycling = true;}
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
            if (resultFraction.getDen()>(uint32_t)(MAX_THRESH>>uniqueSteps)) {
                break;
            }
            for (int j=cycleSize+uniqueSteps-1;j>=uniqueSteps+1;j--) {
                resultFraction += integerParts[j];
                resultFraction = Fraction(1,resultFraction);
            }
            resultFraction += integerParts[uniqueSteps];
        }
        for (int i=uniqueSteps-1;i>=1;i--) {
            resultFraction += integerParts[i];
            resultFraction = Fraction(1,resultFraction);
            if (resultFraction.getDen()>MAX_THRESH&&i%2) {
                break;
            }
        }
        resultFraction += integerParts[0];
    }
    else {
        resultFraction = buildContinuedFraction(integerParts,integerPartsSize);
    }
    return sign ? -resultFraction:resultFraction;
}

Fraction::Fraction(int _num,int _den) {
    uint64_t commonDivisor;
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

Fraction::Fraction(double decimal,Fraction _denFrac) {
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
    
    return *this>rhs;
}

bool Fraction::operator<=(Fraction rhs) {
    return rhs>=*this;
}

bool Fraction::operator>(Fraction rhs) {
    // this should work for all extreme cases
    uint64_t num1;
    uint64_t num2;
    uint64_t den1;
    uint64_t den2;
    if (*this==rhs) return false;
    // not equal (non-negotiable)
    if (num<0&&rhs.num<0) return -rhs>-*this;
    if (num<0||rhs.num<0) return rhs.num<0;
    // both are positive (non-negotiable)
    num1 = static_cast<uint64_t>(num);
    num2 = static_cast<uint64_t>(rhs.num);
    den1 = static_cast<uint64_t>(den);
    den2 = static_cast<uint64_t>(rhs.den);
    if (num1/den1!=num2/den2) return num1/den1>num2/den2;
    // same integer part (non-negotiable)
    num1 = num1 - (num1/den1) * den1; // cannot overflow & cannot be negative
    num2 = num2 - (num2/den2) * den2; // cannot overflow & cannot be negative
    // numerators are less than their denominators (as defined by equation)
    // numerators are less than 32bit unsigned integer (as defined by equation)
    if (den1<=den2&&num1>=num2) return true;
    if (den1>=den2&&num1<=num2) return false;
    // different numerators (non-negotiable)
    // different denominators (non-negotiable)

    return num1*den2>den1*num1;
}

bool Fraction::operator<(Fraction rhs) {
    return rhs>*this;
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
