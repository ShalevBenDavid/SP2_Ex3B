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
        Fraction () : _numerator(1), _denominator(1) { }; // Default.
        Fraction (float num) : _numerator((int) (num * PRECISION)), _denominator(PRECISION) {
            // Reduce fraction.
            this -> reduce();
        }

        // Stream operators.
        // <<<<<<<<<<<<<<<<<< Operator << >>>>>>>>>>>>>>>>>>
        friend std :: ostream& operator << (std :: ostream& output, const Fraction& frac);
        // <<<<<<<<<<<<<<<<<< Operator >> >>>>>>>>>>>>>>>>>>
        friend std :: istream& operator >> (std :: istream& input, Fraction& frac);

        // Arithmetic operators.
        // <<<<<<<<<<<<<<<<<< Operator + >>>>>>>>>>>>>>>>>>
        Fraction operator + (const Fraction& other) const;
        Fraction operator + (const float& other) const;
        friend Fraction operator + (const float& left, const Fraction& right);

        // <<<<<<<<<<<<<<<<<< Operator - >>>>>>>>>>>>>>>>>>
        Fraction operator - (const Fraction& other) const;
        Fraction operator - (const float& other) const;
        friend Fraction operator - (const float& left, const Fraction& right);

        // <<<<<<<<<<<<<<<<<< Operator / >>>>>>>>>>>>>>>>>>
        Fraction operator / (const Fraction& other) const;
        Fraction operator / (const float& other) const;
        friend Fraction operator / (const float& left, const Fraction& right);

        // <<<<<<<<<<<<<<<<<< Operator * >>>>>>>>>>>>>>>>>>
        Fraction operator * (const Fraction& other) const;
        Fraction operator * (const float& other) const;
        friend Fraction operator * (const float& left, const Fraction& right);

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
        friend bool operator == (const Fraction& left, const Fraction& right);
        friend bool operator == (const float& left, const Fraction& right);
        friend bool operator == (const Fraction& left, const float& right);

        // <<<<<<<<<<<<<<<<<< Operator <= >>>>>>>>>>>>>>>>>>
        friend bool operator <= (const Fraction& left, const Fraction& right);
        friend bool operator <= (const float& left, const Fraction& right);
        friend bool operator <= (const Fraction& left, const float& right);

        // <<<<<<<<<<<<<<<<<< Operator >= >>>>>>>>>>>>>>>>>>
        friend bool operator >= (const Fraction& left, const Fraction& right);
        friend bool operator >= (const float& left, const Fraction& right);
        friend bool operator >= (const Fraction& left, const float& right);

        // <<<<<<<<<<<<<<<<<< Operator > >>>>>>>>>>>>>>>>>>
        friend bool operator > (const Fraction& left, const Fraction& right);
        friend bool operator > (const float& left, const Fraction& right);
        friend bool operator > (const Fraction& left, const float& right);

        // <<<<<<<<<<<<<<<<<< Operator < >>>>>>>>>>>>>>>>>>
        friend bool operator < (const Fraction& left, const Fraction& right);
        friend bool operator < (const float& left, const Fraction& right);
        friend bool operator < (const Fraction& left, const float& right);

        // <<<<<<<<<<<<<<<<<< Operator != >>>>>>>>>>>>>>>>>>
        friend bool operator != (const Fraction& left, const Fraction& right);
        friend bool operator != (const float& left, const Fraction& right);
        friend bool operator != (const Fraction& left, const float& right);

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