// Created by Shalev Ben David.
#include "Fraction.hpp"
using namespace ariel;

// <<<<<<<<<<<<<<<<<< Operator + >>>>>>>>>>>>>>>>>>
Fraction Fraction :: operator + (const Fraction& other) const {
    // Check for overflow.
    if ((abs(other._numerator) > MAX / abs(_denominator)) || (abs(_numerator) > MAX / abs(other._denominator)) ||
            (abs(_denominator) > MAX / abs(other._denominator))) {
        throw std::overflow_error("An overflow occurred.");
    }
    Fraction temp ((other._numerator * _denominator) + (_numerator * other._denominator),
                   _denominator * other._denominator);
    temp.reduce();
    return temp;
}
Fraction Fraction :: operator + (const float& other) const {
    Fraction temp (other);
    temp = *this + temp;
    temp.reduce();
    return temp;
}

// <<<<<<<<<<<<<<<<<< Operator - >>>>>>>>>>>>>>>>>>
Fraction Fraction ::operator - (const Fraction& other) const {
    Fraction temp (-(other._numerator * _denominator) + (_numerator * other._denominator),
                   _denominator * other._denominator);
    temp.reduce();
    return temp;
}
Fraction Fraction :: operator - (const float& other) const {
    Fraction temp (other);
    temp = *this - temp;
    temp.reduce();
    return temp;
}

// <<<<<<<<<<<<<<<<<< Operator / >>>>>>>>>>>>>>>>>>
Fraction Fraction :: operator / (const Fraction& other) const {
    if (other == 0) {
        throw std::runtime_error("You can't divide by 0!");
    }
    Fraction temp (_numerator * other._denominator,
                   _denominator * other._numerator);
    temp.reduce();
    return temp;
}
Fraction Fraction :: operator / (const float& other) const {
    if (other == 0) {
        throw std::runtime_error("You can't divide by 0!");
    }
    Fraction temp (other);
    temp = *this / temp;
    temp.reduce();
    return temp;
}

// <<<<<<<<<<<<<<<<<< Operator * >>>>>>>>>>>>>>>>>>
Fraction Fraction :: operator * (const Fraction& other) const {
    Fraction temp (_numerator * other._numerator,
                   _denominator * other._denominator);
    temp.reduce();
    return temp;
}
Fraction Fraction :: operator * (const float& other) const {
    Fraction temp (other);
    temp = *this * temp;
    temp.reduce();
    return temp;
}

// Prefix increment (++n).
Fraction& Fraction :: operator ++ () {
    _numerator += _denominator;
    return *this;
}

// Prefix decrement (--n).
Fraction& Fraction :: operator -- () {
    _numerator -= _denominator;
    return *this;
}

// Postfix increment (n++).
Fraction Fraction :: operator ++ (int dont_care) {
    Fraction copy (*this);
    _numerator += _denominator;
    return copy;
}

// Postfix decrement (--n).
Fraction Fraction :: operator -- (int dont_care) {
    Fraction copy (*this);
    _numerator -= _denominator;
    return copy;
}

// Get methods.
int Fraction :: getNumerator () { return _numerator; }
int Fraction :: getDenominator () { return _denominator; }

// Set methods.
void Fraction :: setNumerator (int numerator) {
    _numerator = numerator;
    this -> reduce();
}
void Fraction :: setDenominator (int denominator) {
    _denominator = denominator;
    this -> reduce();
}

/**
 *
 * @param numerator
 * @param denominator
 * @return the gcd of the numerator and denominator of this object.
 */
int gcd (int numerator, int denominator) {
    if (!numerator) { return denominator; }
    // Wouldn't happen but for the general case of computing gcd.
    if (!denominator) { return numerator; }
    while (denominator) {
        int r = numerator % denominator;
        numerator = denominator;
        denominator = r;
    }
    return numerator;
}

/**
 * Reduces a fraction before returning it.
 */
void Fraction:: reduce () {
    int save_gcd = gcd (this -> _numerator, this -> _denominator);
    _numerator /= save_gcd;
    _denominator /= save_gcd;
    // If the denominator is negative, multiply both the denominator and numerator by -1.
    if (_denominator < 0) {
        _numerator *= -1;
        _denominator *= -1;
    }
}