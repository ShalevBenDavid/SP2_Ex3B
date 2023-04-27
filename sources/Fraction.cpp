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
    Fraction temp (_numerator * other._denominator,
                   _denominator * other._numerator);
    temp.reduce();
    return temp;
}
Fraction Fraction :: operator / (const float& other) const {
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
Fraction& Fraction :: operator = (const Fraction& other) {
    if (this != &other) {
        _numerator = other._numerator;
        _denominator = other._denominator;
    }
    return *this;
}
Fraction& Fraction :: operator = (Fraction&& other) noexcept {
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
 * @return the gcd of the numerator and denominator
 */
int gcd (int numerator, int denominator) {
    if (!numerator) { return denominator; }
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
    int save_gcd = gcd (this -> getNumerator(), this -> getDenominator());
    this -> getNumerator() /= save_gcd;
    this -> getDenominator() /= save_gcd;
}