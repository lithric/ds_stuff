#include <iostream>
#include <fstream>
#include "fraction.h"
#include "point.h"
#include "ideal_number.h"

using namespace std;

int main () {
    Fraction test = Fraction(1,Fraction(5,3)) + 1;
    test = Fraction(1,test) + 3;
    test = -test;
    Fraction test2;
    test2 = 0.573450673f;
    cout << "Hello There!" << endl;
    cout << test << endl;
    cout << test2 << endl;
    cout << static_cast<float>(test2) << endl;
    return 0;
}