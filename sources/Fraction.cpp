// Created by Shalev Ben David.
#include "Fraction.hpp"
using namespace ariel;

namespace ariel {
// Overflow functions. Using source: https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
void add_overflow (const Fraction&, const Fraction&);
void sub_overflow (const Fraction&, const Fraction&);
void div_overflow (const Fraction&, const Fraction&);
void mul_overflow (const Fraction&, const Fraction&);

    // <<<<<<<<<<<<<<<<<< Operator << >>>>>>>>>>>>>>>>>>
    std :: ostream &operator << (std :: ostream& output, const Fraction& frac) {
        output << frac._numerator << '/' << frac._denominator;
        return output;
    }

    // <<<<<<<<<<<<<<<<<< Operator >> >>>>>>>>>>>>>>>>>>
    std :: istream &operator >> (std :: istream& input, Fraction& frac) {
        int numerator = 0;
        int denominator = 0;
        // Insert to the input stream.
        input >> numerator >> denominator;
        // If denominator is 0, throw exception.
        if (denominator == 0) {
            throw std :: runtime_error("You can't assign 0 to the fraction's denominator!");
        }
        // If frac is null, throw input.
        if (!input) {
            return input;
        }
        // Assign the data and return input.
        frac._denominator = denominator;
        frac._numerator = numerator;
        // Reduce frac.
        frac.reduce();
        return input;
    }

    // <<<<<<<<<<<<<<<<<< Operator + >>>>>>>>>>>>>>>>>>
    Fraction Fraction :: operator + (const Fraction& other) const {
        // Check for overflow.
        add_overflow(*this, other);
        Fraction temp((other._numerator * _denominator) + (_numerator * other._denominator),
                      _denominator * other._denominator);
        temp.reduce();
        return temp;
    }

    Fraction Fraction :: operator + (const float& other) const {
        Fraction temp(other);
        temp = *this + temp;
        temp.reduce();
        return temp;
    }

    Fraction operator + (const float& left, const Fraction& right) {
        Fraction temp (left);
        temp = temp + right;
        temp.reduce();
        return temp;
    }

    // <<<<<<<<<<<<<<<<<< Operator - >>>>>>>>>>>>>>>>>>
    Fraction Fraction :: operator - (const Fraction& other) const {
        // Check for overflow.
        sub_overflow(*this, other);
        Fraction temp(-(other._numerator * _denominator) + (_numerator * other._denominator),
                      _denominator * other._denominator);
        temp.reduce();
        return temp;
    }

    Fraction Fraction :: operator - (const float& other) const {
        Fraction temp(other);
        temp = *this - temp;
        temp.reduce();
        return temp;
    }

    Fraction operator - (const float& left, const Fraction& right) {
        Fraction temp (left);
        temp = temp - right;
        temp.reduce();
        return temp;
    }

    // <<<<<<<<<<<<<<<<<< Operator / >>>>>>>>>>>>>>>>>>
    Fraction Fraction :: operator / (const Fraction &other) const {
        // Check for overflow.
        div_overflow(*this, other);
        // Check if we divide by 0.
        if (other == 0) {
            throw std :: runtime_error("You can't divide by 0!");
        }
        Fraction temp(_numerator * other._denominator,
                      _denominator * other._numerator);
        temp.reduce();
        return temp;
    }

    Fraction Fraction :: operator / (const float& other) const {
        if (other == 0) {
            throw std :: runtime_error("You can't divide by 0!");
        }
        Fraction temp(other);
        temp = *this / temp;
        temp.reduce();
        return temp;
    }

    Fraction operator / (const float& left, const Fraction& right) {
        if (right == 0) {
            throw std :: runtime_error("You can't divide by 0!");
        }
        Fraction temp (left);
        temp = temp / right;
        temp.reduce();
        return temp;
    }

    // <<<<<<<<<<<<<<<<<< Operator * >>>>>>>>>>>>>>>>>>
    Fraction Fraction :: operator * (const Fraction& other) const {
        // Check for overflow.
        mul_overflow(*this, other);
        Fraction temp(_numerator * other._numerator,
                      _denominator * other._denominator);
        temp.reduce();
        return temp;
    }

    Fraction Fraction :: operator * (const float& other) const {
        Fraction temp(other);
        temp = *this * temp;
        temp.reduce();
        return temp;
    }

    Fraction operator * (const float& left, const Fraction& right) {
        Fraction temp (left);
        temp = temp * right;
        temp.reduce();
        return temp;
    }


    // Prefix increment (++n).
    Fraction& Fraction :: operator ++ () {
        // Throw exception in case of an overflow.
        if (__builtin_add_overflow(_numerator, _denominator, &_numerator)) {
            throw std :: overflow_error("An overflow occurred!");
        }
        return *this;
    }

    // Prefix decrement (--n).
    Fraction& Fraction :: operator -- () {
        // Throw exception in case of an overflow.
        if (__builtin_sub_overflow(_numerator, _denominator, &_numerator)) {
            throw std :: overflow_error("An overflow occurred!");
        }
        return *this;
    }

    // Postfix increment (n++).
    Fraction Fraction :: operator ++ (int dont_care) {
        Fraction copy(*this);
        // Throw exception in case of an overflow.
        if (__builtin_add_overflow(_numerator, _denominator, &_numerator)) {
            throw std :: overflow_error("An overflow occurred!");
        }
        return copy;
    }

    // Postfix decrement (--n).
    Fraction Fraction :: operator -- (int dont_care) {
        Fraction copy(*this);
        // Throw exception in case of an overflow.
        if (__builtin_sub_overflow(_numerator, _denominator, &_numerator)) {
            throw std :: overflow_error("An overflow occurred!");
        }
        return copy;
    }

    // <<<<<<<<<<<<<<<<<< Operator = >>>>>>>>>>>>>>>>>>
    bool operator == (const Fraction& left, const Fraction& right) {
        return (left._numerator == right._numerator && left._denominator == right._denominator);
    }
    bool operator == (const float& left, const Fraction& right) {
        Fraction temp (left);
        return (temp == right);
    }
    bool operator == (const Fraction& left, const float& right) {
        Fraction temp (right);
        return (left == temp);
    }

    // <<<<<<<<<<<<<<<<<< Operator <= >>>>>>>>>>>>>>>>>>
    bool operator <= (const Fraction& left, const Fraction& right) {  // 2 * 5 <= -3
        return (left._numerator * right._denominator <= right._numerator * left._denominator);
    }
    bool operator <= (const float& left, const Fraction& right) {
        Fraction temp (left);
        return (temp <= right);
    }
    bool operator <= (const Fraction& left, const float& right) {
        Fraction temp (right);
        return (left <= temp);
    }

    // <<<<<<<<<<<<<<<<<< Operator >= >>>>>>>>>>>>>>>>>>
    bool operator >= (const Fraction& left, const Fraction& right) {
        return (left > right) || (left == right);
    }
    bool operator >= (const float& left, const Fraction& right) {
        return (left > right) || (left == right);
    }
    bool operator >= (const Fraction& left, const float& right) {
        return (left > right) || (left == right);
    }

    // <<<<<<<<<<<<<<<<<< Operator > >>>>>>>>>>>>>>>>>>
    bool operator > (const Fraction& left, const Fraction& right) {
        return !(left <= right);
    }
    bool operator > (const float& left, const Fraction& right) {
        return !(left <= right);
    }
    bool operator > (const Fraction& left, const float& right) {
        return !(left <= right);
    }

    // <<<<<<<<<<<<<<<<<< Operator < >>>>>>>>>>>>>>>>>>
    bool operator < (const Fraction& left, const Fraction& right) {
        return !(left >= right);
    }
    bool operator < (const float& left, const Fraction& right) {
        return !(left >= right);
    }
    bool operator < (const Fraction& left, const float& right) {
        return !(left >= right);
    }

    // <<<<<<<<<<<<<<<<<< Operator != >>>>>>>>>>>>>>>>>>
    bool operator != (const Fraction& left, const Fraction& right) {
        return !(left == right);
    }
    bool operator != (const float& left, const Fraction& right) {
        return !(left == right);
    }
    bool operator != (const Fraction& left, const float& right) {
        return !(left == right);
    }

    // Get methods.
    int Fraction :: getNumerator () const { return _numerator; }

    int Fraction :: getDenominator () const { return _denominator; }

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
    void Fraction :: reduce () {
        int save_gcd = gcd(_numerator, _denominator);
        _numerator /= save_gcd;
        _denominator /= save_gcd;
        // If the denominator is negative, multiply both the denominator and numerator by -1.
        if (_denominator < 0) {
            _numerator *= -1;
            _denominator *= -1;
        }
    }

    // <<<<<<<<<<<<<<<<<< Overflow Functions >>>>>>>>>>>>>>>>>>
    /**
     * Throws exception in case of overflow when computing f1 + f2.
     * @param f1 - First fraction.
     * @param f2 - Second fraction.
     */
    void add_overflow (const Fraction &f1, const Fraction &f2) {
        int result;
        int result1;
        int result2;
        if (__builtin_mul_overflow(f1.getDenominator(), f2.getDenominator(), &result) |
            __builtin_mul_overflow(f1.getNumerator(), f2.getDenominator(), &result1) |
            __builtin_mul_overflow(f2.getNumerator(), f1.getDenominator(), &result2) |
            __builtin_add_overflow(result1, result2, &result)) {
            throw std::overflow_error("An overflow occurred!");
        }
    }

    /**
     * Throws exception in case of overflow when computing f1 - f2.
     * @param f1 - First fraction.
     * @param f2 - Second fraction.
     */
    void sub_overflow (const Fraction &f1, const Fraction &f2) {
        int result;
        int result1;
        int result2;
        if (__builtin_mul_overflow(f1.getDenominator(), f2.getDenominator(), &result) |
            __builtin_mul_overflow(f1.getNumerator(), f2.getDenominator(), &result1) |
            __builtin_mul_overflow(f2.getNumerator(), f1.getDenominator(), &result2) |
            __builtin_sub_overflow(result1, result2, &result)) {
            throw std::overflow_error("An overflow occurred!");
        }
    }

    /**
     * Throws exception in case of overflow when computing f1 / f2.
     * @param f1 - First fraction.
     * @param f2 - Second fraction.
     */
    void div_overflow (const Fraction &f1, const Fraction &f2) {
        int result;
        if (__builtin_mul_overflow(f1.getNumerator(), f2.getDenominator(), &result) |
            __builtin_mul_overflow(f1.getDenominator(), f2.getNumerator(), &result)) {
            throw std::overflow_error("An overflow occurred!");
        }
    }

    /**
     * Throws exception in case of overflow when computing f1 * f2.
     * @param f1 - First fraction.
     * @param f2 - Second fraction.
     */
    void mul_overflow (const Fraction &f1, const Fraction &f2) {
        int result;
        if (__builtin_mul_overflow(f1.getNumerator(), f2.getNumerator(), &result) |
            __builtin_mul_overflow(f1.getDenominator(), f2.getDenominator(), &result)) {
            throw std::overflow_error("An overflow occurred!");
        }
    }
}