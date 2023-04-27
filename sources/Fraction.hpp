// Created by Shalev Ben David.

#ifndef SP2_EX3A_FRACTION_H
#define SP2_EX3A_FRACTION_H
#include <iostream>

const int PRECISION = 1000;

namespace ariel {
    class Fraction {
        // Private attributes.
        int _numerator; // Numerator.
        int _denominator; // Denominator.

    public:
        // Constructors.
        Fraction (int numerator, int denominator) {
            if (denominator == 0) {
                throw std::invalid_argument("You can't divide by 0!");
            }
            this -> _numerator = numerator;
            this -> _denominator = denominator;
        }
        Fraction () : _numerator(1), _denominator(1) {} // Default
        Fraction (const Fraction& copy) : _numerator(copy._numerator), _denominator(copy._denominator) {} // Copy
        Fraction (Fraction&& copy) noexcept : _numerator(copy._numerator), _denominator(copy._denominator) {} // Move
        Fraction (float num) : _numerator((int) num * PRECISION), _denominator(PRECISION) {}

        // Destructor
        ~Fraction() {}

        // Stream operators.
        // <<<<<<<<<<<<<<<<<< Operator << >>>>>>>>>>>>>>>>>>
        friend std::ostream& operator << (std::ostream& output, const Fraction& frac) {
            Fraction temp(frac._numerator, frac._denominator);
            temp.reduce();
            output << temp._numerator << '/' << temp._denominator;
            return output;
        }
        // <<<<<<<<<<<<<<<<<< Operator >> >>>>>>>>>>>>>>>>>>
        friend std::istream& operator >> (std::istream& input, const Fraction& frac) {
            return input;
        }

        // Arithmetic operators.
        // <<<<<<<<<<<<<<<<<< Operator + >>>>>>>>>>>>>>>>>>
        Fraction operator + (const Fraction& other) const;
        Fraction operator + (const float& other) const;
        friend Fraction operator + (const float& left, const Fraction& right) {
            Fraction temp (left);
            temp = temp + right;
            temp.reduce();
            return temp;
        }

        // <<<<<<<<<<<<<<<<<< Operator - >>>>>>>>>>>>>>>>>>
        Fraction operator - (const Fraction& other) const;
        Fraction operator - (const float& other) const;
        friend Fraction operator - (const float& left, const Fraction& right) {
            Fraction temp (left);
            temp = temp - right;
            temp.reduce();
            return temp;
        }

        // <<<<<<<<<<<<<<<<<< Operator / >>>>>>>>>>>>>>>>>>
        Fraction operator / (const Fraction& other) const;
        Fraction operator / (const float& other) const;
        friend Fraction operator / (const float& left, const Fraction& right) {
            Fraction temp (left);
            temp = temp / right;
            temp.reduce();
            return temp;
        }

        // <<<<<<<<<<<<<<<<<< Operator * >>>>>>>>>>>>>>>>>>
        Fraction operator * (const Fraction& other) const;
        Fraction operator * (const float& other) const;
        friend Fraction operator * (const float& left, const Fraction& right) {
            Fraction temp (left);
            temp = temp * right;
            temp.reduce();
            return temp;
        }

        // Prefix increment (++n).
        Fraction& operator ++ ();
        // Prefix decrement (--n).
        Fraction& operator -- ();
        // Postfix increment (n++).
        Fraction operator ++ (int dont_care);
        // Postfix decrement (--n).
        Fraction operator -- (int dont_care);

        // Compare operators.
        // <<<<<<<<<<<<<<<<<< Operator = >>>>>>>>>>>>>>>>>>
        friend bool operator == (const Fraction &left, const Fraction &right) {
            Fraction temp_left (left);
            Fraction temp_right (right);
            temp_left.reduce();
            temp_right.reduce();
            return (temp_left._numerator == temp_right._numerator && temp_right._denominator == temp_left._denominator);
        }
        friend bool operator == (const float &left, const Fraction &right) {
            Fraction temp (left);
            return (temp == right);
        }
        friend bool operator == (const Fraction &left, const float &right) {
            Fraction temp (right);
            return (left == temp);
        }

        // <<<<<<<<<<<<<<<<<< Operator <= >>>>>>>>>>>>>>>>>>
        friend bool operator <= (const Fraction &left, const Fraction &right) {
            return (left._numerator * right._denominator < right._numerator * left._denominator);
        }
        friend bool operator <= (const float &left, const Fraction &right) {
            Fraction temp (left);
            return (temp <= right);
        }
        friend bool operator <= (const Fraction &left, const float &right) {
            Fraction temp (right);
            return (left <= temp);
        }

        // <<<<<<<<<<<<<<<<<< Operator >= >>>>>>>>>>>>>>>>>>
        friend bool operator >= (const Fraction &left, const Fraction &right) { return true; }
        friend bool operator >= (const float &left, const Fraction &right) { return true; }
        friend bool operator >= (const Fraction &left, const float &right) { return true; }

        // <<<<<<<<<<<<<<<<<< Operator > >>>>>>>>>>>>>>>>>>
        friend bool operator > (const Fraction &left, const Fraction &right) {
            return !(left <= right);
        }
        friend bool operator > (const float &left, const Fraction &right) {
            return !(left <= right);
        }
        friend bool operator > (const Fraction &left, const float &right) {
            return !(left <= right);
        }

        // <<<<<<<<<<<<<<<<<< Operator < >>>>>>>>>>>>>>>>>>
        friend bool operator < (const Fraction &left, const Fraction &right) { return true; }
        friend bool operator < (const float &left, const Fraction &right) { return true; }
        friend bool operator < (const Fraction &left, const float &right) { return true; }

        // <<<<<<<<<<<<<<<<<< Operator = >>>>>>>>>>>>>>>>>>
        Fraction& operator = (const Fraction& other);
        Fraction& operator = (Fraction&& other) noexcept;


            // Get methods.
        int& getNumerator() { return _numerator; }
        int& getDenominator() { return _denominator; }

        // Methods
        void reduce();
    };
}

#endif //SP2_EX3A_FRACTION_H