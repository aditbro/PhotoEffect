#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
    public:
        float r;    // real part of the number
        float i;    // imaginary part of the number

        Complex();
        Complex(float r, float i);

        bool operator==(const Complex &c);
        Complex operator+(const Complex &c);
        Complex operator-(const Complex &c);
        Complex operator*(const Complex &c);

        float getScalar();

        void print();
};

#endif