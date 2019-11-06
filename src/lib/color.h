#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color {
    public:
        unsigned char b;
        unsigned char g;
        unsigned char r;

        Color(char r, char g, char b) {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        bool operator==(const Color &c) {
            return (r == c.r && g == c.g && b == c.b);
        }

        void print() {
            std::cout << +r << " " << +g << " " << +b << " ";
        }
};

#endif