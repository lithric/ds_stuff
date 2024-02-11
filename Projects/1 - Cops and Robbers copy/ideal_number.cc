#include "ideal_number.h"

IdealNumber::IdealNumber(float _decimal) {
    int _integer;
    Fraction _fraction;

    sign = false;
    if (_decimal<0) {
        sign = true;
        decimal = -decimal;
    }

    _integer = static_cast<int>(_decimal);
    _decimal -= _integer;
    _fraction = Fraction(_decimal);
    _decimal -= static_cast<float>(_fraction);

    integer = _integer;
    fraction = _fraction;
    decimal = _decimal;
}

IdealNumber::IdealNumber(Fraction _fraction) {
    int _integer;

    sign = false;
    if (_fraction<0) {
        sign = true;
        _fraction = -_fraction;
    }

    _integer = static_cast<int>(_fraction);
    _fraction -= _integer;

    integer = _integer;
    fraction = _fraction;
    decimal = 0;
}

IdealNumber::IdealNumber(int _integer) {
    sign = false;
    if (_integer<0) {
        _integer=-_integer;
        sign = true;
    }
    integer = _integer;
    fraction = 0;
    decimal = 0.0;
}