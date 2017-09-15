#ifndef COMPLEX_H
#define COMPLEX_H

#include <istream>
#include <ostream>

class Complex
{
    public:

    Complex(double r, double i) : real(r), imaginary(i) { }
    Complex(double r) : real(r), imaginary(0) { }

    Complex& operator+=(const Complex& rhs);
    Complex& operator-=(const Complex& rhs);
    Complex& operator*=(const Complex& rhs);
    Complex& operator/=(const Complex& rhs);

    /**
      * Return square modulus
      */
    double abs2();

    /**
      * Return argument of complex number
      */
    double arg();

    std::ostream& operator<<(std::ostream& os, const Complex& n);
    std::istream& operator>>(std::istream& is, Complex& n);

    private:
        double real;
        double imaginary;
};

#endif // COMPLEX_H
