#include <iostream>
#include <fstream>
#include <cmath>
#include "fraction.h"
#include "point.h"
#include "ideal_number.h"

using namespace std;

int main () {
    double num = 0.312312312312;
    Fraction test1 = num;
    cout << test1 << endl;
    cout << (float)test1 << endl;
    cout << (double)test1 << endl;
    cout << num << endl;
    return 0;
}