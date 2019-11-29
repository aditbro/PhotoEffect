#include <math.h>
#include "complex.h"

Complex::Complex() {
    this->r = 0.0;
    this->i = 0.0;
}

Complex::Complex(float r, float i) {
    this->r = r;
    this->i = i;
}

bool Complex::operator==(const Complex &c) {
    return (r == c.r && i == c.i);
}

Complex Complex::operator+(const Complex &c) {
    Complex number(r + c.r, i + c.i);
    return number;
}

Complex Complex::operator-(const Complex &c) {
    Complex number(r - c.r, i - c.i);
    return number;
}

Complex Complex::operator*(const Complex &c) {
    Complex number;
    number.r = this->r * c.r - this->i * c.i;
    number.i = this->r * c.i + this->i * c.r;
    return number;
}

float Complex::getScalar() {
    return sqrt(pow(this->r, 2) + pow(this->i, 2));
}

void Complex::print() {
    std::cout << r << " + " << i << "i";
}