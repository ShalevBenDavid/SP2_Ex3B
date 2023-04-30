// Created by Shalev Ben David.
#include "Fraction.hpp"
using namespace ariel;

// <<<<<<<<<<<<<<<<<< Operator + >>>>>>>>>>>>>>>>>>
Fraction Fraction :: operator + (const Fraction& other) const {
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
        throw std::invalid_argument("You can't divide by 0!");
    }
    Fraction temp (_numerator * other._denominator,
                   _denominator * other._numerator);
    temp.reduce();
    return temp;
}
Fraction Fraction :: operator / (const float& other) const {
    if (other == 0) {
        throw std::invalid_argument("You can't divide by 0!");
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

// <<<<<<<<<<<<<<<<<< Operator = >>>>>>>>>>>>>>>>>>
Fraction& Fraction :: operator = (const Fraction& right) {
    if (this != &right) {
        this -> _numerator = right._numerator;
        this -> _denominator = right._denominator;
    }
    return *this;
}
Fraction& Fraction :: operator = (Fraction&& other) noexcept {
    if (this != &other) {
        _numerator = other._numerator;
        _denominator = other._denominator;
        // Ruin other's data.
        other._numerator = 0;
        other._denominator = 1;
    }
    return *this;
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
    this -> _numerator /= save_gcd;
    this -> _denominator /= save_gcd;
}