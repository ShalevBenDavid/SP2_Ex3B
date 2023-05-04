// Created by Shalev Ben David.

#ifndef SP2_EX3A_FRACTION_H
#define SP2_EX3A_FRACTION_H
#include <iostream>
#include <limits>

const int PRECISION = 1000;

namespace ariel {
    class Fraction {
        // Private attributes.
        int _numerator; // Numerator.
        int _denominator; // Denominator.

    public:
        // Constructors.
        Fraction (const int numerator, int denominator) {
            // If denominator is 0, throw exception.
            if (denominator == 0) {
                throw std::invalid_argument("You can't create a fraction where denominator is 0!");
            }
            this -> _numerator = numerator;
            this -> _denominator = denominator;
            // Reduce fraction.
            this -> reduce();
        }
        Fraction () : _numerator(1), _denominator(1) {} // Default
        Fraction (float num) : _numerator((int) (num * PRECISION)), _denominator(PRECISION) {}

        // Stream operators.
        // <<<<<<<<<<<<<<<<<< Operator << >>>>>>>>>>>>>>>>>>
        friend std::ostream& operator << (std::ostream& output, const Fraction& frac) {
            output << frac._numerator << '/' << frac._denominator;
            return output;
        }
        // <<<<<<<<<<<<<<<<<< Operator >> >>>>>>>>>>>>>>>>>>
        friend std::istream& operator >> (std::istream& input, Fraction& frac) {
            int numerator = 0;
            int denominator = 0;
            // Insert to the input stream.
            input >> numerator >> denominator;
            // If denominator is 0, throw exception.
            if (denominator == 0) {
                throw std::runtime_error("You can't assign 0 to the fraction's denominator!");
            }
            // If frac is null, throw input.
            if (!input) {
                return input;
            }
            // Assign the data and return input.
            frac._denominator = denominator;
            frac._numerator = numerator;
            frac.reduce();
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
            if (right == 0) {
                throw std::runtime_error("You can't divide by 0!");
            }
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
            return (temp_left._numerator == temp_right._numerator && temp_left._denominator == temp_right._denominator);
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
        friend bool operator <= (const Fraction &left, const Fraction &right) {  // 2 * 5 <= -3
            return (left._numerator * right._denominator <= right._numerator * left._denominator);
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
        friend bool operator >= (const Fraction &left, const Fraction &right) {
            return (left > right) || (left == right);
        }
        friend bool operator >= (const float &left, const Fraction &right) {
            return (left > right) || (left == right);
        }
        friend bool operator >= (const Fraction &left, const float &right) {
            return (left > right) || (left == right);
        }

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
        friend bool operator < (const Fraction &left, const Fraction &right) {
            return !(left >= right);
        }
        friend bool operator < (const float &left, const Fraction &right) {
            return !(left >= right);
        }
        friend bool operator < (const Fraction &left, const float &right) {
            return !(left >= right);
        }

        // <<<<<<<<<<<<<<<<<< Operator != >>>>>>>>>>>>>>>>>>
        friend bool operator != (const Fraction &left, const Fraction &right) {
            return !(left == right);
        }
        friend bool operator != (const float &left, const Fraction &right) {
            return !(left == right);
        }
        friend bool operator != (const Fraction &left, const float &right) {
            return !(left == right);
        }

        // Get methods.
        int getNumerator () const;
        int getDenominator () const;
        // Set methods.
        void setNumerator (int numerator);
        void setDenominator (int denominator);

        // Methods
        void reduce ();
    };
}

#endif //SP2_EX3A_FRACTION_H