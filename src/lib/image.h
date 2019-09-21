#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include "color.h"

/*
 * Image type code
 * BMP = 1
 */

class Image {
    public:
        Image(char type, int width, int height);

        Color getColorAt(int i, int j);
        void setColorAt(int i, int j, Color c);

        int getWidth();
        int getHeight();
        char getType();

    private:
        std::vector<Color> img;
        int width;
        int height;
        char type;
};

#endif