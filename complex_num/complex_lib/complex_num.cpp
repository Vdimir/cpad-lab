#include "complex.h"
#include <cmath>

Complex operator+(Complex lhs, const Complex& rhs) {
    lhs += rhs;
    return lhs;
}

Complex operator-(Complex lhs, const Complex& rhs) {
    lhs -= rhs;
    return lhs;
}

Complex operator*(Complex lhs, const Complex& rhs) {
    lhs *= rhs;
    return lhs;
}

Complex operator/(Complex lhs, const Complex& rhs) {
    lhs /= rhs;
    return lhs;
}


Complex& Complex::operator+=(const Complex& rhs) {
    this->real += rhs.real;
    this->imaginary += rhs.imaginary;
    return *this;
}

Complex& Complex::operator-=(const Complex& rhs) {
    this->real -= rhs.real;
    this->imaginary -= rhs.imaginary;
    return *this;
}

Complex& Complex::operator*=(const Complex& rhs) {
    double a = this->real,
           b = this->imaginary,
           c = rhs.real,
           d = rhs.imaginary;

    this->real = a*c - b*d;
    this->imaginary = a*d + b*c;
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs) {
    double a = this->real,
           b = this->imaginary,
           c = rhs.real,
           d = rhs.imaginary;
    double den = (c*c+d*d);

    this->real = (a*c+d*b)/den;
    this->imaginary = (b*c-a*d)/den;
    return *this;
}

double Complex::abs2() {
    double res = this->real*this->real + this->imaginary*this->imaginary;
    return res;
}

double Complex::arg() {
    double res = std::atan2(this->imaginary, this->real);
    return res;
}


std::ostream& operator<<(std::ostream& os, const Complex& n) {
    os << n.real << " + " << n.imaginary << "*i";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& n) {
    is >> n.real >> n.imaginary;
    return is;
}
